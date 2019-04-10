#include "HuffmanTree.hpp"

struct CharInfo
{
	unsigned char _ch;
	long long _count;
	string _code;

	CharInfo(long long count = 0)
		:_count(count)
	{}

	bool operator != (const CharInfo& info)const
	{
		return _count != info._count;
	}

	bool operator == (const CharInfo& info)const
	{
		return _count == info._count;
	}
	bool operator > (const CharInfo& info)const
	{
		return _count > info._count;
	}

	CharInfo operator + (const CharInfo& info)
	{
		return CharInfo(_count + info._count);
	}
};


typedef HuffmanTreeNode<CharInfo> Node;

class FileCompress
{
public:
	FileCompress()
	{
		_Info.resize(256);
		for (size_t i = 0; i < 256; ++i)
		{
			_Info[i]._ch = i;
			_Info[i]._count = 0;
		}
	}

	static void ReadLine(FILE* fIn, string &line)
	{
		while (!feof(fIn))
		{
			char ch = fgetc(fIn);
			if ('\n' == ch)
				return;

			line += ch;
		}
	}

	void WriteHead(FILE* fOut, const string& strFilePath)
	{
		string strInfo;
		strInfo = strFilePath.substr(strFilePath.rfind('.'));
		strInfo += '\n';
		string str;
		char szCount[32];
		size_t lineCount = 0;
		for (size_t i = 0; i < 256; ++i)
		{
			if (_Info[i]._count)
			{
				str += _Info[i]._ch;
				str += ',';
				_itoa(_Info[i]._count, szCount, 10);//
				str += szCount;
				str += '\n';
				lineCount++;
			}
		}
		_itoa(lineCount, szCount, 10);
		strInfo += szCount;
		strInfo += '\n';

		strInfo += str;
		fwrite(strInfo.c_str(), 1, strInfo.size(), fOut);
	}

  void Compress(const char* filename)
	{
		FILE* fIn = fopen(filename, "rb");
		assert(fIn);
		//统计每个字符出现的次数
		unsigned char* pReadBuff = new unsigned char[1024];
		while (1)
		{
			size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
			if (0 == rdSize)
				break;

			for (size_t i = 0; i < rdSize; ++i)
			{
				_Info[pReadBuff[i]]._count++;
			}
		}
		//每个字符出现的次数创建huffman树
		HuffmanTree<CharInfo> ht;
		ht._CreateHuffmanTree(_Info,CharInfo(0));
		//根据huffman树获取每个字符的编码
		_GetHuffmanCode(ht.GetRoot());

		//根据每个字符的编码重写源文件
		FILE* fOut = fopen("1.hzp", "wb");
		assert(fOut);

		WriteHead(fOut, filename);//
		char ch = 0;
		int bitCount = 0;
		fseek(fIn,0, SEEK_SET);//设置文件指针
		while (true)
		{
			size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
			if (0 == rdSize)
				break;

			for (size_t i = 0; i < rdSize; ++i)
			{
				string& strCode = _Info[pReadBuff[i]]._code;
				for (size_t j = 0; j < strCode.size(); ++j)
				{
					ch <<= 1;
					if ('1' == strCode[j])
						ch |= 1;
					
					bitCount++;
					if (bitCount == 8)
					{
						fputc(ch,fOut);
						bitCount = 0;
					}
				}
			}
		}
		if (bitCount >0 && bitCount < 8)
		{
			ch <<= (8 - bitCount);
			fputc(ch, fOut);
		}
		delete[] pReadBuff;
		fclose(fIn);
		fclose(fOut);
	}

	void UNCompreess(const string& filename)
	{
		string strPostFix = filename.substr(filename.rfind('.'));
		if (".hzp" != strPostFix)
		{
			cout << "压缩文件的格式有问题" << endl;
			return;
		}
		//获取解压缩的信息
		FILE* fIn = fopen(filename.c_str(), "rb");
		if (nullptr == fIn)
		{
			cout << "压缩文件打开失败" << endl;
			return;
		}
		strPostFix = "";
		ReadLine(fIn, strPostFix);
		string strContent;
		ReadLine(fIn, strContent);
		size_t lineCount = atoi(strContent.c_str());

		for (size_t i = 0; i < lineCount; ++i)
		{
			strContent = "";
			ReadLine(fIn, strContent);
			if (strContent.empty())//处理换行符
			{
				strContent += '\n';
				ReadLine(fIn, strContent);
			}
			_Info[(unsigned char)strContent[0]]._count = atoi(strContent.c_str() + 2);
		}
		HuffmanTree<CharInfo>ht;
		ht._CreateHuffmanTree(_Info, CharInfo(0));

		string strUncompressfile = "2";
		strUncompressfile += strPostFix;
		FILE* fOut = fopen(strUncompressfile.c_str(), "wb");
		assert(fOut);
		unsigned char* readBuff = new unsigned char[1024];
		HuffmanTreeNode<CharInfo>* cur = ht.GetRoot();
		char pos = 7;
		size_t fileSize = cur->_weight._count;
		while (true)
		{
			size_t rdSize = fread(readBuff, 1, 1024, fIn);
			if (0 == rdSize)
				break; 

			for (size_t i = 0;i <rdSize; ++i)
			{
				pos = 7;
				for (size_t j = 0; j < 8; ++j)
				{
					if (readBuff[j] & (1 < pos))
					{
						cur = cur->_right;
					}
					else
					{
						cur = cur->_left;
					}
					if (nullptr == cur->_left && nullptr == cur->_right)
					{
						fputc(cur->_weight._ch, fOut);
						cur = ht.GetRoot();

						/*fileSize--;
						if (fileSize == 0)
							break;*/
					}
					pos--;
				}
			}
		}
		delete[] readBuff;
		fclose(fIn);
		fclose(fOut);
	}

	void _GetHuffmanCode(HuffmanTreeNode<CharInfo>* root)
	{
		if (root)
		{
			_GetHuffmanCode(root->_left);
			_GetHuffmanCode(root->_right);
			if (nullptr == root->_left && nullptr == root->_right)
			{
				HuffmanTreeNode<CharInfo> *cur = root;
				HuffmanTreeNode<CharInfo> *parent = root->_parent;

				string& str = _Info[cur->_weight._ch]._code;
				while (parent)
				{
					if (parent->_left == cur)
					{
						str += '0';
					}
					if (parent->_right == cur)
					{
						str += '1';
					}
					cur = parent;
					parent = parent->_parent;
				}
				reverse(str.begin(),str.end());
			}
		}
	}

	static string& vectorTostring(vector<char>& vec, string& str)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			str.push_back(vec[i]);
		}
		return str;
	}

private:
	vector<CharInfo> _Info;
};
