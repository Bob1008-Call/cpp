#pragma once 
#include <string>
#include <atomic>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <jsoncpp/json/json.h>
#include "util.hpp"
using namespace std;
//完成在线编译模块
//提供一个 Compiler 类，提供一个核心的CompileAndRun

class Compiler
{
public:

  //形如tmp_1553408103.1.cpp
  //1.源代码文件
  static string SrcPath(const string& name)
  {
    return "./temp_files/" + name + ".cpp";
  }
  //2.编译错误文件
  static string CompileErrorPath(const string& name)
  {
    return "./temp_files/" + name + ".compile_error";
  }
  //3.可执行程序文件
  static string ExePath(const string& name)
  {
    return "./temp_files/" + name + ".exe";
  }
  //4.标准输入文件
  static string StdinPath(const string& name)
  {
    return "./temp_files/" + name + ".stdin";
  }
  //5.标准输出文件
  static string StdoutPath(const string& name)
  {
    return "./temp_files/" + name + ".stdout";
  }
  //6.标准错误文件
  static string StderrPath(const string& name)
  {
    return "./temp_files/" + name + ".stderr";
  }
  
  static bool CompileAndRun(const Json::Value&req
      ,Json::Value* resp)
  {
    //1.根据请求对象，生成源代码文件
    if(req["code"].empty())
    {
      (*resp)["error"] = 3;
      (*resp)["reason"] = "code empty";
      LOG(ERROR) << "code empty" << endl;
      return false;
    }
    //req["code"]根据key取出Value，value类型也是
    //Json::Value.通过asString()转成字符串
    const string& code = req["code"].asString();
    
    //这个函数把代码写到代码文件中
    string file_name = WriteTmpFile(code,req["stdin"].asString());
    //2.调用g++进行编译（fork+exec/system）
    //生成可执行程序，如果编译出错
    //需要把错误记录下来（重定向到文件中）
    bool ret = Compile(file_name);
    if(!ret)
    {
      (*resp)["error"] = 1;
      string reason;
      FileUtil::Read(CompileErrorPath(file_name),&reason);
      (*resp)["reason"] = reason;
      LOG(INFO) << "Compile failed" << endl;
      return false;
    }
    //3.调用可执行程序，把标准输入记录到文件中，然后
    //把文件中的内容重定向给可执行程序，可执行程序的
    //标准输出和标准错误内容也要重定向输出记录到文件
    int sig = Run(file_name);
    if(sig != 0)
    {
      (*resp)["error"] = 2;
      (*resp)["reason"] = "Program exit by signo: " + to_string(sig);
      LOG(INFO) << "Program exit by signo:" << to_string(sig << endl;
      return false;
    }
    //4.把程序的最终结果进行返回，构造resp对象
    (*resp)["error"] = 0;
    (*resp)["reason"] = "";
    string str_stdout;
    FileUtil::Read(StdoutPath(file_name),&str_stdout);
    (*resp)["stdout"] = str_stdout;
    string str_stderr;
    FileUtil::Read(StderrPath(file_name),&str_stderr);
    (*resp)["stderr"] = str_stderr;
    LOG(INFO) << "Program " << file_name << " Done" <<endl;
    return true;
  }

private:
  //1.把代码写到文件里面
  //2.给这次请求分配一个唯一的名字
  // tmp_1553408103.2
  static string WriteTmpFile(const string& code,const string& str_stdin)
  {
    static atomic_int id(0);
    ++id;
    string file_name = "tmp_"
      + to_string(TimeUtil::TimeStamp())
      + "." + to_string(id);
    FileUtil::Write(SrcPath(file_name).c_str(),code);
    //把标准输入也写到文件中
    FileUtil::Write(StdinPath(file_name).c_str(),str_stdin);
    return file_name;
  }
  static bool Compile(const string& file_name)
  {
    char* command[20] = {0};
    char buf[20][50] = {{0}};
    for(int i = 0;i < 20;++i)
    {
      command[i] = buf[i];
    }
    //1.构造编译指令
    sprintf(command[0],"%s","g++");
    sprintf(command[1],"%s",SrcPath(file_name).c_str());
    sprintf(command[2],"%s","-o");
    sprintf(command[3],"%s",ExePath(file_name).c_str());
    sprintf(command[4],"%s","-std=c++11");
    command[5] = NULL;
    int ret = fork();
    //2.创建子进程
    if(ret > 0)
    {
      //3.父进程进行进程等待
      waitpid(ret,NULL,0);
    }
    else 
    {
      //4.子进程进行程序替换
      int fd = open(CompileErrorPath(file_name).c_str(),O_WRONLY | O_CREAT,0666);
      if(fd < 0)
      {
        LOG(ERROR) << "open Compile file error" << endl;  
        exit(1);
      }
      dup2(fd,2);//期望写2能够把数据放到文件中
      execvp(command[0],command);
      exit(0);
    } 
    //ls就是基于stat实现的
    //5.编译是否成功
    struct stat st;
    ret = stat(ExePath(file_name).c_str(),&st);
    if(ret < 0)
    {
      LOG(INFO) << "Compile failed! " << file_name << endl; 
      return false;
    }
    LOG(INFO) << "Compile " << file_name << "OK!" << endl;
    return true;
  }
  
  static int Run(const string& file_name)
  {
    //1.创建子进程
    int ret = fork();
    if(ret > 0)
    {
      //2.父进程进行等待
      int status = 0;
      waitpid(ret,&status,0);
      return status & 0x7f;
    }
    else 
    {
      //3.进程重定向（标准输入 标准输出 标准错误）
      int fd_stdin = open(StdinPath(file_name).c_str(),O_RDONLY);
      dup2(fd_stdin,0);
      int fd_stdout = open(StdoutPath(file_name).c_str(),O_WRONLY | O_CREAT,0666);
      dup2(fd_stdout,1);
      int fd_stderr = open(StderrPath(file_name).c_str(),O_WRONLY | O_CREAT,0666);
      dup2(fd_stderr,2);
      //4.子进程进行程序替换
      execl(ExePath(file_name).c_str(),
          ExePath(file_name).c_str(),NULL);
      exit(0);
    }
  }
};
//请求
//{
// "code" : "#include...",
// "stdin" : "hello"
//}
//响应
//{
//"error" : 0正确编译运行,1编译,2运行,3其他错误
//"reason" : "",error为0，reason就是空字符串
//"stdout" : "hello",
//"stderr" : "",
//}
