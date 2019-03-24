#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  umask(0);//在创建新文件或者目录时，屏蔽掉新文件或目录不应有的访问允许权限。
  int fd = open("myfile",O_WRONLY|O_CREAT,0644);
  if(fd<0)
  {
    perror("open");
    return 1;
  }

  int count = 5;
  const char* msg = "hello world!!!\n";
  while(count--)
  {
    write(fd,msg,strlen(msg));
  }
  close(fd);
  return 0;
}
