#include <iostream>
#include <fstream>
using namespace std;
const int MAX = 200;
struct User{
  string name,password;
};

int main()
{
  string Current_User[MAX][2];
  ifstream fin ("User_Info.txt");
  ofstream fout ("User_Info.txt");
  if (fin.fail() || fout.fail())
  {
    cout<<"Error in file opening!"<<endl;
    exit(1);
  }
  //Get Current User Data
  for (int i=0;i<MAX;i++)
  {
    for (int j=0;j<2;j++)
    {
      fin>>Current_User[i][j];
    }
  }
  //Start Procedure
  cout<<"Please login first."<<endl;
  cout<<"1.Login\n2.Register\n";
  cout<<"Your choice(1/2):\n";
  int choice;
  cin>>choice;
  if (choice==1)
  {

  }
  else if (choice==2)
  {
    User New_User;
    string Confirm_pw="Confirm_pw";
    int Rename=1;
    while (Rename==1)
    {
      cout<<"User Name: ";
      cin>>New_User.name;
      for (int k=0;k<MAX;k++)
      {
        if (Current_User[k][0]==New_User.name)
        {
          cout<<"The User Name Has Been Taken."<<endl;
          Rename=1;
          break;
        }
      }
      Rename=0;
    }
    while (Confirm_pw!=New_User.password)
    {
      New_User.password="\0";
      cout<<"Password: ";
      cin>>New_User.password;
      cout<<"Confirm Your Password: ";
      cin>>Confirm_pw;
      if (Confirm_pw!=New_User.password)
      {
        cout<<"Not the same"<<endl;
      }
    }
    fout<<New_User.name<<endl<<New_User.password<<endl;
  }
  fin.close();
  fout.close();
  return 0;
}
