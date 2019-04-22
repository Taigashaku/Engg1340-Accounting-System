#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  string date, amount, type, payment_method;
  ifstream fin ("temp.txt",ios::app);
  ofstream fout ("temp.txt",ios::app);
  if (fout.fail())
  {
    cout<<"Error in file opening!"<<endl;
    exit(1);
  }
  string command, line, month, tran_type, income_type;
  int statistic;
  double total_income=0,total_expenses=0;
  cout << "Please input command" << endl;
  cout << "add delete sort stat alert register login deleteac exit" << endl;
  while (cin >> command){

    //command "add"
    if (command=="add"){
      cout << "Please input \"date(DDMMYYYY), type, amount, payment method\"" << endl;
      while (cin >> date){
        if (date=="-1"){
          break;
        }
        cin >> type >> amount >> payment_method;
        fout << date << " " << type << " " << amount << " " << payment_method << endl;
      }
    }

    //command "delete"
    if (command=="delete"){
      cout << "Which line of record would you like to delete?" << endl;

    }

    //command "stat"

    if (command=="stat"){
      cout << "Please choose which one you would like to view" << endl;
      cout << "1. monthly income" << endl;
      cout << "2. percentage of transaction" << endl;
      cin >> statistic;
      switch(statistic){
        case 1:{
          //monthly income
          int sum=0;
          cout << "Which month would you like to search?" << endl;
          cout << "Please input in the format of MMYYYY" << endl;
          cin >> month;
          while (getline(fin,line)){
            if (line.substr(2,6)==month){
              int pos=0;
              int first_space, second_space;
              for (int i=0;i<3;i++){
                pos=line.find(" ",pos+1);
                if (i==1){
                  first_space=pos;
                }
                if (i==2){
                  second_space=pos;
                }
              }
              int length=second_space-first_space-1;
              sum+=stoi(line.substr(first_space+1,length));
            }
          }
          cout << "The monthly income is " << sum << endl;
        }
        case 2:{
          //percentage of transaction
          int sum=0;
          cout << "Please choose a type of transaction" << endl;
          cin >> tran_type;
          cout << "Is it income or expense?" << endl;
          cin >> income_type;
          while (getline(fin,line)){
            int first_space, second_space;
            int pos=0;
            for (int i=0;i<3;i++){
              pos=line.find(" ",pos+1);
              if (i==1){
                first_space=pos;
              }
              if (i==2){
                second_space=pos;
              }
            }
            if (line.substr(9,line.find(" ",9)-line.find(" ")-1)==tran_type){
              int length=second_space-first_space-1;
              if (income_type=="income" && stoi(line.substr(first_space+1,length))>0){
                sum+=stoi(line.substr(first_space+1,length));
                total_income+=stoi(line.substr(first_space+1,length));
              }
              else if (income_type=="expense" && stoi(line.substr(first_space+1,length))<0){
                sum-=stoi(line.substr(first_space+1,length));
                total_expenses-=stoi(line.substr(first_space+1,length));
              }
            }
            else{
              int length=second_space-first_space-1;
              if (stoi(line.substr(first_space+1,length))>0){
                total_income+=stoi(line.substr(first_space+1,length));
              }
              else if (stoi(line.substr(first_space+1,length))<0){
                total_expenses-=stoi(line.substr(first_space+1,length));
              }
            }
          }
          fin.clear();
          fin.seekg(0, ios::beg);
          double percentage=sum/(income_type=="income" ? total_income : total_expenses);
          cout << percentage*100 << "%" << endl;
          sum=0;
          total_income=0;
          total_expenses=0;
        }
      }
    }

    if (command=="exit"){
      fin.close();
      fout.close();
      exit(1);
    }

    cout << "Please input command" << endl;
    cout << "add delete sort stat alert register login deleteac" << endl;
  }

  return 0;
}
