
// Client

#include "Customer_Manager.h"
#include "User.h"
#include <arpa/inet.h>
#include <cstring>
#include <error.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

#define MAX_DATA_SIZE 1024

using namespace std;

void recv_thread(int new_fd) {
  cout << "recv thread on " << endl;
  char recv_msg[MAX_DATA_SIZE];
  int n;
  while (1) {
    n = recv(new_fd, recv_msg, MAX_DATA_SIZE, 0);
    if (n<=0){
      cout << "Disconnected from server" << endl;
      break;
    }
    recv_msg[n] = '\0';
    cout << recv_msg << endl;
    fflush(stdout);
  }
  //c++에서는 thread cancle / exit 없음.
}

void send_thread(int new_fd) {
  cout << "send thread on " << endl;
  int n;
  char send_msg[MAX_DATA_SIZE];
  while (1) {
    cin >> send_msg;
    n = strlen(send_msg);
    if(!strcmp(send_msg,"/q"))
      break;
    send(new_fd, send_msg, MAX_DATA_SIZE, 0);
  }
  //c++에서는 thread cancle / exit 없음.
}

int main(int argc, char *argv[]) {
  int sockfd;
  socklen_t addr_len;
    
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  struct hostent *he;
  he = gethostbyname(argv[1]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(60000);
  server_addr.sin_addr = *((struct in_addr *)he->h_addr);
  inet_ntoa(server_addr.sin_addr);
  memset(&(server_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
    perror("connet");
    exit(1);
  }
  cout << "Client Start-------" << endl;
  thread recv_c(recv_thread, sockfd);
  thread send_c(send_thread, sockfd);
  recv_c.join();
  send_c.join();
  close(sockfd);
}