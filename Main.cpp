#include <iostream>
using namespace std;

int main()
{
  Graphic_User_Interface();
  int User_ID=User_System();//Get UserID
  Operation(User_ID);
  return 0;
}
