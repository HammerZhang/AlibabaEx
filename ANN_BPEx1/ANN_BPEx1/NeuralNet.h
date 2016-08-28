// NeuralNet.h: 提供NerualNet类接口
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <vector>
#include <math.h>
#include "NeuroNode.h"
using namespace std;

typedef vector<double> iovector;
#define BIAS 1.0;                                                   // 截距
const double WEIGHT_FACTOR = 0.1;                                   // 用来限制初始权值

//返回一个0-1的随机浮点数
inline double Randfloat()
{
	return (rand() / (RAND_MAX + 1.0));
}

//返回一个-1-1的随机浮点数
inline double RandomClamped()
{
	return WEIGHT_FACTOR*(Randfloat() - Randfloat());
}

class  NeuralNet
{
public:
	/*
	*构造函数
	*/
	 NeuralNet(int nInput,int nOutput,int nNeuronsPerLyr,int nHiddenLyr);

	 /*
	 *析构函数
	 */
	~ NeuralNet();

	/*
	*计算前馈网络输出
	*/
	bool CalculateOutput(vector<double> input, vector<double> &output);
	
	/*
	*方向传播训练
	*/
	bool TrainingEpoch(vector<iovector> &SetIn, vector<iovector> &SetOut, double learningRate);

	/*
	*获取误差
	*/
	double GetErrorSum(){ return m_dErrorSum; }
	SNeuronLayer *GetHiddenLyr(){ return m_pHiddenLyr; }
	SNeuronLayer *GetOutputLyr(){ return m_pOutputLyr; }

private:
	// 初始参数，在训练过程中不能被改变
	int m_nInput;                                  // 输入节点数量 
	int m_nOutput;                                 // 输出节点数量
	int m_nHiddenLyr;                              // 隐藏层层数
	int m_nNeuronPerLyr;                           // 每层隐藏层节点数量

	// 动态参数
	double m_dErrorSum;                            // 每次迭代误差之和
	SNeuronLayer * m_pHiddenLyr;                   // 隐藏层
	SNeuronLayer * m_pOutputLyr;                   // 输出层

private:
	/*
	*构建神经网络，为每层节点分配空间
	*/
	void CreateNetwrok();

	/*
	*初始化神经网络
	*/
	void InitNetwork();

	/*
	*Sigmoid激活函数
	*/
	double SigmoidActive(double netinput)
	{
		// 控制sigmoid函数斜率
		double degree = 1.0;
		return (1 / (1 + exp(-netinput / degree)));
	}
};

#endif