#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

/************************************************************
 * Autor:	Nick Milford
 * Date: 	November 5
 * Description:	Defines a geometric square, subclass of Rectangle
 * **********************************************************/

class Square : public Rectangle
{
public:
	Square(double);
	void setLength(double);// Override
	void setWidth(double); // Override
};

#endif
