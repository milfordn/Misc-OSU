#include "RegularProject.hpp"

RegularProject::RegularProject(double hours, double materials, double transportation) : CustomerProject(hours, materials, transportation) {}

double RegularProject::billAmount()
{
	return materials + transportation + 80 * hours;
}
