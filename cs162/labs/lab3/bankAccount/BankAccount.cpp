/*************************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Implementation for the BankAccount class
*************************************************/

#include "BankAccount.hpp"
#include <string>
using std::string;

/*************************************************
 * ** Description: Standard constructor, sets all
 * **		private fields with arguments
 * *************************************************/
BankAccount::BankAccount(string name, string id, double startBalance)
{
	customerName = name;
	customerID = id;
	customerBalance = startBalance;
}


/*************************************************
 * ** Description: accessor method for private 
 * **		customerName
 * *************************************************/
string BankAccount::getCustomerName()
{
	return customerName;
}


/*************************************************
 * ** Description: accessor method for private
 * **		customerID
 * *************************************************/
string BankAccount::getCustomerID()
{
	return customerID;
}


/*************************************************
 * ** Description: accessor method for private
 * **		customerBalance
 * *************************************************/
double BankAccount::getCustomerBalance()
{
	return customerBalance;
}


/*************************************************
 * ** Description: subtracts given value from the
 * **		customer's balance
 * *************************************************/
void BankAccount::withdraw(double balance)
{
	customerBalance -= balance;
}


/*************************************************
 * ** Description: adds the given value to the 
 * **		customer's balance
 * *************************************************/
void BankAccount::deposit(double balance)
{
	customerBalance += balance;
}
