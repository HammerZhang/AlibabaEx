// AlibabaEx2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string.h>


struct CharSequence
{
	char seq[50];
	int num;

	CharSequence()
	{
		memset(this->seq,0,sizeof(this->seq));
		this->num = 0;
	}

	void AddChar(char a)
	{
		*(seq+num) = a;
		num++;
	}

	void DeleteSeq()
	{
		memset(this->seq, 0, sizeof(this->seq));
		this->num = 0;
	}
};

template <class T>
int getArrayLen(T& arr)
{
	return (sizeof(arr) / sizeof(arr[0]));
}

/*
* find the longest common part between two strings
* @param char* str1, char* str2 are the two strings
* @return a CharSequence struct which contain the longest common part and the length
*/
CharSequence* FindLongest(char str1[], char str2[])
{
	CharSequence* seq = new CharSequence();
	CharSequence* tmpSeq = new CharSequence();

	// find which string is shorter and the length
	int len1 = strlen(str1) / sizeof(char);
	int len2 = strlen(str2) / sizeof(char);

	for (int i = 0; i < len1; i++)
	{
		int k = 0;
		for (int j = 0; j < len2; j++)
		{
			if (*(str1 + i + k) == *(str2 + j))
			{
				tmpSeq->AddChar(*(str1 + i + k));
				k++;
			}
			else
			{
				if (tmpSeq->num > seq->num)
				{
					seq->DeleteSeq();
					strcpy(seq->seq, tmpSeq->seq);
					seq->num = tmpSeq->num;
				}

				tmpSeq->DeleteSeq();
				k = 0;
			}
		}
	}

	return seq;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char* str1 = "I am HammerZhang";
	char* str2 = "My name is HammerZhang";
	CharSequence* seq = FindLongest(str1, str2);
	return 0;
}

