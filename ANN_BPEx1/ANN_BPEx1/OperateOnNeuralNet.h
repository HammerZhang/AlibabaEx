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

	/*������Ĳ���*/
	int m_nInput;
	int m_nOutput;
	int m_nNeuronsPerLyr;
	int m_nHiddenLyr;

	/*ѵ����������*/
	int m_nMaxEpoch;
	double m_dMinError;
	double m_dLearningRate;

	/*��̬��������*/
	int m_nEpochs;
	double m_dError;                   // ÿ�ε�����ƽ�����
	bool m_bStop;                      // �����Ƿ���ֹ����
	vector<double> m_vecError;         // ��¼ÿ��ѵ���������ڻ����������

};

/*
*����������߶�ȡ������
*/
struct NEURALNET_HEADER
{
	unsigned long version;             // �汾��Ϣ

	/*��ʼ����*/
	int m_nInput;
	int m_nOutput;
	int m_nNeuronsPerLyr;
	int m_nHiddenLyr;

	/*ѵ�����ò���*/
	int m_nMaxEpoch;
	double m_dMinError;
	double m_dLearningRate;

	/*��̬����*/
	int m_nEpochs;
	double m_dError;
};

#endif