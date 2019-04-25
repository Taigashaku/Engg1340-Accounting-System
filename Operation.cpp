#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
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
  int statistic, budget=0, count=0, category;
  double total_income=0,total_expenses=0;
  cout << "Please input budget." << endl;
  cin >> budget;
  cout << "Please input command" << endl;
  cout << "add delete sort stat alert register login deleteac exit" << endl;
  while (cin >> command){

    count=0;
    //calculate the total income and total expense
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
      int length=second_space-first_space-1;
      if (stoi(line.substr(first_space+1,length))>0){
        total_income+=stoi(line.substr(first_space+1,length));
      }
      else if (stoi(line.substr(first_space+1,length))<0){
        total_expenses-=stoi(line.substr(first_space+1,length));
      }
      count+=1;
    }
    fin.clear();
    fin.seekg(0, ios::beg);



    //command "add"
    if (command=="add"){
      cout << "Please input \"date(YYYYMMDD), type, amount, payment method(please use underline to replace spacebar)\"" << endl;
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
      if (statistic==1){
        //monthly income
        int sum=0;
        cout << "Which month would you like to search?" << endl;
        cout << "Please input in the format of YYYYMM" << endl;
        cin >> month;
        while (getline(fin,line)){
          if (line.substr(0,6)==month){
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
        cout << "The monthly income is $" << sum << endl;
      }
      if (statistic==2){
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
            }
            else if (income_type=="expense" && stoi(line.substr(first_space+1,length))<0){
              sum-=stoi(line.substr(first_space+1,length));
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

    if (command=="alert"){
      cout << "Please choose which action you would like to take" << endl;
      cout << "1. check budget" << endl;
      cout << "2. update budget" << endl;
      cin >> statistic;
      if (statistic==1){
        cout << "Your current budget is $" << budget << "." << endl;
      }
      if (statistic==2){
        cout << "Please input the new budget." << endl;
        cin >> budget;
        cout << "Your update budget is $" << budget << endl;
      }
    }

    if (command=="sort"){

      cout << "which category would you like to sort?" << endl;
      cout << "1. date" << endl;
      cout << "2. type" << endl;
      cout << "3. amount" << endl;
      cout << "4. payment method" << endl;
      cin >> category;
      if (category==1){
        int * array=new int [count];
        int smallest=100000000;
        for (int i=0;i<count;i++){
          int number=0;
          getline(fin,line);
          //store the date in array
          array[i]=stoi(line.substr(0,8));
        }
        fin.clear();
        fin.seekg(0, ios::beg);

        //arrange the date in ascending order in array
        for (int i=0;i<count;i++){
          int temp=0;
          int largest=0;
          int number;
          for (int j=0;j<count-i;j++){
            if (array[j]>largest){
              largest=array[j];
              number=j;
            }
          }
          temp=array[count-i-1];
          array[count-i-1]=largest;
          array[number]=temp;
        }

        //print the sorted file according to the order in array
        for (int i=0;i<count;i++){
          while (getline(fin,line)){
            if (stoi(line.substr(0,8))==array[i]){
              cout << line << endl;
            }
          }
          fin.clear();
          fin.seekg(0, ios::beg);
        }
        delete[] array;
      }

      if (category==2){
        string * array=new string [count];
        for (int i=0;i<count;i++){
          int number=0;
          getline(fin,line);
          //store the type in array
          array[i]=line.substr(9,line.find(" ",9)-9);
        }
        fin.clear();
        fin.seekg(0, ios::beg);

        //arrange the type in array
        sort(array, array+count);

        //remove duplicates in array
        for (int i=0;i<count;i++){
          for (int j=i+1;j<count;){
            if (array[i]==array[j]){
              for (int k=j;k<count-1;k++){
                array[j]=array[j+1];
              }
              count--;
            }
            else{
              j++;
            }
          }
        }

        //print the sorted file according to the order in array
        for (int i=0;i<count;i++){
          while (getline(fin,line)){
            if (line.substr(9,line.find(" ",9)-9)==array[i]){
              cout << line << endl;
            }
          }
          fin.clear();
          fin.seekg(0, ios::beg);
        }

        delete[] array;
      }

      if (category==3){
        int * array=new int [count];
        int smallest=100000000;
        for (int i=0;i<count;i++){
          int number=0;
          getline(fin,line);
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
          int length=second_space-first_space-1;

          //store the amount in array
          array[i]=stoi(line.substr(first_space+1,length));
        }
        fin.clear();
        fin.seekg(0, ios::beg);

        //arrange the amount in ascending order in array
        for (int i=0;i<count;i++){
          int temp=0;
          int largest=array[0];
          int number;
          for (int j=0;j<count-i;j++){
            if (array[j]>=largest){
              largest=array[j];
              number=j;
            }
          }
          temp=array[count-i-1];
          array[count-i-1]=largest;
          array[number]=temp;
        }

        //print the sorted file according to the order in array
        for (int i=0;i<count;i++){
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
            int length=second_space-first_space-1;
            if (stoi(line.substr(first_space+1,length))==array[i]){
              cout << line << endl;
            }
          }
          fin.clear();
          fin.seekg(0, ios::beg);
        }
        delete[] array;
      }

      if (category==4){
        string * array=new string [count];
        for (int i=0;i<count;i++){
          int number=0;
          getline(fin,line);
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
          int length=line.length()-second_space-1;

          //store the payment method in array
          array[i]=line.substr(second_space,length);
        }
        fin.clear();
        fin.seekg(0, ios::beg);

        //arrange the payment method in array
        sort(array, array+count);

        //remove duplicates in array
        for (int i=0;i<count;i++){
          for (int j=i+1;j<count;){
            if (array[i]==array[j]){
              for (int k=j;k<count-1;k++){
                array[j]=array[j+1];
              }
              count--;
            }
            else{
              j++;
            }
          }
        }

        //print the sorted file according to the order in array
        for (int i=0;i<count;i++){
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
            int length=line.length()-second_space-1;
            if (line.substr(second_space,length)==array[i]){
              cout << line << endl;
            }
          }
          fin.clear();
          fin.seekg(0, ios::beg);
        }

        delete[] array;
      }
    }

    if (command=="deleteac"){

    }

    if (command=="register"){

    }

    if (command=="login"){

    }

    if (command=="exit"){
      cout << "Bye!" << endl;
      fin.close();
      fout.close();
      exit(1);
    }

    if (total_expenses>budget){
      cout << "Your expenses have exceeded your budget!" << endl;
    }
    if (total_expenses==budget){
      cout << "Your expenses have just met your budget!" << endl;
    }

    cout << "Please input command" << endl;
    cout << "add delete sort stat alert register login deleteac" << endl;
  }
  return 0;
}
