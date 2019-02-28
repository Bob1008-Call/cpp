#include <stdio.h>
void PrintCircle(int** array,int row,int col,int start)
{
	int endCol = col - 1 - start;
	int endRow = row - 1 - start;
	for (int i = start; i <= endCol; ++i)
	{
		printf("%d ", array[start][i]);
	}
	if (start < endRow)
	{
		for (int i = start + 1; i < endRow; ++i)
		{
			printf("%d ", array[i][endCol]);
		}
	}
	if (start < endRow && start < endCol)
	{
		for (int i = endCol - 1; i >= start; --i)
		{
			printf("%d ", array[endRow][i]);
		}
	}
	if (start < endRow - 1 && start < endCol)
	{
		for (int i = endRow - 1; i>start; --i)
		{
			printf("%d", array[i][start]);
		}
	}
}
void PrintMatrix(int** array,int row,int col)
{
	if (NULL == array || row <= 0 || col <= 0)
		return;
	int start = 0;
	while (col>start*2 && row>start*2)
	{
		PrintCircle(array, row, col, start);
		++start;
	}
}









