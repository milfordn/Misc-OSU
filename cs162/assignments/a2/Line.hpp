#ifndef LINE_HPP
#define LINE_HPP

/*********************************************
 * ** Author: Nick Milford
 * ** Date: 10/11/16
 * ** Description: Header file for a class defining a 
 * **		geometric point in 2d space
 * *********************************************/

#include "Point.hpp"

class Line
{
private:
	Point p1, p2;
public:
	Line(Point _p1, Point _p2);
	Line();
	Point getPoint1();
	Point getPoint2();
	double slope();
	Point intersectWith(Line other);
	class DegenerateLinesException;
	class ParallelLinesException;
	class UndefinedSlopeException;
	const static double VERY_CLOSE = 0.00001;

};


class Line::DegenerateLinesException
{
public:
	Point onlyPoint;
	DegenerateLinesException(Point problem) 
	{
		onlyPoint = problem;
	}
};

class Line::ParallelLinesException
{
public:
	Line l1, l2;
	ParallelLinesException(Line _l1, Line _l2)
	{
		l1 = _l1;
		l2 = _l2;
	}
};

class Line::UndefinedSlopeException
{
public:
	Line problem;
	UndefinedSlopeException(Line l1)
	{
		problem = l1;
	}
};

#endif
