#ifndef BOX_HPP
#define BOX_HPP

/*********************************************
 * ** Author: Nick Milford
 * ** Date: 10/11/16
 * ** Description: Definition for the Box class
 * *********************************************/

class Box
{
private:
	double width, length, height;
public:
	Box();
	Box(double _length, double _width, double _height);
	void setWidth(double _width);
	void setLength(double _length);
	void setHeight(double _height);
	double getVolume();
	double getSurfaceArea();
};

#endif

