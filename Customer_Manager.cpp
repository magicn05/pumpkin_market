#include <iostream>
#include <vector>
#include "Customer_Manager.h"
#include "User.h"
using namespace std;

void Customer_Manager::Put_User_List(User* new_User){
  User_List.push_back(new_User);
}