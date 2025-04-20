#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netdb.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main(){
  
  mkfifo(FIFO1,0666);
  mkfifo(FIFO2,0666);

  char filename[50];
  char buffer[1024];
  
  printf("\nEnter the file name\n");
  fgets(filename,sizeof(filename),stdin);
  filename[strcspn(filename, "\n")] = '\0';
  
  int fd1=open(FIFO1,O_WRONLY);
  write(fd1,filename,strlen(filename)+1);
  
  int fd2=open(FIFO2,O_RDONLY);
  int n= read(fd2,buffer,sizeof(buffer));
  buffer[n] = '\0';
  
  printf("%s",buffer);
  
  return 0;
}
