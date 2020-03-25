#ifndef MYINT_HPP
#define MYINT_HPP

class MyInteger
{
private: int *pInteger;
public:
	MyInteger(int);
	MyInteger(MyInteger&);
	~MyInteger();
	MyInteger operator=(MyInteger&);
	void setMyInt(int);
	int getMyInt();
};

#endif
