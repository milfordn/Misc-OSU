#include "PreferredProject.hpp"
#include "RegularProject.hpp"

#include <cstdio>

int main(int c, char** v)
{
	PreferredProject p(100, 100, 100);
	RegularProject r(100, 100, 100);

	CustomerProject *p1 = &p;
	CustomerProject *p2 = &r;

	printf("Preferred Project Cost: %f\n", p1->billAmount());
	printf("Regular Project Cost: %f\n", p2->billAmount());
	return 0;
}
