#include "PreferredProject.hpp"

PreferredProject::PreferredProject(double hours, double mats, double transport) : CustomerProject(hours, mats, transport) {}

double PreferredProject::billAmount()
{
	double ceilingHours;

	if(hours > 100)
		ceilingHours = 100;
	else
		ceilingHours = hours;
	return 0.85 * materials + 0.9 * transportation + ceilingHours * 80;
}
