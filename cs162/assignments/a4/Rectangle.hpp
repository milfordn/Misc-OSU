#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "Shape.hpp"

/**************************************************8
 * Author: 	Nick Milford
 * Date:	November 5
 * Description:	Definition of a geometric rectangle, subclass of Shape
 * ************************************************/

class Rectangle : public Shape
{
private:
	double length, width;
public:
	Rectangle(double l, double w);
	double area(); //override
	double perimiter(); //override
	double getLength();
	double getWidth();
	virtual void setLength(double l);
	virtual void setWidth(double w);
};

#endif
