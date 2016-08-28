// OperateOnNeuralNet: OperateOnNN类的实现
//
//////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OperateOnNeuralNet.h"
#include <assert.h>

OperateOnNN::OperateOnNN()
{
	m_nInput = 0;
	m_nOutput = 0;
	m_nNeuronsPerLyr = 0;
	m_nHiddenLyr = 0;

	m_nMaxEpoch = 0;
	m_dMinError = 0.0;
	m_dLearningRate = 0.0;

	m_oNetwork = 0;

	m_nEpochs = 0;
	m_dError = 0.0;
	m_bStop = false;
}

OperateOnNN::~OperateOnNN()
{
	if (m_oNetwork)
	{
		delete m_oNetwork;
	}
}

void OperateOnNN::SetNetworkPara(int nInput, int nOutput, int nNeuronsPerLyr, int nHiddenLyr)
{
	assert(nInput > 0 && nOutput > 0 && nNeuronsPerLyr > 0 && nHiddenLyr > 0);
	m_nInput = nInput;
	m_nOutput = nOutput;
	m_nNeuronsPerLyr = nNeuronsPerLyr;
	m_nHiddenLyr = nHiddenLyr;
}

bool OperateOnNN::CreateNetwork()
{
	assert(m_nInput > 0 && m_nOutput > 0 && m_nNeuronsPerLyr > 0 && m_nHiddenLyr > 0);
	m_oNetwork = new NeuralNet(m_nInput, m_nOutput, m_nNeuronsPerLyr, m_nHiddenLyr);
	if (m_oNetwork)
		return true;
	else
		return false;
}

void OperateOnNN::SetTrainConfig(int nMaxEpoch, double dMinError, double dLearningRate)
{
	assert(nMaxEpoch > 0 && !(dMinError < 0) && dLearningRate != 0);
	m_nMaxEpoch = nMaxEpoch;
	m_dMinError = dMinError;
	m_dLearningRate = dLearningRate;
}

bool OperateOnNN::Train(vector<iovector> &SetIn, vector<iovector> &SetOut)
{
	m_bStop = false;                     // 不停止训练
	char *outMsg;

	do 
	{
		/*迭代*/
		if (!m_oNetwork->TrainingEpoch(SetIn,SetOut,m_dLearningRate))
		{
			outMsg = "Error occured in training epoch\n";
		}
		else
		{
			m_nEpochs++;
		}

		/*计算每次迭代误差平均值*/
		int sum = m_oNetwork->GetErrorSum();
		m_dError = m_oNetwork->GetErrorSum() / (m_nOutput * SetIn.size());
		m_vecError.push_back(m_dError);
		if (m_dError < m_dMinError)
		{
			break;
		}

		if (m_bStop)
		{
			break;
		}
	} while (--m_nMaxEpoch > 0);

	return true;
}