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
// 	int sin_size;
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
#include "menu.h"
//#include "member.h"

//#include "board.h"
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
  LPMENU lpMenu;
 	//int sd = *((int*) arg);	
 	menuCreate(&lpMenu);
 	menuRun(lpMenu, new_fd);
 	menuDestroy(lpMenu);
 	close(new_fd);
 	return;
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
