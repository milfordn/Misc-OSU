#ifndef PREFERREDPROJECT_HPP
#define PREFERREDPROJECT_HPP

#include "CustomerProject.hpp"

class PreferredProject : public CustomerProject
{
public:
	PreferredProject(double, double, double);
	double billAmount(); //override
};

#endif
