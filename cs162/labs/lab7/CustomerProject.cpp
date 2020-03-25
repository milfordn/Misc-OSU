#include "CustomerProject.hpp"

CustomerProject::CustomerProject(double hours, double mats, double transport)
{
	this->hours = hours;
	this->materials = mats;
	this->transportation = transport;
}

void CustomerProject::setHours(double h)
{
	hours = h;
}

void CustomerProject::setMaterials(double m)
{
	materials = m;
}

void CustomerProject::setTransportation(double t)
{
	transportation = t;
}

double CustomerProject::getHours()
{
	return hours;
}

double CustomerProject::getMaterials()
{
	return materials;
}

double CustomerProject::getTransportation()
{
	return transportation;
}
