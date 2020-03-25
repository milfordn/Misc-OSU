#include "Store.hpp"
#include <cstdio>
#include <string>

using std::string;

/********************************
 * Description: tests that the constructor and 
 * 		accessors don't mess with the values
 * *****************************/
void testGetMethods(string title, string id, string description, double price, int quantity)
{
	Product p(title, id, description, price, quantity);
	bool result = p.getIdCode() == id && p.getDescription() == description && p.getTitle() == title && p.getPrice() == price && p.getQuantityAvailable() == quantity;
	printf("Product constructor and get methods don't mess with values: %d\n", result);
}

/********************************
 * Description: tests that the constructor and
 * 		accessors don't mess with the values
 * *****************************/
void testGetMethods(string name, string id, bool isPremium)
{
	Customer c(name, id, isPremium);
	bool result = c.getAccountID() == id && c.isPremiumMember() == isPremium;
	printf("Customer constructor and get methods don't mess with values: %d\n", result);
}

/********************************
 * Description: tests that decreaseQuantity works
 * *****************************/
void testDecreaseQuantity(Product *p)
{
	int beforeQuantity = p->getQuantityAvailable();
	p->decreaseQuantity();
	bool result = p->getQuantityAvailable() == beforeQuantity - 1;
	printf("Product::decreaseQuantity works: %d\n", result);
}

/******************************************
 * Description: Tests that the given product is
 * 		added where we expect it to be
 * ***************************************/
void testAddProductToCart(Customer *c, Product *p)
{
	c->addProductToCart(p->getIdCode());
	bool result = c->getCart()[c->getCart().size() - 1] == p->getIdCode();
	printf("Customer::addproductToCart works: %d\n", result);
}

/*******************************************
 * Description: tests that Customer::emptyCart 
 * 		actually empties the cart
 * ****************************************/
void testEmptyCart(Customer *c, Product *p)
{
	c->addProductToCart(p->getIdCode());
	c->emptyCart();
	bool result =  c->getCart().empty();
	printf("Customer::emptyCart works: %d\n", result);
}

/*********************************************
 * Description: tests that the store search works
 * ******************************************/
void testProductMemberSearch(Store *s, Customer *c, Product *p)
{
	bool result = s->getProductFromID(p->getIdCode()) == p && s->getMemberFromID(c->getAccountID()) == c;
	printf("Searching for products and members by ID works: %d\n", result);
}

/*********************************************
 * Description: tests that a search that doesn't yield
 * 		results gives null
 * ******************************************/
void testProductMemberSearch(Store *s)
{
	bool result = s->getProductFromID("_") == NULL && s->getMemberFromID("invalid") == NULL;
	printf("Searching for invalid IDs give null: %d\n", result);
}

/*********************************************
 * Description: Tests that the product search works.
 * 		Because this prints, we can't automatically
 * 		check for correctness
 * ********************************************/
void testProductTextSearch(Store *s, string text)
{
	printf("Testing product text search for %s\n", text.c_str());
	s->productSearch(text);
}

/**********************************************
 * Description: tests that nothing will be printed if
 * 		no products match the text
 * *******************************************/
void testProductFailedSearch(Store *s)
{
	printf("Testing for failed product text search\n");
	s->productSearch("_");
	printf("Nothing should have been printed\n");
}

/************************************************
 * Description: Tests adding a product to a member's cart
 * *********************************************/
void testAddProductToMemberCart(Store *s, Customer *c, Product *p)
{
	s->addProductToMemberCart(p->getIdCode(), c->getAccountID());
	bool result = c->getCart()[c->getCart().size()-1] == p->getIdCode();
	printf("Adding a product to a member's cart works: %d\n", result);
}

/*********************************************
 * Description: Tests that a message is printed if the product is out of stock
 * *******************************************/
void testAddProductOutOfStock()
{
	Store s;
	Customer c("_", "_", false);
	Product p("out of stock", "out of stock", "out of stock", 0, 0);
	s.addProduct(&p);
	s.addMember(&c);

	printf("Testing for error message on adding out of stock item to cart\n");
	s.addProductToMemberCart(p.getIdCode(), c.getAccountID());
	printf("Something should have been printed\n");
}

/**********************************************
 * Description: Tests that a message is printed 
 * 		when an item doesn't exist
 * *******************************************/
void testAddInvalidID(Store *s, Customer *c, Product *p)
{
	printf("Testing for error message on adding product to invalid cart id\n");
	s->addProductToMemberCart(p->getIdCode(), "spooky ghost member");
	printf("An error should have been printed\n");

	printf("testing for error message on adding invalid product to cart\n");
	s->addProductToMemberCart("Unobtanium", c->getAccountID());
	printf("An error should have been printed\n");
	
	printf("testing for error message on adding invalid product to an invalid cart\n");
	s->addProductToMemberCart("wat are ids", "how do they work?");
	printf("An error should have been printed. I don't care which error, I just want one\n");
}

/*****************************************
 * Description: when an empty cart is checked 
 * 		out, complain
 * **************************************/
void testCheckoutEmpty(Store *s, Customer *c)
{
	c->emptyCart();
	printf("Testing error on checking out an empty cart\n");
	s->checkOutMember(c->getAccountID());
	printf("Something should have been printed\n");
}

/*****************************************
 * Description: Test that an error is printed
 * 		if the member DNE
 * **************************************/
void testCheckoutInvalidID(Store *s)
{
	printf("testing error on checking out invalid member ID\n");
	s->checkOutMember("ddddddddddddddddddd");
	printf("something should have printed\n");
}

/***********************************************
 * Description: tests a successful checkout
 * ********************************************/
void testSuccessfulCheckout(Store *s, Customer *c)
{
	printf("Testing successful sture checkout, a receipt should be printed\n");
	s->checkOutMember(c->getAccountID());
	printf("Now checking if the cart is emptied: %d\n", c->getCart().empty());
}

int main(int argc, char** argv)
{
	Store s;
 	
	//initialize store products
	//(food items in the room because I'm not feeling creative)
	
	Product *p[12];
	p[0] = new Product("F_001", "Grapes", " Seedless, comes in red or green", 4.99, 20);
	p[1] = new Product("B_001", "Strawberry Lemonade", "Strawberries and lemonade. What more do you need in life?", 3.85, 5);
	p[2] = new Product("P_001", "Sliced Ham", "Perfect for sandwiches", 2.50, 8);
	p[3] = new Product("G_001", "PoppySeed Muffins", "may contain poppy seeds", 2.99, 2);
	p[4] = new Product("G_002", "Whole Wheat Bread", "pre-sliced! Also perfect for sandwiches", 3.50, 12);
	p[5] = new Product("C_001", "Mayonnaise", "pretty meh condiment tbh but it works", 5.00, 6);
	p[6] = new Product("C_002", "Mustard", "goes well with any other condiment", 2.25, 14);
	p[7] = new Product("C_003", "Cream Cheese", "Use with bagels for a good start to any morning, unless you have a midterm you haven't studied for. In that case, god help you", 3.99, 10);
	p[8] = new Product("G_003", "Bagels", "The superior form of bread, though significantly more per two slices", 2.85, 18);
	p[9] = new Product("B_002", "Lemonade Mix", "Just add water", 0.99, 23);
	p[10] = new Product("B_003", "Variety pack mix", "contains lemonade, strawberry lemonade, raspberry lemonade, and cherry pomegranete", 8.00, 9);
	p[11] = new Product("B_004", "Hot Chocoloate Mix", "for all of you who don't like coffee", 12.00, 3);
	
	for(int i = 0; i < 12; i++)
		s.addProduct(p[i]);

	//Initialize Customers
	Customer nonPremium("guy A", "C_001", false);
	Customer premium("guy B", "C_002", true);

	s.addMember(&nonPremium);
	s.addMember(&premium);

	//let's get started
	
	//testGetMethods("title", "id", "desc", 123, 456);
	//testGetMethods("name", "identification", false);

	testDecreaseQuantity(p[0]);
	
	testAddProductToCart(&nonPremium, p[1]);
	testEmptyCart(&premium, p[2]);

	testProductMemberSearch(&s);
	testProductTextSearch(&s, "lemonade");
	testProductFailedSearch(&s);

	testAddProductToMemberCart(&s, &nonPremium, p[3]);
	testAddProductOutOfStock();
	testAddInvalidID(&s, &nonPremium, p[4]);

	testCheckoutEmpty(&s, &premium);
	testCheckoutInvalidID(&s);
	testSuccessfulCheckout(&s, &nonPremium);

	for(int i = 0; i < 12; i++)
		delete (p[i]);

	return 0;
}
