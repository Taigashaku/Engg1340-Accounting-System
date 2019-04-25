#include <iostream>
#include <fstream>
#include <vector>
#include "User_Data.h"
using namespace std;

int main()
{
  vector<User> Current_User;
  int status=0,counter=0;//0=offline,others=logged UserID
  //Start Procedure
  while (status==0)
  {
    ifstream fin ("User_Info.txt",ios::app);
    ofstream fout ("User_Info.txt",ios::app);
    if (fin.fail() || fout.fail())
    {
      cout<<"Error in file opening!"<<endl;
      exit(1);
    }
    //Get Current User Data
    User r;
    while (!fin.eof())
    {
      fin>>r.code>>r.name>>r.password;
      counter++;
      Current_User.push_back(r);
    }
    cout<<"Please login first."<<endl;
    cout<<"1.Login\n2.Register\n";
    cout<<"Your choice(1/2):\n";
    int choice;
    cin>>choice;
    if (choice==1)//login
    {
      string Username,Password;
      int Rename=0;
      int Pos;
      while (Rename==0)//Username
      {
        cout<<"User Name: ";
        cin>>Username;
        for (int k=0;k<Current_User.size();k++)
        {
          if (Current_User[k].name==Username)
          {
            Pos=k;
            Rename=1;
            break;
          }
        }
        if (Rename==0)
        {
          cout<<"No Such User"<<endl;
          Rename=0;
        }
      }
      while (Password!=Current_User[Pos].password)
      {
        cout<<"Password: ";
        cin>>Password;
        if (Password!=Current_User[Pos].password)
        {
          cout<<"Wrong Password!"<<endl;
        }
      }
      cout<<"Login success!"<<endl;
      status=Current_User[Pos].code;

    }
    else if (choice==2)//Register
    {
      User New_User;
      string Confirm_pw="Confirm_pw";
      int Rename=0;
      while (Rename==0)//Username
      {
        Rename=1;
        cout<<"User Name: ";
        cin>>New_User.name;
        for (int k=0;k<Current_User.size();k++)
        {
          if (Current_User[k].name==New_User.name)
          {
            cout<<"The User Name Has Already Been Taken."<<endl;
            Rename=0;
            break;
          }
        }
      }
      while (Confirm_pw!=New_User.password && Rename==1)//Password
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
      fout<<counter<<endl<<New_User.name<<endl<<New_User.password<<endl;
      cout<<"New User Registered!"<<endl;
    }
    fin.close();
    fout.close();
  }
  return status;
}
