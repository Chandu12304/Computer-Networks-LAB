#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main(){
  mkfifo(FIFO1,0666);
  mkfifo(FIFO2,0666);
  
  char filename[50];
  char buffer[1024];
  
  int fd1=open(FIFO1,O_RDONLY);
  int n1=read(fd1,filename,sizeof(filename));
  buffer[n1] = '\0';
  
  int fd2=open(filename,O_RDONLY);
  int n2=read(fd2,buffer,sizeof(buffer));
  buffer[n2] = '\0'; 
  
  int fd3=open(FIFO2,O_WRONLY);
  write(fd3,buffer,sizeof(buffer));
  
  close(fd1);
  close(fd2);
  close(fd3);
}
