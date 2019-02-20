#include "HuffmanTree.hpp"

struct CharInfo
{
   char _ch;
   long long _count;
   string _code;
   CharInfo(long long count = 0)
     :_count(count)
   {}
   bool operator != (const CharInfo& info)
   {
     return _count != info._count;
   }
   bool operator > (const CharInfo& info)const 
   {
     return _count > info._count;
   }
	 CharInfo operator+(const CharInfo& info)
   {
     return _count+info._count;
   }
};

typedef HuffmanTreeNode<CharInfo> Node;
#include <algorithm>
class FileCompress
{
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_Info[i]._ch = i;
			_Info[i]._count = 0;
		}
	}

	string Compress(const char* filename)
	{
		FILE* fout = fopen(filename, "rb");
		assert(fout);
		//统计每个字符出现的次数
		char ch = fgetc(fout);
		while (!feof(fout))
		{
			_Info[ch]._count++;
			ch = fgetc(fout);
		}
		//创建
		CharInfo invalid;
		invalid._count = 0;
		HuffmanTree<CharInfo>hp(_Info, 256, invalid);

		//得到哈夫曼编码
		_GetHuffmanCode(hp.GetRoot());

		//压缩
		string compressfile = filename;
		size_t index = compressfile.rfind('.');
		compressfile = compressfile.substr(0, index);
		compressfile += ".hzp";
		FILE* fin = fopen(compressfile.c_str(), "wb");
		assert(fin);
		fseek(fout, 0, SEEK_SET);//设置文件指针指向文件开头

		int pos = 0;
		int value = 0;
		unsigned char c = fgetc(fout);
		//char buf[1024] = { 0 };
		while (!feof(fout))
		{
			//size_t rdSize = fread(buf, sizeof(char), 1024, fout);
			string code = _Info[c]._code;
			for (size_t i = 0; i < code.size(); i++)
			{
				value <<= 1;
				if (code[i] == '1')
					value |= 1;
				else
					value |= 0;
				++pos;
				if (pos == 8)
				{
					fputc(value, fin);
					pos = 0;
					value = 0;
				}
			}
			c = fgetc(fout);
		}
		if (pos != 0)
		{
			value <<= (8 - pos);
			fputc(value, fin);
		}
		fclose(fin);
		fclose(fout);

		//配置文件
		string configfilename = filename;
		size_t index2 = configfilename.rfind('.');
		configfilename = configfilename.substr(0, index2);
		configfilename += ".config";
		FILE* foutconfig = fopen(configfilename.c_str(), "wb");
		string line;
		char buf[128];
		for (int i = 0; i < 256; i++)
		{
			if (_Info[i]._count)
			{
				line += _Info[i]._ch;
				line += ',';
				line += _itoa(_Info[i]._count, buf, 10);
				line += '\n';
				fputs(line.c_str(), foutconfig);
				line.clear();
			}
		}
		fclose(foutconfig);
		return compressfile;
	}

	void UNCompree(const char* filename)
	{

	}

	void _GetHuffmanCode(Node* root)
	{
		if (root)
		{
			_GetHuffmanCode(root->_left);
			_GetHuffmanCode(root->_right);
			if (nullptr == root->_left && nullptr == root->_right)
			{
				HuffmanTreeNode<CharInfo> *cur = root;
				HuffmanTreeNode<CharInfo> *parent = root->_parent;

				vector<char> strCode;
				string str;
				while (parent)
				{
					if (parent->_left == cur)
					{
						strCode.push_back('0');
					}
					if (parent->_right == cur)
					{
						strCode.push_back('1');
					}
					cur = parent;
					parent = parent->_parent;
				}
				reverse(strCode.begin(),strCode.end());
				vectorTostring(strCode, str);
				_Info[root->_weight._ch]._code = str;
			}
		}
	}

	string& vectorTostring(vector<char>& vec, string& str)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			str.push_back(vec[i]);
		}
		return str;
	}
private:
	CharInfo _Info[256];
};
   {
     return _count + info._count; 
   }
};
