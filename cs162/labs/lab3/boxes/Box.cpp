/*************************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Implementation for the Box class
*************************************************/

#include "Box.hpp"

/*************************************************
 * ** Description: Sets the width member variable
 * **
 * *************************************************/
void Box::setWidth(double _width)
{
	width = _width;
}


/*************************************************
 * ** Description: Sets the length member variable
 * **
 * *************************************************/
void Box::setHeight(double _height)
{
	height = _height;
}


/*************************************************
 * ** Description: Sets the height member variable
 * **
 * *************************************************/
void Box::setLength(double _length)
{
	length = _length;
}


/*************************************************
 * ** Description: Standard constructor, sets length,
 * **		width, height
 * *************************************************/
Box::Box(double _length, double _width, double _height)
{
	setLength(_length);
	setWidth(_width);
	setHeight(_height);
}


/*************************************************
 * ** Description: Default constructor, sets all
 * **		values to zero
 * *************************************************/
Box::Box()
{
	setLength(0);
	setWidth(0);
	setHeight(0);
}


/*************************************************
 * ** Description: Calculates the volume of the given
 * **		box size
 * *************************************************/
double Box::getVolume()
{
	return length * width * height;
}

/*************************************************
 * ** Description: Calculates the surface area of the
 * **		given box size
 * *************************************************/
double Box::getSurfaceArea()
{
	return 2 * length * length + 2 * width * width + 2 * height * height;
}
