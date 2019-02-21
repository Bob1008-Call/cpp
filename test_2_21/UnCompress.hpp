nclude "HuffmanTree.hpp"

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

	CharInfo operator + (const CharInfo& info)
	{
		return _count + info._count;
	}
};


typedef HuffmanTreeNode<CharInfo> Node;

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

	bool ReadLine(FILE* configfile, string &line)
	{
		char ch = fgetc(configfile);
		if (ch == EOF)
		{
			return false;
		}
		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(configfile);
		}
		return true;
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

		////压缩
		//string compressfile = filename;
		//size_t index = compressfile.rfind('.');
		//compressfile = compressfile.substr(0, index);
		//compressfile += ".hzp";
		//FILE* fin = fopen(compressfile.c_str(), "wb");
		//assert(fin);
		//fseek(fout, 0, SEEK_SET);//设置文件指针指向文件开头
		string compressfile = filename;
		string str = filename;
		size_t index1 = str.rfind('.');

		size_t index = compressfile.rfind('.');
		compressfile = compressfile.substr(0, index);
		compressfile += ".hzp";
		FILE* fin = fopen(compressfile.c_str(), "wb");
		assert(fin);
		fputs(str.substr(index1).c_str(), fin);
		//fclose(fout);

	    char str11 = '\n';
		fputc(str11, fin);

		string line;
		char buf[128];
		int count = 0;
		for (int i = 0; i < 256; i++)
		{
			if (_Info[i]._count)
			{
				count++;
			}
		}
		fputc(count+'0', fin);
		char str12 = '\n';
		fputc(str12, fin);

		for (int i = 0; i < 256; i++)
		{
			if (_Info[i]._count)
			{
				line += _Info[i]._ch;
				line += ',';
				line += _itoa(_Info[i]._count, buf, 10);
				line += '\n';
				fputs(line.c_str(), fin);
				line.clear();
			}
		}

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
		return compressfile;
	}

	string UNCompreess(const char* filename)
	{
		string uncompressfile = filename;
		FILE* fout = fopen(filename, "rb");
		assert(fout);

		size_t index = uncompressfile.rfind('.');
		uncompressfile = uncompressfile.substr(0, index);
		string line;
		unsigned char ch = fgetc(fout);
		while (ch != '\n')
		{			
			line.push_back(ch);
			ch = fgetc(fout);
		}
		uncompressfile += line;

		string line1;
		ch = fgetc(fout);
		while (ch != '\n')
		{
			line1.push_back(ch);
			ch = fgetc(fout);
		}
		int count = atoi(line1.c_str());

		string line2;
		unsigned char ch1 = 0;
		while (count)
		{
			while (ReadLine(fout, line2))
			{
				if (line2.empty())
				{
					line2 += '\n';
					continue;
				}
				else
				{
					ch1 = line2[0];
					_Info[ch1]._count = atoi(line2.substr(2).c_str());
					line2.clear();
				}
			}
			count--;
		}
		
		CharInfo invalid;
		HuffmanTree<CharInfo> hp(_Info, 256, invalid);
		long long int charCount = hp.GetRoot()->_weight._count;
		FILE* fin = fopen(uncompressfile.c_str(), "wb");
		assert(fin);
		int pos = 7;
		unsigned char c = fgetc(fout);
		HuffmanTreeNode<CharInfo>* root = hp.GetRoot();
		HuffmanTreeNode<CharInfo>* cur = root;
		//while (charCount && ch != EOF)
		while (charCount && !feof(fout))
		{
			//到叶子节点说明找到字符，放入解压文件
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fout);
				charCount--;
				cur = root;
			}
			//如果不是叶子结点就找叶子节点，0向左走，1向右走
			if (c & (1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			pos--;
			//当pos<0时，说明此时已经解压完一个字节，开始解压下一个字节
			if (pos < 0)
			{
				pos = 7;
				c = fgetc(fout);
			}
			//当charCount == 0时，字符已经全部解压完
			if (charCount == 0)
				break;
		}
		return uncompressfile.c_str();

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
//
//GetHuffmanCode();
//GetLine(); 
//WriteHead(); 
//UNCompressFile();
//CompressFile();
