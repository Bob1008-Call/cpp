#pragma once 
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sys/time.h>
#include <boost/algorithm/string.hpp>
using namespace std;

//准备一个时间戳获取工具

class TimeUtil
{
public:
  static int64_t TimeStamp()
  {
    struct timeval tv;
    ::gettimeofday(&tv,NULL);
    return tv.tv_sec;
  }

  static int64_t TimeStampMS()
  {
    struct timeval tv;
    ::gettimeofday(&tv,NULL);
    return tv.tv_sec*1000 + tv.tv_usec/1000;
  }
};

//[I1550892581 util.hpp:31] hello
//[W1550892581 util.hpp:31] hello
//[E1550892581 util.hpp:31] hello
//[F1550892581 util.hpp:31] hello
//日志的使用方式
//LOG(INFO)<<"hello"<<"\n";
enum Level
{
  INFO,
  WARNING,
  ERROR,
  FATAL,
};

inline ostream& Log(Level level,
    const string& file_name,int line_num)
{
  string prefix = "[";
  if(level == INFO)
  {
    prefix += "I";
  }
  else if(level == WARNING)
  {
    prefix += "W";
  }
  else if(level == ERROR)
  {
    prefix += "E";
  }
  else if(level == FATAL)
  {
    prefix += "F";
  }
  prefix += to_string(TimeUtil::TimeStamp());
  prefix += " ";
  prefix += file_name;
  prefix += ":";
  prefix += to_string(line_num);
  prefix += "] ";
  cout<<prefix;
  return cout;
}

#define LOG(level) Log(level,__FILE__,__LINE__)

class FileUtil
{
public:
  //输入一个文件路径，把内容读出来放到content字符串中
  static bool Read(const string& file_path,
      string* content)
  {
    content->clear();
    ifstream file(file_path.c_str());
    if(!file.is_open())
    {
      return false;
    }
    string line;
    while(getline(file,line))
    {
      *content += line + "\n";//读出来去掉\n 需手动添加
    }
    file.close();
    return true;
  }

  static bool Write(const string& file_path,
      const string& content)
  {
    ofstream file(file_path.c_str());
    if(!file.is_open())
    {
      return false;
    }
    file.write(content.c_str(),content.size());
    file.close();
    return true;
  } 
};
//URL body 解析模块
class StringUtil 
{
public:
   static void Split(const string& input,const string& split_char,vector<string>* output)
  {
    boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);//off 就是4 on 3
  }
};

//1.boost split
class UrlUtil
{
public:
  static void ParseBody(const string& body,
      unordered_map<string,string>* params)
  {
    //1.先对这里的body字符串进行切分，切分为键值对
    // a）先按照&符号切分
    // b）再按照 = 切分
    vector<string> kvs;
    StringUtil::Split(body,"&",&kvs);
    for(size_t i = 0;i < kvs.size(); ++i)
    {
      vector<string> kv;
      StringUtil::Split(kvs[i], "=", &kv);
      if(kv.size() != 2)
      {
        continue;
      }
      //2.对这里的键值对进行urldecode
      (*params)[kv[0]] = UrlDecode(kv[1]);//给key取value
    }
  }
  static unsigned char ToHex(unsigned char x) 
  { 
    return  x > 9 ? x + 55 : x + 48; 
  }

	static unsigned char FromHex(unsigned char x) 
	{ 
		unsigned char y;
		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';
		else assert(0);
		return y;
	}

	static string UrlEncode(const string& str)
	{
		string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) || 
					(str[i] == '-') ||
					(str[i] == '_') || 
					(str[i] == '.') || 
					(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}
		return strTemp;
	}

	static string UrlDecode(const string& str)
	{
		string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%')
			{
				assert(i + 2 < length);
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high*16 + low;
			}
			else strTemp += str[i];
		}
		return strTemp;
	}
};

