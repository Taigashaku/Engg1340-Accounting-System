Graphic_User_Interface.o:Graphic_User_Interface.cpp
	g++ -c $<
User_System.o:User_System.cpp
	g++ -c $<
Operation.o:Operation.cpp
	g++ -c $<
Accounting_System:Graphic_User_Interface.o User_System.o Operation.o
	g++ $^ -o $@
