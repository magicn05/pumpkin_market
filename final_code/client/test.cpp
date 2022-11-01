#include <iostream>

using namespace std;

int main()
{
  string s;
  getline(cin, s);
  cout << "length of s : " << s.length() << endl;
  s = s + '\0';
  cout << "length of s : " << s.length() << endl;
}