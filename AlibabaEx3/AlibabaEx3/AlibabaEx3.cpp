// AlibabaEx3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
* A simple method to count number of one in a binary data
* @ n: the number waiting for operation
* @return: number of one
*/
int BitOneCount1(int n)
{
	int c;
	for (c = 0; n; n >>= 1)
	{
		c += (n & 1);
	}
	return c;
}

/*
* A simple method to count the number of ones in a binary data, maximum
* loop number is the number of ones in the binary data
* @ n: the number waiting for operation
* @return: number of ones in the number
*/
int BitOneCount2(int n)
{
	int c = 0;
	while (n)
	{
		n &= (n - 1);
		c++;
	}
	return c;
}

/*
* Table search method to count the number of ones in a binary data
* @n: the number waiting for operation
* @return: number of ones in the number
*/
int BitOneCount3(unsigned int n)
{
	// Build the table
	unsigned int BitSetTable[256] = { 0 };
	
	// Initialize the table
	for (int i = 0; i < 256; i++)
	{
		BitSetTable[i] = (i & 1) + BitSetTable[i / 2];
	}

	// search the table
	unsigned char* p = (unsigned char*)&n;

	int c = BitSetTable[p[0]] + BitSetTable[p[1]]
		+ BitSetTable[p[2]] + BitSetTable[p[3]];

	return c;
}

/*
* shifting algorithm to count the number of ones in a binary data
* @ n: input number
* @ return: the number of ones
*/
int BitOneCount4(unsigned n)
{
	// Build the table
	unsigned int BitSetTable[256] = { 0 };

	// Initialize the table
	for (int i = 0; i < 256; i++)
	{
		BitSetTable[i] = (i & 1) + BitSetTable[i / 2];
	}

	int c = BitSetTable[n & 0xFF] + BitSetTable[(n >> 8) & 0xFF]
		+ BitSetTable[(n >> 16) & 0xFF] + BitSetTable[(n >> 24) & 0xFF];

	return c;
}


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int n = 25176;

	int c = BitOneCount4(n);

	return 0;
}

