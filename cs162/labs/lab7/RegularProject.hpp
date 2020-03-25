#ifndef REGULARPROJECT_HPP
#define REGULARPROJET_HPP

#include "CustomerProject.hpp"

class RegularProject : public CustomerProject
{
public:
	RegularProject(double, double, double);
	double billAmount(); // override
};

#endif
