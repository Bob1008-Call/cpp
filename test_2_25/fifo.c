#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
  int ret;
  ret = mkfifo("myfifo",0666);
  if(ret == -1)
  {
    perror("mkfifo error");
  }
  return 0;
}
