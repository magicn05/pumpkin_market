// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include <netdb.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <pthread.h>
// #include "menu.h"
// //#include "member.h"

// #define BACKLOG 1024


// void* start_main(void* arg)
// {
// 	LPMENU lpMenu;

// 	int sd = *((int*) arg);	

// 	menuCreate(&lpMenu); //메뉴를 만든다..
// 	menuRun(lpMenu, sd); //
// 	menuDestroy(lpMenu);
// 	close(sd);
// 	return NULL;
// }


// char line[]="\n─────────────────────────────────────────────────────────────────────\n";
// char thick_line[]="\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";

// int main(){

// 	int sockfd, new_fd;
// 	struct sockaddr_in my_addr;
// 	struct sockaddr_in their_addr;
// 	socklen_t sin_size;
// 	int yes=1;
// 	pthread_t tid;

// 	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
// 	{
// 		perror("socket");
// 		exit(1);
// 	}

// 	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
// 	{
// 		perror("setsockopt");
// 		exit(1);
// 	}

// 	my_addr.sin_family = AF_INET;
// 	my_addr.sin_port = htons(60000);
// 	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
// 	memset(&(my_addr.sin_zero), '\0', 8);

// 	if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
// 	{
// 		perror("bind");
// 		exit(1);
// 	}

// 	if(listen(sockfd, BACKLOG) == -1) 
// 	{
// 		perror("listen");
// 		exit(1);
// 	}
	
// 	while(1)
// 	{
// 		sin_size = sizeof(struct sockaddr_in);

// 		if((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size)) == -1)
// 		{
// 			perror("accept");
// 			continue;
// 		}
// 		printf("server : got connection from %s \n", inet_ntoa(their_addr.sin_addr));
// 		if(pthread_create(&tid, NULL, start_main, &new_fd)!=0) {
// 			perror("pthread_create");
// 		} else {
// 			pthread_detach(tid);
// 		}
// 	}

// 	return 0;
// }


// Server 
//#include "Customer_Manager.h"
//#include "User.h"
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
#include <vector>
//#include "menu.h"
//#include "member.h"

//#include "board.h"
#define MAX_DATA_SIZE 1024
using namespace std;

void start_menu(int sd);
void menu_select(int sd);


/// 전역변수 ////
int n = 0;
struct sockaddr_in clientaddr;

class user{
  string user_id;
  string user_pin;
  string user_name;
  string chat_name;
  public:
  user(string user_id, string user_pin, string user_name, string chat_name);
  ~user();
  string get_userid(){return user_id;}
};

user::user(string user_id="", string user_pin="", string user_name="", string chat_name=""){
  this->user_id = user_id;
  this->user_pin = user_pin;
  this->user_name = user_name;
  this->chat_name = chat_name;
}

class user_Manager{
  vector<user> user_list;
  public:
  void add_user(user new_user);
};

void user_Manager::add_user(user new_user){
  user_list.push_back(new_user);
}

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

void thread_function(int sd) { 
  
  //load users
  start_menu(sd); //1번 , 2번의 선택..
  close(sd);
    
  // LPMENU lpMenu;
 	// //int sd = *((int*) arg);	
 	// menuCreate(&lpMenu);
 	// menuRun(lpMenu, new_fd);
 	// menuDestroy(lpMenu);
 	// close(new_fd);
 	// return;
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
    
  }
}

void start_menu(int sd) {
  string id, name, pin;
  
  char buf[1024];
  int n, a, b;
  int end_flag = 0;
  while (end_flag != 1) {
    sprintf(buf, "%s", "S T A R T --- M E N U \n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "메뉴를 선택하세요\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "1번. 로그인\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "2번. 회원 가입\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "3번. 연결 끊기\n\n");
    send(sd, buf, strlen(buf), 0);
    n = recv(sd, buf, sizeof(buf), 0);
    buf[n] = '\0';
    a = atoi(buf);

    switch (a) {
    case 1:
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      sleep(1);
      sprintf(buf, "%s", "로그인 페이지 입니다. \n\n");
      send(sd, buf, strlen(buf), 0);

      sprintf(buf, "%s", "ID  >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, buf, sizeof(buf), 0);
      name = buf;
      sprintf(buf, "%s", "PIN >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, buf, sizeof(buf), 0);
      pin = buf;
      // if (Log_in(name, pin, user) == 0) {
      //   menu_select(sd, user);
      // } else
      //   break;
      // if return int = 0 성공 이면 ..
      // menu_select(sd) 로 이동
      //  i freturn int =1 실패 이면, start menu로 다시 g
      break;

    case 2:
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      sleep(1);
      sprintf(buf, "%s", "회원가입 페이지 입니다. \n\n");
      send(sd, buf, strlen(buf), 0);
      
      sprintf(buf, "%s", "New ID  >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, buf, sizeof(buf), 0);
      id = buf;
      sprintf(buf, "%s", "New PIN >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, buf, sizeof(buf), 0);
      pin = buf;
      sprintf(buf, "%s", "User Name >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, buf, sizeof(buf), 0);
      name = buf;
      // function ()..
      sleep(5);
      break;

    case 3:
      sprintf(buf, "%s", "");
      send(sd, buf, 0, 0);
      end_flag = 1;
      break;
    }
  }
  return;
}

void menu_select(int sd){
  // LPMENU lpMenu;
 	// //int sd = *((int*) arg);	
 	// menuCreate(&lpMenu);
 	// menuRun(lpMenu, new_fd);
 	// menuDestroy(lpMenu);
 	// close(new_fd);
 	// return;
}