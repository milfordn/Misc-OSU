#include "myInteger.hpp"

MyInteger::MyInteger(int i)
{
	pInteger = new int(i);
}

MyInteger::MyInteger(MyInteger &m)
{
	pInteger = new int(m.getMyInt());
}

MyInteger::~MyInteger()
{
	delete pInteger;
}

MyInteger MyInteger::operator=(MyInteger &other)
{
	*pInteger = *other.pInteger;
	return *this;	
}

void MyInteger::setMyInt(int i)
{
	*pInteger = i;
}

int MyInteger::getMyInt()
{
	return *pInteger;
}
