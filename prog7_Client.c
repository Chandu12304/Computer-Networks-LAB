#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>

int main(int argc,char *argv[]){
  if(argc<4){
    printf("argument should contain 4 parameters");
  }
  int soc=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in addr;
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr(argv[1]);
  addr.sin_port=htons(atoi(argv[2]));
  
  char buffer[1024];
  
  printf("\nReading from the file %s...\n",argv[3]);
  int fd=open(argv[3],O_RDONLY);
  int n= read(fd,buffer,sizeof(buffer));
  
  sendto(soc,buffer,sizeof(buffer),0,(struct sockaddr*)&addr,sizeof(addr));
  printf("\nMessage is sent to server...\n");
  
  return 0;
}
