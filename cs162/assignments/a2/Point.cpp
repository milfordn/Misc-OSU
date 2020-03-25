/*********************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Implementation for Point.hpp
*********************************************/

#include <math.h>
#include "Point.hpp"

/*********************************************
 * ** Description: basic constructor, passes arguments
 * **		to private fields
 * *********************************************/
Point::Point(double _x, double _y)
{
	x = _x;
	y = _y;
}

/*********************************************
** Description: required(?) default constructor
** 		(compiler complains)
*********************************************/
Point::Point(){}

/*********************************************
 * ** Description: public accessor for private field x
 * **
 * *********************************************/
double Point::getXCoord() 
{
	return x;
}

/*********************************************
 * ** Description: public accessor for private field y
 * **
 * *********************************************/
double Point::getYCoord()
{
	return y;
}

/*********************************************
 * ** Description: computes scalar distance to another point
 * **
 * *********************************************/
double Point::distanceTo(Point p)
{
	double dx = p.x - x;
	double dy = p.y - y;
	return sqrt(dx * dx + dy * dy);
}
