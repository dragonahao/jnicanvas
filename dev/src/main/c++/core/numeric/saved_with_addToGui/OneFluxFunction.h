#include <datamodel>
#include <iostream>
#include <string>

using namespace std;


#ifndef _OneFluxFunction
#define _OneFluxFunction

class OneFluxFunction : public AuxMethodSettings
{

private:
	string name_;
	FloatParameter psi;

public:
	OneFluxFunction(string _n);
	string name(void);
	void show(void);


};

#endif
