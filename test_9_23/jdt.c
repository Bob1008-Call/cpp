#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define NONE  "\e[0m"
#define RED   "\e[0;31m"
#define BLUE  "\e[0;34m"
#define GREEN "\e[0;32m"
int main()
{
      int index = 0;
          char str[21];
              memset(str,'\0',sizeof(str));
                  char tmp[5] = {'-','\\','|','/','\0'};
                      while(index <=20)
                            {   
                                    str[index] = '#';
                                    if(index <=7)
                                        printf(RED"%s[%d%%%c]\r"NONE,str,index*5,tmp[index%4]);
                                    else if(index <= 14)
                                        printf(BLUE"%s[%d%%%c]\r"NONE,str,index*5,tmp[index%4]);
                                    else
                                      printf(GREEN"%s[%d%%%c]\r"NONE,str,index*5,tmp[index%4]); 
                                    fflush(stdout);
                                    index++;
                                    usleep(100000);
                                }   
                          printf("\n");
                              return 0;
}
