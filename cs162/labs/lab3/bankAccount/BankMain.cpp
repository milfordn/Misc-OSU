/*************************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Testing the BankAccount class
*************************************************/

#include<cstdio>
#include "BankAccount.hpp"

int main(int argc, char **argv)
{
	BankAccount account1("Mr Lebowski", "V8856", 22.15);
	printf("%s\n", account1.getCustomerName().c_str());
	printf("%s\n", account1.getCustomerID().c_str());
	printf("%f\n", account1.getCustomerBalance());
	account1.deposit(1000000);
	printf("%f\n", account1.getCustomerBalance());
	account1.withdraw(1000000);
	printf("%f\n", account1.getCustomerBalance());
	return 0;
}
