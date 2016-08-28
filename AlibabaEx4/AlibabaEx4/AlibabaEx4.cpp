// AlibabaEx4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <iostream>


/*
* display an array
* @param: arr: the array to display, len: length of array
*/
void DisplayArry(int* arr, int len);

/*
* find the maximum interaction between prefix and postfix
* @param str: the target string, next: number of interaction
*/
void MakeNext(char *str, int* next)
{
	int len = strlen(str);
	next = new int[len];

	*next = 0;
	int k = 0;
	for (int i = 1; i < len;i++)
	{
		if (*(str + k) == *(str + i))
		{
			k++;
		}
		else
		{
			if (k > 0)
			{
				if (*(str + i) == *(str))
				{
					k = 1;
				}
				else
				{
					int j = 1;
					while (j < k)
					{
						if (*(str + i) == *(str + j))
							break;
						j++;
					}

					if (j < k)
					{
						k = j + 1;
						for (int ii = 0; ii < j; ii++)
						{
							if (*(str + i - j + ii) != *(str + ii))
							{
								k = 0;
								break;
							}
						}
					}
					else
					{
						k = 0;
					}
				}
			}
		}

		*(next + i) = k;
	}

	DisplayArry(next, len);
}


void DisplayArry(int* arr, int len)
{
	for (int i = 0; i < len;i++)
	{
		std::cout << *(arr + i) << "  ";
	}
	std::cout << "\n";
}

/*
* Search a target string in a long string with KMP algorithm
* @param longStr: long string in which to search, targetStr: target string
* @return the start position of target string in long string
*/
int KMPStrSearch(char* longStr, char* targetStr)
{
	int len1 = strlen(longStr);
	int len2 = strlen(targetStr);
	int* next = { 0 };
	MakeNext(targetStr, next);

	int i = 0;
	while (i < len1)
	{
		if (*(longStr + i) == *(targetStr))
		{
			int j = 1;
			while (*(longStr + i + j) == *(targetStr + j))
			{
				if (j < len2)
					j++;
				else
					return i;
			}
			i = i + (j - *(next + j));
		}
		else
		{
			i++;
		}
	}

	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char* longStr = "BBC ABCDAB ABCDABCDABDE";
	char* str = "ABCDABD";
	int* next = {0};
	int pos = KMPStrSearch(longStr, str);

	return 0;
}

