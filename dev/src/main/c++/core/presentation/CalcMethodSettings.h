#ifndef _CalcMethodSettings
#define _CalcMethodSettings

#include <Configurable.h>
#include <string>
#include <iostream>

using namespace std;


class CalcMethodSettings : public Configurable
{

public:
	CalcMethodSettings();
	void show(void);

	virtual string calc(float x_, float y_) = 0;

};

#endif
