
#ifndef User_H
#define User_H
#include <iostream>
#include <string>

using namespace std;

class User{
  private:
  string User_Id;
  string User_Pin;
  string User_Name;
  string User_Payment_Info;
  int Reported_cnt;
  
  public:
  
  //User();
  User(string User_Id, string User_Pin, string User_Name, string User_Payment_Info);
  ~User(){}
  string get_User_Id();
  string get_User_Name();
  string get_User_Payment_Info();
};

#endif