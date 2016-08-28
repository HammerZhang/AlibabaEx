#ifndef _NEURONODE_H
#define _NEURONODE_H

#define NEED_MOMENTUM                              // 如果需要冲量项

#define MOMENTUM 0.6                               // 冲量项权值

typedef double WEIGHT;                             // 定义权值类型

struct SNeuron
{
	/*********data************/
	int m_nInput;                                  // 输入数量
	WEIGHT *m_pWeights;                            // 输入权值数组
#ifdef NEED_MOMENTUM
	WEIGHT *m_pPrevWeights;                        // 前一次更新的权值数组
#endif // NEED_MOMENTUM
	double m_dActivation;                          // Sigmoid函数输出结果
	double m_dError;                               // 输出结果与标准结果误差

	/**********functions********/
	void Init(int nInput)
	{
		m_nInput = nInput + 1;                     // 其中最后一个数是截距               
		m_pWeights = new WEIGHT[m_nInput];        
#ifdef NEED_MOMENTUM
		m_pPrevWeights = new WEIGHT[m_nInput];
#endif // NEED_MOMENTUM
		m_dActivation = 0;
		m_dError = 0;
	}

	~SNeuron()
	{
		// 释放空间
		delete[] m_pWeights;
#ifdef NEED_MOMENTUM
		delete[] m_pPrevWeights;
#endif // NEED_MOMENTUM
	}
};

struct SNeuronLayer
{
	/***********Data*************/
	int m_nNeuron;                          // 该层节点数
	SNeuron *m_pNeurons;                    // 节点数组

	/**********Function************/
	SNeuronLayer(int nNeuron, int nInputPerNeuron)
	{
		m_nNeuron = nNeuron;
		m_pNeurons = new SNeuron[nNeuron];                // 分配空间

		for (int i = 0; i < nNeuron; i++)
		{
			m_pNeurons[i].Init(nInputPerNeuron);
		}
	}

	~SNeuronLayer()
	{ 
		// 释放空间 
		delete[] m_pNeurons;
	}
};

#endif