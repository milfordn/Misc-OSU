#include "Store.hpp"

#include <cstdio>

/************************************
 * Author: Nick Milford
 * Date: October 25 2016
 * Description: Implementation for Store Header
 * *********************************/

using std::string;

/************************************
 * Description: adds a product to the collection of products
 * *********************************/
void Store::addProduct(Product *p)
{
	inventory.push_back(p);
}

/***********************************
 * Description: Adds a member to the collection of members
 * ********************************/
void Store::addMember(Customer *c)
{
	members.push_back(c);
}
/************************************
 * Description: searches the collection of products for a
 * 		given ID, returns null if not found
 * *********************************/
Product* Store::getProductFromID(string id)
{
	for(int i = 0; i < inventory.size(); i++)
	{
		if(id == inventory[i]->getIdCode())
			return inventory[i];
	}
	return NULL;
}

/************************************
 * Description: searches the collection of members for a
 * 		given member id, returns null if not found
 * *********************************/
Customer* Store::getMemberFromID(string id)
{
	for(int i = 0; i < members.size(); i++)
	{
		if(id == members[i]->getAccountID())
			return members[i];
	}
	return NULL;
}

/*************************************
 * Description: searches through titles and descriptions
 * 		or products for a string of text, prints
 * 		details about the product
 * **********************************/
void Store::productSearch(string str)
{
	for(int i = 0; i < inventory.size(); i++)
	{
		bool foundItem = false;
		//check all possible strings of length
		//of str for a match, first in name, then
		//in description
		
		string title = inventory[i]->getTitle();
		string descr = inventory[i]->getDescription();

		int tlen = title.size();
		int dlen = descr.size();
		int slen = str.size();

		//search title
		for(int j = 0; j < tlen - slen; j++)
		{
			//printf("%d, %d, %d, %d\n", tlen, slen, tlen - slen, tlen - slen < 0);
			//if(title.size() - str.size() < 0)
			//	break;
			//printf("Searching %s for %s | %d | %d\n", title.c_str(), str.c_str(), j, title.size() - str.size());
			if(title.compare(j, slen, str) == 0)
			{
				foundItem = true;
				break;
			}
		}		

		//if we didn't find anything, search description
		if(!foundItem)
			for(int j = 0; j < dlen - slen; j++)
			{
				//printf("Searching %s for %s\n", descr.c_str(), str.c_str());
				if(descr.compare(j, slen, str) == 0)
				{
					foundItem = true;
					break;
				}
			}
		
		//if we found a match, print details
		if(foundItem)
		{
			printf("%s\n", title.c_str());
			printf("ID code: %s\n", inventory[i]->getIdCode().c_str());
			printf("Price: %f\n", inventory[i]->getPrice());
			printf("%s\n\n", descr.c_str());
		}
	}	
}

/********************************************
 * Description: finds member and product given their IDs, 
 * 		adds the product ID to the member cart
 * *****************************************/
void Store::addProductToMemberCart(string pID, string mID)
{
	Customer *cust = getMemberFromID(mID);
	Product *prod = getProductFromID(pID);

	//customer must exist
	if(!cust)
	{
		printf("Member #%s Not Found\n", mID.c_str());
		return;
	}

	//product must exist
	if(!prod)
	{
		printf("Product #%s Not Found\n", pID.c_str());
		return;
	}

	//product must exist, but in a different way
	if(prod->getQuantityAvailable() == 0)
	{
		printf("Sorry, product #%s is out of stock\n", pID.c_str());
		return;
	}

	cust->addProductToCart(pID);
}

/***********************************************
 * Description: prints details about each product in a 
 * 		member's cart if that product is in stock,
 * 		accumulates a price, adds a shipping fee
 * 		if the customer is not a member
 * ********************************************/
void Store::checkOutMember(string mID)
{
	Customer *cust = getMemberFromID(mID);
	double accumPrice = 0;

	if(!cust)
	{
		printf("That customer does not exist\n");
		return;
	}
	
	//Techinically we can check out an empty cart, but specifications say otherwise
	if(cust->getCart().size() == 0)
	{
		printf("The cart is empty\n");
		return;
	}

	//go through the cart
	for(int i = 0; i < cust->getCart().size(); i++)
	{
		//product is guarenteed to not be null because it had to be put
		//into the cart by addProductToMemberCart, which checks for invalid ID
		Product *prod = getProductFromID(cust->getCart()[i]);

		//can't give them what we don't have
		if(prod->getQuantityAvailable() == 0)
		{
			printf("Sorry, product #%s, %s is currently out of stock\n", mID.c_str(), prod->getTitle().c_str());
			continue;
		}

		//print some receipt details
		printf("%s - $%f\n", prod->getTitle().c_str(), prod->getPrice());

		//add to total price, decrease quantity
		accumPrice += prod->getPrice();
		prod->decreaseQuantity();
	}

	printf("Subtotal: $%f\n", accumPrice);

	//shipping cost for non-premuim members
	if(!cust->isPremiumMember())
	{
		printf("Shipping Cost: $%f\n", accumPrice * 0.07);
		accumPrice += accumPrice * 0.07; //7% shipping fee
	}
	else
		printf("Shipping Cost: $0\n");

	printf("Total: $%f\n", accumPrice);

	cust->emptyCart();
}
