#include "Circle.hpp"

/****************************************************
 * Author:	Nick Milford
 * Date:	November 5
 * Description:	Implementation of Circle.hpp
 * *************************************************/

#define PI 3.14159

Circle::Circle(double r)
{
	setRadius(r);
}

void Circle::setRadius(double r)
{
	radius = r;
}

double Circle::getRadius()
{
	return radius;
}

/*************************************
 * Description: Implementation of Shape::area()
 * 		pi * r^2
 * **********************************/
double Circle::area()
{
	return radius * radius * PI;
}

/*************************************
 * Description: Implementation of Shape::perimiter()
 * 		2pi * r
 * **********************************/
double Circle::perimiter()
{
	return 2 * PI * radius;
}
