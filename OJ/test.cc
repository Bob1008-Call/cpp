#include "compile.hpp"
#include "util.hpp"
#include <jsoncpp/json/json.h>
int main()
{
  Json::Value req;
  req["code"] = "#include <stdio.h>\n int main() {int a = 0;printf(\"hehe%d\",a);return 0;}";
  req["stdin"] = "";
  Json::Value resp;
  Compiler::CompileAndRun(req,&resp);
  Json::FastWriter writer;
  LOG(INFO) << writer.write(resp) << std::endl;
  return 0;
}
