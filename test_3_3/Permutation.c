#include <stdio.h>

void Swap(char& x,char& y)
{
	char temp = x;
	x = y;
	y = temp;
}


void Permutation(char* pStr, char* pBegin)
{
	if (*pBegin == '\0')
	{
		printf("%c ",pStr);
	}
	else
	{
		for (char* pCh = pBegin; *pCh != '\0'; ++pCh)
		{
			Swap(pCh, pBegin);
			Permutation(pStr, pBegin + 1);
			Swap(pCh, pBegin);
		}
	}
}

void Permutation(char* pStr)
{
	if (NULL == pStr)
		return;

	Permutation(pStr, pStr);
}
int main()
{
	char c[] = "abc";
	Permutation(c);
	return 0;
}

