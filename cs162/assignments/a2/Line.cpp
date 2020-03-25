/*********************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Header file for a class defining a 
**		geometric point in 2d space
*********************************************/

#include "Line.hpp"
#include "Point.hpp"

/*********************************************
** Description: Constructor to make the compiler work
**
*********************************************/
Line::Line(){}

/*********************************************
** Description: Basic constructor, passes arguments
**		to private fields, does some error checking
*********************************************/
Line::Line(Point _p1, Point _p2)
{
	double dx = _p1.getXCoord() - _p2.getXCoord();
	double dy = _p1.getYCoord() - _p2.getYCoord();
	bool sameX = dx < VERY_CLOSE && dx > -VERY_CLOSE;
	bool sameY = dy < VERY_CLOSE && dy > -VERY_CLOSE;
	
	//can't have a line with only one point
	if(sameX && sameY)
		throw Line::DegenerateLinesException(_p1);
	
	p1 = _p1;
	p2 = _p2;
}

/*********************************************
** Description: public accessor for private field point1
**
*********************************************/
Point Line::getPoint1()
{
	return p1;
}

/*********************************************
** Description: public accessor for private field point2
**
*********************************************/
Point Line::getPoint2()
{
	return p2;
}

/*********************************************
** Description: computes the slope of a line,
**		throws an error if the slope is undefined
*********************************************/
double Line::slope()
{
	double dx = p1.getXCoord() - p2.getXCoord();
	double dy = p1.getYCoord() - p2.getYCoord();

	if(dx < VERY_CLOSE && dx > -VERY_CLOSE)
		throw Line::UndefinedSlopeException(*this);

	return dy / dx;
}

/*********************************************
** Description: Finds the point at which two lines
**		intersect, throwing an error if the
**		lines are parallel
*********************************************/
Point Line::intersectWith(Line other)
{		
	//to easily write the equation
	double x1 = p1.getXCoord(), x2 = p2.getXCoord(), x3 = other.p1.getXCoord(), x4 = other.p2.getXCoord();
	double y1 = p1.getYCoord(), y2 = p2.getYCoord(), y3 = other.p1.getYCoord(), y4 = other.p2.getYCoord();
	
	//the Denominator for the equation for both x and y are the same
	double denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	if(denominator < VERY_CLOSE && denominator > -VERY_CLOSE)
		throw Line::ParallelLinesException(*this, other);
	
	double xnumerator = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
	double ynumerator = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
	
	return Point(xnumerator / denominator, ynumerator / denominator);
}
