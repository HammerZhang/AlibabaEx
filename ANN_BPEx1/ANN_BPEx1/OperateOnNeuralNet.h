#ifndef _OPERATEONNEURALNET_H
#define _OPERATEONNEURALNET_H

#include "NeuralNet.h"
#define NEURALNET_VERSION 1.0;
#define RESMAPLE_LEN 4;

class OperateOnNN
{
public:
	OperateOnNN();
	~OperateOnNN();

	void SetNetworkPara(int nInput, int nOutput, int nNeuronsPerLyr, int nHiddenLyr);
	bool CreateNetwork();
	void SetTrainConfig(int nMaxEpoch, double dMinError, double dLearningRate);
	void SetStopFlag(bool bStop){ m_bStop = bStop; }

	double GetError(){ return m_dError; }
	int GetEpoch(){ return m_nEpochs; }
	int GetNeuronsNumPerLyr(){ return m_nNeuronsPerLyr; }

	bool Train(vector<iovector> &SetIn, vector<iovector> &SetOut);
	bool LoadTrainResultsFromFile(const char *lpszFileName, unsigned long startPos);
	//int Recognize(char *strPathName, CRect rt, double &confidence);

private:
	/*Network*/
	NeuralNet *m_oNetwork;

	/*神经网络的参数*/
	int m_nInput;
	int m_nOutput;
	int m_nNeuronsPerLyr;
	int m_nHiddenLyr;

	/*训练参数配置*/
	int m_nMaxEpoch;
	double m_dMinError;
	double m_dLearningRate;

	/*动态参数设置*/
	int m_nEpochs;
	double m_dError;                   // 每次迭代的平均误差
	bool m_bStop;                      // 控制是否终止迭代
	vector<double> m_vecError;         // 记录每次训练的误差，用于绘制误差曲线

};

/*
*用来保存或者读取分类结果
*/
struct NEURALNET_HEADER
{
	unsigned long version;             // 版本信息

	/*初始参数*/
	int m_nInput;
	int m_nOutput;
	int m_nNeuronsPerLyr;
	int m_nHiddenLyr;

	/*训练配置参数*/
	int m_nMaxEpoch;
	double m_dMinError;
	double m_dLearningRate;

	/*动态参数*/
	int m_nEpochs;
	double m_dError;
};

#endif