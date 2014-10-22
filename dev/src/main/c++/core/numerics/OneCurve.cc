#include <OneCurve.h>


OneCurve :: OneCurve(string _n, OneFluxFunction * oneFF_) :
	name_(_n),
	oneFF(oneFF_),
	x("X", 0.4, 0.0, 10.0),
	family("Family", 0, 0, 1)
{
//	addToUI(x);
//	addToUI(family);
//	addToUI(*oneFF);

//	family.type(SPINNER);
}


string OneCurve :: name(void) const
{
	return name_;
}

void OneCurve :: setFF(OneFluxFunction *oneFF_)
{
	oneFF = oneFF_;
}


void OneCurve :: show(void)
{
	cout << "Show in OneCurve" << endl;
	string xml = x.toXML();
	cout << xml;
}


string OneCurve :: calc(float x_, float y_)
{
	cout << endl << endl << "   - Running Calc in OneCurve (" << x_ << ", " << y_ << ")..." << endl << endl;

	return "OK";
}



