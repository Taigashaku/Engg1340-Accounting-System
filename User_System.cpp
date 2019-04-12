#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ofstream fout (User_Data.txt);
  ifstream fin (User_Data.txt); 
  cout<<"Please login first."<<endl;
  cout<<"1.Login\n2.Register\n";
  cout<<"Your choice(1/2/3):\n";
  int choice;
  cin>>choice;
  if (choice==1)
  {

  }
  else if (choice==2)
  {

  }
  return 0;
}
