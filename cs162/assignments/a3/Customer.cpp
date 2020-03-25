/******************************************************
 * Author: Nick Milford
 * Date: October 25 2016
 * Description: Implementation for Customer header
 * ***************************************************/

#include "Customer.hpp"

using std::string;
using std::vector;

/*****************************************************
 * Description: Assigns arguments to member variables, 
 * 		initializes cart as an empty vector
 * **************************************************/
Customer::Customer(string name, string id, bool premium)
{
	this->name = name;
	this->accountID = id;
	this->premiumMember = premium;
}

/*****************************************************
 * Description: public accessor for accountID
 * **************************************************/
string Customer::getAccountID()
{
	return accountID;
}

/*****************************************************
 * Description: Public accessor for cart
 * **************************************************/
vector<string> Customer::getCart()
{
	return cart;
}

/*****************************************************
 * Description: adds the product ID to the back of the cart
 * **************************************************/
void Customer::addProductToCart(string productID)
{
	cart.push_back(productID);
}

/*****************************************************
 * Description: public accessor method for premium member status
 * **************************************************/
bool Customer::isPremiumMember()
{
	return premiumMember;
}

/*****************************************************
 * Description: empties the cart
 * **************************************************/
void Customer::emptyCart()
{
	cart.clear();
}
