#include <iostream>
#include <string>
#include "User.h"

using namespace std;

User::User(string User_Id="", string User_Pin="", string User_Name="", string User_Payment_Info=""){
  this->User_Id = User_Id;
  this->User_Pin = User_Pin;
  this->User_Name = User_Name;
  this->User_Payment_Info = User_Payment_Info;
  Reported_cnt = 0;
}
// User::User(){
//     this->User_Id = "initial";
//     this->User_Pin = "";
//     this->User_Name = "";
//     this->User_Payment_Info = "";
//     this->Reported_cnt = 0;
//   }
string User::get_User_Id(){ return this->User_Id; }
string User::get_User_Name() { return this->User_Name; }
string User::get_User_Payment_Info() { return this->User_Payment_Info; }