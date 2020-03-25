#include "Square.hpp"

/****************************************
 * Author:	Nick Milford
 * Date:	November 5
 * Description:	Implementation of Square.hpp
 * *************************************/

Square::Square(double d) : Rectangle(d, d)
{
	setLength(d);
}

/***************************************
 * Description: Sets both length and width 
 * 		overrides Rectangle::setLength(double)
 * ************************************/
void Square::setLength(double d)
{
	this->Rectangle::setLength(d);
	this->Rectangle::setWidth(d);
}

/*******************************************
 * Description: Sets both length and width
 * 		overrides Rectangle::setWidth(double)
 * ****************************************/
void Square::setWidth(double d)
{
	this->Rectangle::setLength(d);
	this->Rectangle::setWidth(d);
}
