#define _CRT_SECURE_NO_WARNINGS
#include "FileCompress.hpp"
#include "HuffmanTree.hpp"

int main()
{
	FileCompress filecompress;
	filecompress.Compress("1.txt");
	filecompress.UNCompreess("1.hzp");
	return 0;
}
