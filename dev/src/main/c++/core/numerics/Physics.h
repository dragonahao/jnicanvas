#include <iostream>
#include <datamodel>
#include <OneCurve.h>
#include <OneFluxFunction.h>
#include <MacroMethod.h>


using namespace std;

#ifndef _Physics
#define _Physics

class Physics : public PhysicsSettings
{

private:
	string name_;
	IntParameter dim;
	FloatParameter precision;

	OneFluxFunction *oneFF;
	OneCurve oneC;

//	MacroMethod macros;
public:
	Physics();
	string name(void) const;
	void show(void);

};

#endif
