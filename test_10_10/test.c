#include <stdio.h>
#include <string.h>

int main()
{
  FILE *fp = fopen("myfile","w");

  if(NULL == fp)
  {
    perror("fopen");
  }

  const char *ptr = "hello world!!\n";
  int count = 5;
  
  while(count--)
  {
    fwrite(ptr,sizeof(char),strlen(ptr),fp);
  }
  fclose(fp);
  return 0;
}
