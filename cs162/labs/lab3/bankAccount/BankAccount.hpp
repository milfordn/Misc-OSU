#ifndef BANKACCOUNT_HPP
#define BANKACOUNT_HPP

/*********************************************
 * ** Author: Nick Milford
 * ** Date: 10/11/16
 * ** Description: Definition for the BankAccount class
 * *********************************************/

#include <string>
using std::string;

class BankAccount
{
private:
	string customerName, customerID;
	double customerBalance;
public:
	BankAccount(string name, string id, double startBalance);
	string getCustomerName();
	string getCustomerID();
	double getCustomerBalance();
	void withdraw(double balance);
	void deposit(double balance);
};

#endif

