#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class board_item{
  private:
  int board_no;
  string board_title;
  string board_writer;
  int board_cnt;
  int board_recom;

  public:
  board_item(int board_no, string board_title, string board_writer, int board_cnt, int board_recom);
  ~board_item();
  void setBoard_no(int board_no);
  void setBoard_title(string board_title);
  
  int getBoard_no();
  string getBoard_title();
  string getBoard_writer();
  int getBoard_cnt();
  int getBoard_recom();
};

class board_manager{
  private:
  vector<board_item*> board_list;
  int list_cnt;
  public:
  board_manager();
  ~board_manager();
  void addList(board_item* item);
  int getlist_cnt();
  void printList();
};

void board_ctl(int new_fd);

#endif