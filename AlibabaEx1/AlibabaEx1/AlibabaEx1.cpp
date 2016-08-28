// AlibabaEx1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
using namespace std;

#define minusInf -1000
typedef int DATA;

//二叉树节点结构体
struct BiTreeNode
{
	DATA data;
	BiTreeNode* lChild;
	BiTreeNode* rChild;
	
	BiTreeNode()
	{
		this->data = minusInf;
		this->lChild = NULL;
		this->rChild = NULL;
	}

	BiTreeNode(DATA d)
	{
		this->data = d;
		this->lChild = NULL;
		this->rChild = NULL;
	}
};

// 队列节点结构体
struct QueueNode
{
	BiTreeNode* treeNode;
	QueueNode* nextNode;

	QueueNode()
	{
		this->treeNode = NULL;
		this->nextNode = NULL;
	}

	QueueNode(BiTreeNode* node)
	{
		this->treeNode = node;
		this->nextNode = NULL;
	}
};

// 全局变量
QueueNode* queueHead = NULL;
QueueNode* queueTail = NULL;

/*
* Initialize queue
*/
void InitQueue()
{
	queueTail = new QueueNode();
	queueHead = queueTail;
}

/*
* find if queue is empty
* @return true or false
*/
bool empty()
{
	if (queueHead == queueTail)
		return true;
	else
		return false;
}

/*
* Judge if a tree node is null
* @param BiTreeNode* node is the input node
* @return true or false
*/
bool isTreeNodeNull(BiTreeNode *node)
{
	if (NULL != node)
	{
		if (minusInf == node->data && NULL == node->lChild
			&& NULL == node->rChild)
			return true;
	}

	return false;
}

/*
* Push tree node into queue
* @param BiTreeNode* pointer of the node that need to push into queue
*/
void PushIntoQueue(BiTreeNode* node)
{
	if (empty()){
		if (NULL == queueHead && NULL == queueTail)
			InitQueue();
	}
	
	QueueNode* newNode = new QueueNode();
	newNode->treeNode = node;
	queueTail->nextNode = newNode;
	queueTail = newNode;
}

/*
* pull out the last node from the queue
* @return the pointer of the last node
*/
QueueNode* PullOutQueue()
{
	QueueNode* pullNode;
	if (!empty())
	{
		pullNode = queueHead->nextNode;
		queueHead = queueHead->nextNode;
	}
	else
	{
		pullNode = NULL;
		cout << "Queue is empty, reutrn a NULL pointer...\n";
	}

	return pullNode;
}



/*
* Construct a BiTree with given array
* @param int* the given array
* @param int the number of tree nodes
* @return BiTreeNode* return root node of the BiTree
*/
BiTreeNode * BuildBiTree(int* arr, int n)
{
	int i = 0;
	BiTreeNode* root = new BiTreeNode();
	PushIntoQueue(root);
	while (!empty())
	{
		QueueNode* queueNode = PullOutQueue();
		BiTreeNode* treeNode = queueNode->treeNode;
		if (i < n)
			treeNode->data = *(arr + i);
		else
			break;
		i++;

		//Push left tree and right tree into queue
		treeNode->lChild = new BiTreeNode();
		treeNode->rChild = new BiTreeNode();
		PushIntoQueue(treeNode->lChild);
		PushIntoQueue(treeNode->rChild);
		
	}
	return root;
}


/*
* find the biggest and smallest value of the BiTree by middle order search the tree
* @param BiTreeNode* root root of the BiTree
*/
void MiddleOrderSearch(BiTreeNode* root, int* value)
{		
	if (!isTreeNodeNull(root->lChild))
		MiddleOrderSearch(root->lChild, value);

	if (*(value) < root->data)
		*value = root->data;
	if (*(value+1) > root->data)
		*(value+1) = root->data;

	if (!isTreeNodeNull(root->rChild))
		MiddleOrderSearch(root->rChild, value);

}


int _tmain(int argc, _TCHAR* argv[])
{
	int arr[10] = { 7, 9,2,7,2,5,26,1075,-4,-27};
	BiTreeNode* root = BuildBiTree(arr,10);
	int value[2];
	value[0] = value[1] = root->data;
	MiddleOrderSearch(root, value);
	cout << "the biggest value is " << value[0]<<"\nthe smallest value is"<<value[1]<<"\n";
	return 0;
}

