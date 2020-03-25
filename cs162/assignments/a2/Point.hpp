#ifndef POINT_HPP
#define POINT_HPP

/*********************************************
 * ** Author: Nick Milford
 * ** Date: 10/11/16
 * ** Description: Header file for a class defining a 
 * **		geometric point in 2d space
 * *********************************************/

class Point
{
private:
	double x, y;
public:
	Point(double _x, double _y);
	Point();
	double getXCoord();
	double getYCoord();
	double distanceTo(Point p);
};

#endif
