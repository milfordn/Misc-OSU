#include "Rectangle.hpp"

/***************************************
 * Author: 	Nick  Milford
 * Date:	November 5
 * Description: Implementation of Rectangle.hpp
 * ************************************/

double Rectangle::getWidth()
{
	return width;
}

double Rectangle::getLength()
{
	return length;
}

void Rectangle::setWidth(double w)
{
	width = w;
}

void Rectangle::setLength(double l)
{
	length = l;
}

Rectangle::Rectangle(double l, double w)
{
	setLength(l);
	setWidth(w);
}

/*********************************************
 * Description: Implementation of Shape::area()
 * ******************************************/
double Rectangle::area()
{
	return width * length;
}

/*********************************************
 * Description: Implementation of Shape::perimiter()
 * ******************************************/
double Rectangle::perimiter()
{
	return width*2 + length*2;
}
