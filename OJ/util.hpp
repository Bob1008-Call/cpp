#pragma once 
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/time.h>

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

#define Log(level) Log(level,__FILE__,__LINE__)

