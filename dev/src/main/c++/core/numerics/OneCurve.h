#include <iostream>
#include <string>
#include <datamodel>
#include <OneFluxFunction.h>

using namespace std;

#ifndef _OneCurve
#define _OneCurve

class OneCurve : public CalcMethodSettings
{

private:
	string name_;
	FloatParameter x;
	IntParameter family;
	OneFluxFunction *oneFF;

public:
	OneCurve(string _n, OneFluxFunction *oneFF_);
	string name(void) const;
	void setFF(OneFluxFunction *oneFF_);
	void show(void);
	
	string calc(float x_, float y_);


};

#endif
