/***********************************************
** Author: Nick Milford
** Date: 10/11/16
** Description: Just testing. Move along.
***********************************************/

#include<cstdio>
#include "Box.hpp"

int main(int argc, char **argv)
{
	Box box1(3, 4, 5);
	Box box2;

	printf("%f\n", box1.getVolume());
	printf("%f\n", box2.getVolume());
	printf("%f\n", box1.getSurfaceArea());
	printf("%f\n", box2.getSurfaceArea());

	box2.setLength(1);
	box2.setWidth(1);
	box2.setHeight(1);
	printf("%f\n", box2.getVolume());

	return 0;
}
