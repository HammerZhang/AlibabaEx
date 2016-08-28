#ifndef _NEURONODE_H
#define _NEURONODE_H

#define NEED_MOMENTUM                              // �����Ҫ������

#define MOMENTUM 0.6                               // ������Ȩֵ

typedef double WEIGHT;                             // ����Ȩֵ����

struct SNeuron
{
	/*********data************/
	int m_nInput;                                  // ��������
	WEIGHT *m_pWeights;                            // ����Ȩֵ����
#ifdef NEED_MOMENTUM
	WEIGHT *m_pPrevWeights;                        // ǰһ�θ��µ�Ȩֵ����
#endif // NEED_MOMENTUM
	double m_dActivation;                          // Sigmoid����������
	double m_dError;                               // ���������׼������

	/**********functions********/
	void Init(int nInput)
	{
		m_nInput = nInput + 1;                     // �������һ�����ǽؾ�               
		m_pWeights = new WEIGHT[m_nInput];        
#ifdef NEED_MOMENTUM
		m_pPrevWeights = new WEIGHT[m_nInput];
#endif // NEED_MOMENTUM
		m_dActivation = 0;
		m_dError = 0;
	}

	~SNeuron()
	{
		// �ͷſռ�
		delete[] m_pWeights;
#ifdef NEED_MOMENTUM
		delete[] m_pPrevWeights;
#endif // NEED_MOMENTUM
	}
};

struct SNeuronLayer
{
	/***********Data*************/
	int m_nNeuron;                          // �ò�ڵ���
	SNeuron *m_pNeurons;                    // �ڵ�����

	/**********Function************/
	SNeuronLayer(int nNeuron, int nInputPerNeuron)
	{
		m_nNeuron = nNeuron;
		m_pNeurons = new SNeuron[nNeuron];                // ����ռ�

		for (int i = 0; i < nNeuron; i++)
		{
			m_pNeurons[i].Init(nInputPerNeuron);
		}
	}

	~SNeuronLayer()
	{ 
		// �ͷſռ� 
		delete[] m_pNeurons;
	}
};

#endif