
//Pumpkin Market Client

#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include "User.h"
#include "Customer_Manager.h"
#include <cstring>
#include <netdb.h>
#include <error.h>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[])
{
  int sockfd, numbytes;
  socklen_t addr_len;
  char buf[1024];
  int state, client_len;

  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  struct hostent *he;
  he = gethostbyname(argv[1]);
  
  sockfd = socket(AF_INET, SOCK_STREAM,0);
   
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(60000);
  server_addr.sin_addr= *((struct in_addr*)he->h_addr);
  
  inet_ntoa(server_addr.sin_addr);
  memset(&(server_addr.sin_zero),'\0',8);
  
  if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr))==-1){
    perror("connet");
    exit(1);
  }
  //char buf[1024];
  
  while(1)
  {
    fgets(buf, 1024, stdin);
    buf[strlen(buf)-1] = '\0';
    write(sockfd, buf, strlen(buf));
    
  }
  cout << "socket fd" << sockfd << endl;

  

  if((numbytes == recv(sockfd, buf, 1024,0))==-1){
    perror("recv");
    exit(1);
  }  
  buf[numbytes] = '\0';
  cout << "recevied " << endl;
  close(sockfd);
  return 0;
}