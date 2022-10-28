//This is Server for Pumpkin Market"
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include <unistd.h>

#include "User.h"
#include "Customer_Manager.h"

using namespace std;

class Server_Manager{
  public:
  struct sockaddr_in server_addr;
  Server_Manager(){
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(60000);
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(this->server_addr.sin_zero),'\0',8);
  }
};

void thread_function(int new_fd){
  cout << "thread test" << endl;
  int n;
  char buf[1024];
  while(1){
    if((n=read(new_fd,buf,1024))==-1){
      perror("read");
      exit(1);
    }
    write(new_fd, buf, strlen(buf));
  }

  
  cout << "b : " << new_fd << endl;
  cout << "good bye" << endl;
  cout << this_thread::get_id() << endl;
  sleep(2);
    
}


int main() {
  
  cout << "S E R V E R          O N" << endl;
  
  int choice;
  int sockfd, new_fd, state;
  socklen_t client_len;
  struct sockaddr_in clientaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  Server_Manager Server_Set;

  int reuseAddress = 1; 
  int option = 1;
  
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,&option, sizeof(option));

  
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

  new_fd = accept(sockfd, (struct sockaddr *)&clientaddr, &client_len);
  
  thread t1(thread_function, new_fd);
  //vector<thread*> vector_thread;
  //vector_thread.pop_back(new thread(thread_function,1));
  
  //thread t1(thread_function, 1); //thread 를 만든다.
  t1.join();
  
  Customer_Manager a;
  a.Put_User_List(new User("aaa","bbb","ccc","ddd"));
  a.Put_User_List(new User("ddd","bbb","ccc","ddd"));
  a.Print_out_all();
  // Load Customer's list.
  
  

  string User_Id;
  string User_Pin;
  cout << "Id >> ";
  cin >> User_Id;
  cout << "Pin >> ";
  cin >> User_Pin;
}