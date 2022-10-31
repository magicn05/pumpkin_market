// Server 
#include "Customer_Manager.h"
#include "User.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include "board.h"
#define MAX_DATA_SIZE 1024
using namespace std;

/// 전역변수 ////
int n = 0;
struct sockaddr_in clientaddr;

class Server_Manager {
public:
  struct sockaddr_in server_addr;
  Server_Manager() {
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(60000);
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(this->server_addr.sin_zero), '\0', 8);
  }
};

void thread_function(int new_fd) { 
  char buf[1024];
  int choice=0;
  cout << "Server:connection from FD: " << new_fd << " : " << inet_ntoa(clientaddr.sin_addr) << endl;
  cout << "Thread On" << endl;
  send(new_fd, "Welcome to Server!!", MAX_DATA_SIZE, 0);
  sleep(1);
  while(1){
  send(new_fd, "Choose your options", MAX_DATA_SIZE, 0);
  sleep(0.5);
  send(new_fd, "1. Board \n", MAX_DATA_SIZE, 0);
  sleep(1);
  send(new_fd, "2. Chatting Room \n", 25, 0);
  sleep(1);
  send(new_fd, "3. Library \n", 25, 0);
  sleep(1);
  send(new_fd, "Input >> ", 25, 0);
  A:
  recv(new_fd, buf, 1024, 0); 
  choice = atoi(buf);
  cout << "Client choice : " << choice << endl;
  sleep(1);
  switch(choice){
    case 1:
      send(new_fd, "client selected 1", 1024, 0);
      board_ctl(new_fd);
      goto A;
    case 2:
      send(new_fd, "client selected 2", 1024, 0);
      goto A;
    default:
      send(new_fd, "client selected none", 1024, 0);
      goto A;
  }
    
  n++;
  if (strcmp(buf, "z") == 0)
    cout << "n : " << n << endl;
  //}
  sleep(3);
  send(new_fd, "===========", 25, 0);
  }
}



int main() {
  cout << "S E R V E R          O N" << endl;
  int choice;
  int sockfd, new_fd, state;
  socklen_t client_len;
  // struct sockaddr_in clientaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  Server_Manager Server_Set;
  int reuseAddress = 1;
  int option = 1;

  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if (bind(sockfd, (struct sockaddr *)&(Server_Set.server_addr),
           sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  state = listen(sockfd, 5);
  if (state == -1) {
    perror("listen error : ");
    exit(0);
  }
  while (1) {

    new_fd = accept(sockfd, (struct sockaddr *)&clientaddr, &client_len);
    thread t1(thread_function, new_fd);
    t1.detach();
    cout << "count n : " << n << endl;
  }

  // vector<thread*> vector_thread;
  // vector_thread.pop_back(new thread(thread_function,1));
  // thread t1(thread_function, 1); //thread 를 만든다.
  // t1.join();

  // Customer_Manager a;
  // a.Put_User_List(new User("aaa","bbb","ccc","ddd"));
  // a.Put_User_List(new User("ddd","bbb","ccc","ddd"));
  // a.Print_out_all();
}
