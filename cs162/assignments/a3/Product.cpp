#include "Product.hpp"

/*********************************
 * Author: Nick Milford
 * Date: October 25 2016
 * Description: Implementation for a product class
 * ******************************/

using std::string;

/*********************************
 * Description: Run-of-the-mill constructor, assigns argument values to private members
 * ******************************/
Product::Product(string id, string title, string description, double price, int quantity)
{
	this->idCode = id;
	this->title = title;
	this->description = description;
	this->price = price;
	this->quantityAvailable = quantity;
}

/*********************************
 * Description: public accessor for ID
 * ******************************/
string Product::getIdCode() 
{
	return idCode;
}

/********************************
 * Description: public accessor for title
 * *****************************/
string Product::getTitle() 
{
	return title;
}

/********************************
 * Description: public accessor for description
 * *****************************/
string Product::getDescription()
{
	return description;
}

/********************************
 * Description: public accessor for price
 * *****************************/
double Product::getPrice()
{
	return price;
}

/********************************
 * Description: public accessor for quantity
 * *****************************/
int Product::getQuantityAvailable()
{
	return quantityAvailable;
}

/********************************
 * Description: decrements available quantity
 * *****************************/
void Product::decreaseQuantity()
{
	quantityAvailable--;
}
