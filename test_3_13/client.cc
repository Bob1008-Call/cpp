
static void Usage(std::string proc_)
{
  std::cout<<"Usage: "<< proc_ << "port"<<std::endl;
}

//client 

int main(int argc,int *argv[])
{
  if(argc != 3)
  {
    Usage(argv[0]);
    exit(1);
  }
  int sock = socket(AF_INET,SOCK_STREAM,0);
  if(sock<0)
  {
    std::cout<<"socket error!"<<std::endl;
    exit(2);
  }
  
  struct sockaddr_in sever;
  bzero(&sever,sizeof(sever));
  sever.sin_family = AF_INET;
  sever.sin_port = htons(atoi(argv[2]));
  sever.sin_addr.s_addr = inet_addr(argv[1]);
  if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
  {
    std::cerr<<"connect"<<std::endl;
    exit(3);
  }

  Request_t rq;
  Response_t rsp;
  for(;;)
  {
    std::cout<<"Please Enter<x,y>";
    std::cin>>rq.x>>rq.y;
    std::cout<<"Please Enter Your Op<+ - * />";
    std::cin>>rq.op;
    send(sock,&rq,sizeof(rq),0);
    recv(sock,&rsp,sizeof(rsp),0);
    std::cout<<"status: "<<rsp.status<<std::endl;
    std::cout<<"result: "<<rsp.result<<std::endl;
  }
  return 0;
}

