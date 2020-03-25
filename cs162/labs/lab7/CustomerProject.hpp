#ifndef CUSTOMERPROJECT_HPP
#define CUSTOMERPROJECT_HPP

class CustomerProject
{
protected:
	double hours, materials, transportation;
public:
	CustomerProject(double, double, double);
	void setHours(double);
	void setMaterials(double);
	void setTransportation(double);
	double getHours();
	double getMaterials();
	double getTransportation();

	virtual double billAmount() = 0;
};

#endif
