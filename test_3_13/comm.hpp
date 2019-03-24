#pragma once 

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>


typedef struct 
{
  int x;
  int y;
  char op;
}Request_t;

typedef struct 
{
  int status;
  int result;
}Response_t;
