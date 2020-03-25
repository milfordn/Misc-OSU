#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

/**************************************************
 * Author: 	Nick Milford
 * Date:	November 5
 * Description:	Class definition for a geometric circle, subclass of Shape
 * ***********************************************/

class Circle : public Shape
{
private:
	double radius;
public:
	Circle(double r);
	double area();	//Override
	double perimiter(); //Override
	void setRadius(double r);
	double getRadius();
};

#endif
	
