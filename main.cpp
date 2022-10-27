//This is Server for Pumpkin Market"

#include <iostream>
#include <string>
#include "User.h"
#include "Customer_Manager.h"

using namespace std;

int main()
{
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