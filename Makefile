User_System.o:User_System.cpp User_Data.h
	g++ -c $<
Operation.o:Operation.cpp
	g++ -c $<
Accounting_System:User_System.o Operation.o
	g++ $^ -o $@
##g++ -std=c++11 User_system.cpp Operation.cpp Main.cpp -o Accounting_System
