// NeuralNet.cpp: NeuralNet���ʵ��
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NeuralNet.h"
#include <assert.h>

NeuralNet::NeuralNet(int nInput, int nOutput, int nNeuronsPerLyr, int nHiddenLyr)
{
	assert(nInput > 0 && nOutput > 0 && nNeuronsPerLyr > 0 && nHiddenLyr > 0);
	m_nInput = nInput;
	m_nOutput = nOutput;
	m_nNeuronPerLyr = nNeuronsPerLyr;

	if (nHiddenLyr != 1)
		m_nHiddenLyr = 1;
	else
		m_nHiddenLyr = nHiddenLyr;

	m_pHiddenLyr = NULL;
	m_pOutputLyr = NULL;

	CreateNetwrok();                          // ����һ������
	InitNetwork();                            // ��ʼ������
}

NeuralNet::~NeuralNet()
{
	if (m_pHiddenLyr != NULL)
	{
		delete m_pHiddenLyr;
	}
	if (m_pOutputLyr != NULL)
	{
		delete m_pOutputLyr;
	}
}

void NeuralNet::CreateNetwrok()
{
	m_pHiddenLyr = new SNeuronLayer(m_nNeuronPerLyr, m_nInput);
	m_pOutputLyr = new SNeuronLayer(m_nOutput, m_nNeuronPerLyr);
}

void NeuralNet::InitNetwork()
{
	int i, j;

	/*��ʼ�����ز��Ȩֵ*/
	for (i = 0; i < m_pHiddenLyr->m_nNeuron; i++)
	{
		for (j = 0; j < m_pHiddenLyr->m_pNeurons[i].m_nInput; j++)
		{
			m_pHiddenLyr->m_pNeurons[i].m_pWeights[j] = RandomClamped();
#ifdef NEED_MOMENTUM
			m_pHiddenLyr->m_pNeurons[i].m_pPrevWeights[j] = 0;
#endif // NEED_MOMENTUM

		}
	}

	/*��ʼ��������Ȩֵ*/
	for (i = 0; i < m_pOutputLyr->m_nNeuron; i++)
	{
		for (j = 0; j < m_pOutputLyr->m_pNeurons[i].m_nInput; j++)
		{
			m_pOutputLyr->m_pNeurons[i].m_pWeights[j] = RandomClamped();
#ifdef NEED_MOMENTUM
			m_pOutputLyr->m_pNeurons[i].m_pPrevWeights[j] = 0;
#endif // NEED_MOMENTUM

		}
	}

	m_dErrorSum = 9999.0;    // �������Ϊһ���ܴ��ֵ��������ѵ���𽥼�С
}

bool NeuralNet::CalculateOutput(vector<double> input, vector<double> &output)
{
	if (input.size() != m_nInput)
	{
		// ����������������������ڵ�������ͬ
		return false;
	}

	int i, j;
	double nInputSum;

	/*�������ز����*/
	for (i = 0; i < m_pHiddenLyr->m_nNeuron; i++)
	{
		nInputSum = 0;
		for (j = 0; j < m_pHiddenLyr->m_pNeurons[i].m_nInput - 1;j++)
		{
			nInputSum += m_pHiddenLyr->m_pNeurons[i].m_pWeights[j] * input[j];
		}
		/*���Ͻؾ�*/
		nInputSum += m_pHiddenLyr->m_pNeurons[i].m_pWeights[j] * BIAS;
		/*���㼤���*/
		m_pHiddenLyr->m_pNeurons[i].m_dActivation = SigmoidActive(nInputSum);
	}

	/*������������*/
	for (i = 0; i < m_pOutputLyr->m_nNeuron;i++)
	{
		nInputSum = 0;
		for (j = 0; j < m_pOutputLyr->m_pNeurons[i].m_nInput - 1;j++)
		{
			nInputSum += m_pOutputLyr->m_pNeurons[i].m_pWeights[j] * m_pHiddenLyr->m_pNeurons[j].m_dActivation;
		}
		/*���Ͻؾ�*/
		nInputSum += m_pOutputLyr->m_pNeurons[i].m_pWeights[j] * BIAS;
		/*���㼤���*/
		m_pOutputLyr->m_pNeurons[i].m_dActivation = SigmoidActive(nInputSum);
		/*ѹ���������*/
		output.push_back(m_pOutputLyr->m_pNeurons[i].m_dActivation);
	}

	return true;
}

bool NeuralNet::TrainingEpoch(vector<iovector> &SetIn, vector<iovector> &SetOut, double learningRate)
{
	int i, j, k;
	double weightUpdate;
	double err;

	/*����ݶ��½��㷨*/
	m_dErrorSum = 0;
	for (i = 0; i < SetIn.size(); i++)
	{
		iovector vecOutput;
		if (!CalculateOutput(SetIn[i],vecOutput))
		{
			return false;
		}

		/*���������Ȩֵ*/
		for (j = 0; j < m_pOutputLyr->m_nNeuron;j++)
		{
			/*���������*/
			err = ((double)SetOut[i][j] - vecOutput[j])*(1 - vecOutput[j])*vecOutput[j];
			m_pOutputLyr->m_pNeurons[j].m_dError = err;

			/*���������ֵ*/
			m_dErrorSum += ((double)SetOut[i][j] - vecOutput[j]) * ((double)SetOut[i][j] - vecOutput[j]);

			/*��������Ȩֵ*/
			for (k = 0; k < m_pOutputLyr->m_pNeurons[j].m_nInput -1;k++)
			{
				weightUpdate = err * learningRate * m_pHiddenLyr->m_pNeurons[k].m_dActivation;
#ifdef NEED_MOMENTUM
				m_pOutputLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate + MOMENTUM *
					m_pOutputLyr->m_pNeurons[j].m_pPrevWeights[k];

				m_pOutputLyr->m_pNeurons[j].m_pPrevWeights[k] = weightUpdate;
#else
				m_pOutputLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate;
					
#endif // NEED_MOMENTUM

			}

			/*���½ؾ�*/
			weightUpdate = err * learningRate * BIAS;
#ifdef NEED_MOMENTUM
			m_pOutputLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate + MOMENTUM *
				m_pOutputLyr->m_pNeurons[j].m_pPrevWeights[k];

			m_pOutputLyr->m_pNeurons[j].m_pPrevWeights[k] = weightUpdate;
#else
			m_pOutputLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate;
#endif // NEED_MOMENTUM

		}// for each output layer

		/*�������ز�Ȩֵ*/
		for (j = 0; j < m_pHiddenLyr->m_nNeuron;j++)
		{
			/*���������*/
			err = 0;
			for (k = 0; k < m_pOutputLyr->m_nNeuron;k++)
			{
				err += m_pOutputLyr->m_pNeurons[k].m_pWeights[j] *
					m_pOutputLyr->m_pNeurons[k].m_dError;
			}
			err *= m_pHiddenLyr->m_pNeurons[j].m_dActivation *
				(1 - m_pHiddenLyr->m_pNeurons[j].m_dActivation);
			m_pHiddenLyr->m_pNeurons[j].m_dError = err;                // ��¼���ز����

			/*�������ز�Ȩֵ*/
			for (k = 0; k < m_pHiddenLyr->m_pNeurons[j].m_nInput-1;k++)
			{
				weightUpdate = err * learningRate * SetIn[i][k];
#ifdef NEED_MOMENTUM
				m_pHiddenLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate + MOMENTUM *
					m_pHiddenLyr->m_pNeurons[j].m_pPrevWeights[k];
				m_pHiddenLyr->m_pNeurons[j].m_pPrevWeights[k] = weightUpdate;
#else
				m_pHiddenLyr->m_pNeurons[j].m_pWeights[j] += weightUpdate;
#endif // NEED_MOMENTUM
			}

			/*���½ؾ�*/
			weightUpdate = learningRate * err * BIAS;
#ifdef NEED_MOMENTUM
			m_pHiddenLyr->m_pNeurons[j].m_pWeights[k] += weightUpdate + MOMENTUM *
				m_pHiddenLyr->m_pNeurons[j].m_pPrevWeights[k];
			m_pHiddenLyr->m_pNeurons[j].m_pPrevWeights[k] = weightUpdate;
#else
			/*����ƫ��*/
			m_pHiddenLyr->m_pNeurons[j].m_pWeights[j] += weightUpdate;
#endif // NEED_MOMENTUM
		}// for each hidden layer
	}// ÿ�ε���

	return true;
}