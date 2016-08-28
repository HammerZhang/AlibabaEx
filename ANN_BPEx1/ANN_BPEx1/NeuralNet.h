// NeuralNet.h: �ṩNerualNet��ӿ�
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <vector>
#include <math.h>
#include "NeuroNode.h"
using namespace std;

typedef vector<double> iovector;
#define BIAS 1.0;                                                   // �ؾ�
const double WEIGHT_FACTOR = 0.1;                                   // �������Ƴ�ʼȨֵ

//����һ��0-1�����������
inline double Randfloat()
{
	return (rand() / (RAND_MAX + 1.0));
}

//����һ��-1-1�����������
inline double RandomClamped()
{
	return WEIGHT_FACTOR*(Randfloat() - Randfloat());
}

class  NeuralNet
{
public:
	/*
	*���캯��
	*/
	 NeuralNet(int nInput,int nOutput,int nNeuronsPerLyr,int nHiddenLyr);

	 /*
	 *��������
	 */
	~ NeuralNet();

	/*
	*����ǰ���������
	*/
	bool CalculateOutput(vector<double> input, vector<double> &output);
	
	/*
	*���򴫲�ѵ��
	*/
	bool TrainingEpoch(vector<iovector> &SetIn, vector<iovector> &SetOut, double learningRate);

	/*
	*��ȡ���
	*/
	double GetErrorSum(){ return m_dErrorSum; }
	SNeuronLayer *GetHiddenLyr(){ return m_pHiddenLyr; }
	SNeuronLayer *GetOutputLyr(){ return m_pOutputLyr; }

private:
	// ��ʼ��������ѵ�������в��ܱ��ı�
	int m_nInput;                                  // ����ڵ����� 
	int m_nOutput;                                 // ����ڵ�����
	int m_nHiddenLyr;                              // ���ز����
	int m_nNeuronPerLyr;                           // ÿ�����ز�ڵ�����

	// ��̬����
	double m_dErrorSum;                            // ÿ�ε������֮��
	SNeuronLayer * m_pHiddenLyr;                   // ���ز�
	SNeuronLayer * m_pOutputLyr;                   // �����

private:
	/*
	*���������磬Ϊÿ��ڵ����ռ�
	*/
	void CreateNetwrok();

	/*
	*��ʼ��������
	*/
	void InitNetwork();

	/*
	*Sigmoid�����
	*/
	double SigmoidActive(double netinput)
	{
		// ����sigmoid����б��
		double degree = 1.0;
		return (1 / (1 + exp(-netinput / degree)));
	}
};

#endif