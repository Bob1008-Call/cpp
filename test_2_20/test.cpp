#define _CRT_SECURE_NO_WARNINGS
#include "Compress.hpp"
#include "HuffmanTree.hpp"

int main()
{
	FileCompress filecompress;
	filecompress.Compress("1.txt");
	return 0;
}
