/********************************************************
** Author: Nick Milford
** Date: 10/12/16
** Description: Testing Line and Point classes
********************************************************/

#include "Line.hpp"
#include "Point.hpp"
#include <cstdio>
#include <cstdlib>
#include <time.h>

bool testAccessor(double x, double y)
{
	Point p(x, y);
	return p.getXCoord() == x && p.getYCoord() == y;
}

bool testCommutative(double x, double y, double v, double w)
{
	Point p1(x, y);
	Point p2(v, w);

	return p1.distanceTo(p2) == p2.distanceTo(p1);
}

bool testAbsoluteDistance(double x, double y, double a, double b)
{
	if(x < 0) x *= -1;
	if(y < 0) y *= -1;
	if(a < 0) a *= -1;
	if(b < 0) b *= -1;

	if(x < a) x += a;
	if(y < b) y += b; 	

	Point p1(x, y), p2(a, b), zero(0, 0);

	if(x < a || y < b || x < 0 || y < 0 || a < 0 || b < 0)
		throw "Invalid call to testProperty2";

	return p1.distanceTo(zero) > p2.distanceTo(zero);
}

bool zeroDistance(double x, double y)
{
	Point p1(x, y);
	return p1.distanceTo(p1) == 0;
}

bool zeroSlope(double x, double y, double z)
{
	Point p1(x, y);
	Point p2(z, y);
	Line l(p1, p2);
	return l.slope() == 0;
}

bool undefinedSlope(double x, double y, double z)
{
	Point p1(x, y);
	Point p2(x, z);
	Line l(p1, p2);
	try
	{
		l.slope();
	}
	catch(Line::UndefinedSlopeException e)
	{
		return true;
	}
	return false;
}

bool scaleSlope(double x, double y, double k)
{
	//x != 0, y != 0, k != 1
	Point zero(0, 0);
	Point p1(x, y);
	Point p2(x * k, y * k);
	Line l1(zero, p1);
	Line l2(zero, p2);
	double slope1 = l1.slope();
	double slope2 = l2.slope();
	if(slope1 < 0) slope1 *= -1;
	if(slope2 < 0) slope2 *= -1;
	double slopeDif = slope1 - slope2;
	return slopeDif < Line::VERY_CLOSE && slopeDif > -Line::VERY_CLOSE;
}

bool constantSlope(double x, double y, double k)
{
	Point p1(x, y);
	Point p2(x + 1, y + k);
	Line l1(p1, p2);
	double slopeDif = l1.slope() - k;
	return slopeDif < Line::VERY_CLOSE && slopeDif > -Line::VERY_CLOSE;

}

bool inverseConstantSlope(double x, double y, double k)
{
	Point p1(x, y);
	Point p2(x + k, y + 1);
	Line l1(p1, p2);
	double slopeDif = l1.slope() - 1.0 / k;
	return slopeDif < Line::VERY_CLOSE && slopeDif > -Line::VERY_CLOSE;
}

bool parallelLines(double x, double y, double v, double w, double a, double b)
{
	Point p1(x, y);
	Point p2(v, w);
	Point p3(x + a, y + b);
	Point p4(v + a, w + b);
	Line l1(p1, p2);
	Line l2(p3, p4);

	try
	{
		l1.intersectWith(l2);
	}
	catch(Line::ParallelLinesException e)
	{
		return true;
	}
	return false;
}

bool transformationIntersection(double x, double y, double v, double w, double a, double b)
{
	Point p1(x, y);
	Point p2(v, w);
	Point p3(v + a, w + b);
	Point p4(v - a, w - b);
	Line l1(p1, p2);
	Line l2(p3, p4);
	
	Point intersection = l1.intersectWith(l2);
	double xDif = intersection.getXCoord() - v;
	double yDif = intersection.getYCoord() - w;
	bool xSame = xDif < Line::VERY_CLOSE && xDif > -Line::VERY_CLOSE;
	bool ySame = yDif < Line::VERY_CLOSE && yDif > -Line::VERY_CLOSE;
	return xSame && ySame;
}

bool axisIntersection(double x, double y)
{
	Point p1(x, 0);
	Point p2(0, y);
	Point p3(x, y);
	Line l1(p1, p3);
	Line l2(p2, p3);

	Point intersection = l1.intersectWith(l2);
	double xDif = intersection.getXCoord() - x;
	double yDif = intersection.getYCoord() - y;
	bool xSame = xDif < Line::VERY_CLOSE && xDif > -Line::VERY_CLOSE;
	bool ySame = yDif < Line::VERY_CLOSE && yDif > -Line::VERY_CLOSE;
	return xSame && ySame;
}


bool degenerateLineConstruction(double x, double y)
{
	Point p1(x, y);
	try
	{
		Line l1(p1, p1);
	}
	catch(Line::DegenerateLinesException e)
	{
		return true;
	}
	return false;
}

double randomDub()
{
	double temp = (double)(rand() % 1000000) / (double)(rand() % 100000); 
	if(rand() % 2 == 0)
		temp *= -1;
	return temp;
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	int testCount = 100;
	
	printf("Testing Access\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub();
		if(!testAccessor(arg1, arg2))
			printf("Access Test Failed with %f, %f\n", arg1, arg2);
	}
	
	printf("Testing Commutative\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub(), arg4 = randomDub();
		if(!testCommutative(arg1, arg2, arg3, arg4))
			printf("Commutative Test Failed with %f, %f, %f, %f\n", arg1, arg2, arg3, arg4);
	}
	
	printf("Testing Absolute Distance\n");

	for(int i = 0; i < testCount;)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub(), arg4 = randomDub();
		
		//arg1, arg2, arg3, arg4 > 0
		
		if(arg1 < 0) arg1 *= -1;
		if(arg2 < 0) arg2 *= -1;
		if(arg3 < 0) arg3 *= -1;
		if(arg4 < 0) arg4 *= -1;
		
		//arg3 > arg1, arg4 > arg2
		arg3 += arg1;
		arg4 += arg2;	

		try
		{
			bool succ = testAbsoluteDistance(arg1, arg2, arg3, arg4);
			if(!succ)
				printf("Absolute Distance test failed with %f, %f, %f, %f\n", arg1, arg2, arg3, arg4);
				
			i++;
		}
		catch(const char* s) 
		{
			printf("We screwed up\n");
		}
	}

	printf("Testing Zero Distance\n");
	
	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub();
		if(!zeroDistance(arg1, arg2))
			printf("Zero Distance Test Failed with %f, %f\n", arg1, arg2);
	}
	
	printf("Testing Zero Slope\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub();
		if(!zeroSlope(arg1, arg2, arg3))
			printf("Zero Slope test failed with %f, %f, %f\n", arg1, arg2, arg3);
	}
	
	printf("Testing Undefined Slope\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub();
		if(!undefinedSlope(arg1, arg2, arg3))
			printf("Undefined slope test failed with %f, %f, %f\n", arg1, arg2, arg3);
	}
	
	printf("Testing Scaled Slope\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub();
		if(!scaleSlope(arg1, arg2, arg3))
			printf("Scaled slope test failed with %f, %f, %f\n", arg1, arg2, arg3);
	}
	
	printf("Testing Constant Slope\n"); 

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub();
		if(!constantSlope(arg1, arg2, arg3))
			printf("Constant slope failed with %f, %f, %f\n", arg1, arg2, arg3);
	}
	
	printf("Testing Inverse Constant Slope\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub();
		if(!inverseConstantSlope(arg1, arg2, arg3))
			printf("Constant slope failed with %f, %f, %f\n", arg1, arg2, arg3);
	}
	
	printf("Testing Parallel Lines\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub(), arg4 = randomDub(), arg5 = randomDub(), arg6 = randomDub();
		if(!parallelLines(arg1, arg2, arg3, arg4, arg5, arg6))
			printf("Parallel Lines test failed with %f, %f, %f, %f, %f, %f\n", arg1, arg2, arg3, arg4, arg5, arg6);
	}
	
	printf("Testing Transformation Intersection\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub(), arg3 = randomDub(), arg4 = randomDub(), arg5 = randomDub(), arg6 = randomDub();
		if(!transformationIntersection(arg1, arg2, arg3, arg4, arg5, arg6))
			printf("Transformation intersection failed with %f, %f, %f, %f, %f, %f\n", arg1, arg2, arg3, arg4, arg5, arg6);
	}
	
	printf("Testing Axis Intersection\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub();
		if(!axisIntersection(arg1, arg2))
			printf("Axis intersection failed with %f, %f\n", arg1, arg2);
	}

	printf("Testing Degenerate Line Construction\n");

	for(int i = 0; i < testCount; i++)
	{
		double arg1 = randomDub(), arg2 = randomDub();
		if(!degenerateLineConstruction(arg1, arg2))
			printf("Degenerate line test %d failed with %f, %f\n", i, arg1, arg2);
	}
	
	printf("Tests Complete\n");

	return 0;
}
