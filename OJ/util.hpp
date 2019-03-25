#pragma once 
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sys/time.h>
#include <boost>

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

inline std::ostream& Log(Level level,
    const std::string& file_name,int line_num)
{
  std::string prefix = "[";
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
  prefix += std::to_string(TimeUtil::TimeStamp());
  prefix += " ";
  prefix += file_name;
  prefix += ":";
  prefix += std::to_string(line_num);
  prefix += "] ";
  std::cout<<prefix;
  return std::cout;
}

#define LOG(level) Log(level,__FILE__,__LINE__)

class FileUtil
{
public:
  //输入一个文件路径，把内容读出来放到content字符串中
  static bool Read(const std::string& file_path,
      std::string* content)
  {
    content->clear();
    std::ifstream file(file_path.c_str());
    if(!file.is_open())
    {
      return false;
    }
    std::string line;
    while(std::getline(file,line))
    {
      *content += line + "\n";//读出来去掉\n 需手动添加
    }
    file.close();
    return true;
  }

  static bool Write(const std::string& file_path,
      const std::string& content)
  {
    std::ofstream file(file_path.c_str());
    if(!file.is_open())
    {
      return false;
    }
    file.write(content.c_str(),content.size());
    file.close();
    return true;
  } 
};

class UrlUtil
{
public:
  static void ParseBody(const std::string& body,
      std::unordered_map<std::string,std::string>* params)
  {
    //1.先对这里的body字符串进行切分，切分为键值对
    // a）先按照&符号切分
    // b）再按照 = 切分
    //2.对这里的键值对进行urldecode
  }
};

class StringUtil 
{
public:
  void Split(const std::string& input,const std::string& split_char,std::vector<std::string>* output)
  {
    
  }
};
