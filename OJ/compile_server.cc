#include "httplib.h"
#include "compile.hpp"
#include <unordered_map>
#include <jsoncpp/json/json.h>
int main()
{
  using namespace httplib;
  Server server;

  server.Post("/compile",[](const Request& req,Response& resp)
  {
    (void)req;
    //如何从req获取到Json请求，Json如何和http协议结合
    //Json如何进行解析和构造?jsoncpp第三方库
    std::unordered_map<std::string,std::string> body_kv;
    UrlUtil::ParseBody(req.body,&body_kv);
    Json::Value req_json;//req对象获取到
    //for(std::unordered_map<std::string,std::string>::iterator it = body_kv.begin();it != body_kv.end();++it)
    //{
    //  req_json[it->first] = it->second;
    //}
    for(auto p : body_kv)
    {
      req_json[p.first] = p.second;
    }
    
    Json::Value resp_json;//resp_json 放到响应中
    Compiler::CompileAndRun(req_json,&resp_json);
    Json::FastWriter writer;//完成序列化 
    resp.set_content(writer.write(resp_json),"text/plain");
  });
  server.listen("0.0.0.0",9092);
  return 0;
}
