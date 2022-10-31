#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
using namespace std;

board_item::board_item(int board_no=0, string board_title="", string board_writer="", int board_cnt = 0, int board_recom = 0){
  this->board_cnt = board_no;
  this->board_title = board_title;
  this->board_writer = board_writer;
  this->board_cnt = board_cnt;
  this->board_recom = board_recom;
}

board_item::~board_item(){

}

int board_item::getBoard_no(){
  return this->board_no;
}

string board_item::getBoard_title(){
  return this->board_title;
}

string board_item::getBoard_writer(){
  return this->board_writer;
}

int board_item::getBoard_cnt(){
  return this->board_cnt;
}

int board_item::getBoard_recom(){
  return this->board_recom;
}

void board_item::setBoard_no(int board_no){
  this->board_no = board_no;
}

void board_item::setBoard_title(string board_title){
  this->board_title = board_title;
}

board_manager::board_manager(){
  this->list_cnt = 0;
}

board_manager::~board_manager(){

}

void board_manager::addList(board_item* item){
  this->board_list.push_back(item);
  this->list_cnt++;
}

int board_manager::getlist_cnt(){
  return this->list_cnt;
}

void board_manager::printList(){
  for(auto i: board_list){
    cout << i->getBoard_no() << " " << i->getBoard_title() << " " << i->getBoard_writer() << endl;
  }
}

void board_ctl(int new_fd){
  int choice;
  board_manager board_admin;
  board_admin.addList(new board_item(1,"Welcome","Admin",10,100));
  board_admin.addList(new board_item(2,"Hi","Peter",2,0));
  board_admin.addList(new board_item(3,"Hello","David",3,0));
  board_admin.addList(new board_item(4,"Bon Joure","Jang",1,0));
  string temp = "No              Title             Writer             Read             Recom";
  char chars[temp.length() + 1];
  temp.copy(chars,temp.length() + 1);
  send(new_fd, chars, 1024, 0);
  while(1)
  {
    //cout << "No    " << "Title  " << "Writer  " << "Read  " << "Recom " << endl;
    board_admin.printList();
    switch(choice){
      case 1: // 번호 입력은 글 읽기.
              // 댓글작성
              // 추천하기
              // 나가기

      case 2: // 글 작성하기

      case 3: // 다음 페이지로
    }
  }
  
}