#include "myInteger.hpp"
#include <iostream>

int main(int charc, char** argv)
{
	MyInteger obj1(17);
	MyInteger obj2 = obj1;
	std::cout << obj1.getMyInt() << std::endl;
	std::cout << obj2.getMyInt() << std::endl;
	
	obj2.setMyInt(9);
	std::cout << obj1.getMyInt() << std::endl;
	std::cout << obj2.getMyInt() << std::endl;
	
	MyInteger obj3(42);
	obj2 = obj3;
	//obj2.setMyInt(obj3.getMyInt());
	std::cout << obj2.getMyInt() << std::endl;
	std::cout << obj3.getMyInt() << std::endl;

	obj3.setMyInt(1);
	std::cout << obj2.getMyInt() << std::endl;
	std::cout << obj3.getMyInt() << std::endl;
	return 0;
}
