#include <iostream>
#include "User_Data.h"
using namespace std;

int main()
{
  cout<<"****************************"<<endl;
  cout<<"Welcome to AccountingSystem"<<endl;
  cout<<"****************************"<<endl;
  int User_ID=User_System();//Get UserID
  Operation(User_ID);
  return 0;
}
