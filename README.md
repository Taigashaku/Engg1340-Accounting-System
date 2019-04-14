# Engg1340-Accounting-System

Problem statement

Help users to manage their financial status like adding records, editing and removing records, sorting the records according to users’ input.

Problem setting
Assumption
1.	Amount by user input does not exceed 2147483647.
2.	All inputs from user are valid and they follow the format.
3. The Number of users are up to 200.

Functions
1.	Record the income and expenses of the user
2.	Basic information could be found in the records, such as date of transaction, amount of money involved, type of the transaction(e.g. food, stationery, electronics, etc), payment method(e.g. cash, credit card, smartphone apps, etc)
3.	User can edit or remove the records at anytime
4.	The system can sort the records according to user’s input like type, date, etc
5.	The system can calculate some statistic for the user like monthly income, percentage of each type of transaction, etc
6.	User can set an amount of budget. When the expenses reach the budget, the system will alert the user
7.	A user authentication system: Users are allowed to register and set password for individual account, using the account to access their own data. The system secure the data as it requires a password to unlock the data

Input/Output specifications

Input:

date type amount payment method

date type amount payment method

…(until user input “-1”)

What to output(monthly_income / percentage type / records)

Output:
monthly income / percentage / …

Compilation and execution instructions

The program will first ask for the registration of user if no accounts has been registered before. After logging in the system with password, the system allows users to type in different commands to manipulate their data.

Commands:

add

delete

sort

stat

alert

register

login

deleteac(while using the ac to be deleted)
