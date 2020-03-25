#include "Square.hpp"
#include "Circle.hpp"
#include <cstdio>
#include <vector>

using std::vector;

/*******************************************
 * Description: Calculates the average area given some shapes
 *
 * ****************************************/
double averageArea(vector<Shape*> shapes)
{
	double total = 0;
	for(int i = 0; i < shapes.size(); i++)
	{
		total += shapes[i]->area();
	}
	return total / shapes.size();
}

int main(int argc, char** argv)
{
	Circle c1(1);
	Rectangle r1(1, 3);
	Square s1(2);

	vector<Shape*> v;
	v.push_back(&c1);
	v.push_back(&r1);
	v.push_back(&s1);

	printf("Area of circle radius 1: %f\n", c1.area());
	printf("Area of rectangle lengths 1 and 3: %f\n", r1.area());
	printf("Area of square side lengths 2: %f\n", s1.area());
	printf("Perimiter of circle radius 1: %f\n", c1.perimiter());
	printf("Perimiter of rectangle lengths 1 and 3: %f\n", r1.perimiter());
	printf("Perimiter of Square side lengths 1: %f\n", s1.perimiter());
	printf("Average Area: %f\n", averageArea(v));

	return 1;
}
