#ifndef SHAPE_HPP
#define SHAPE_HPP

/*************************************
 * Author:	Nick Milford
 * Date: 	November 5
 * Description:	Abstract class definition for a shape, requires Area and Perimiter implementation
 * **********************************/

class Shape
{
public:
	virtual double area() = 0;
	virtual double perimiter() = 0;
};

#endif
