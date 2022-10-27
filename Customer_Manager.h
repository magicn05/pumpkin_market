#ifndef Customer_Manager_H
#define Customer_Manager_H
#include "User.h"
#include <vector>

using namespace std;

class Customer_Manager{
  vector<User*> User_List;

  public:
  void Put_User_List(User* new_User);
  bool Login_Check(string User_Id, string User_Pin);
  bool Add_User();
  void Print_out_all(){
    for (auto i:this->User_List){
      cout << i->get_User_Id() << endl;
    }
  }
};

#endif