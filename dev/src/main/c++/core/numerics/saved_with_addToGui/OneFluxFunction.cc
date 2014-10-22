#include <OneFluxFunction.h>


OneFluxFunction :: OneFluxFunction(string _n) : 
	name_(_n),
	psi("Psi", 0.9, 0.0, 1.0)
{
	addToUI(psi);
}


string OneFluxFunction :: name(void)
{
	return name_;
}


void OneFluxFunction :: show(void)
{
	cout << "in OneFluxFunction\n";
	string xml = psi.toXML();
	cout << xml;
}


