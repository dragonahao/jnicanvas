#ifndef _FloatProfile
#define _FloatProfile

#include <string>
#include <iostream>
#include <ProfileSettings.h>

using namespace std;


class FloatProfile : public ProfileSettings
{
private:
	string name_;
	float value_, default_value_, min_, max_;

public:
	FloatProfile(int _ID, int _t, bool _vs, bool _c, string _n, float _v, float _d, float _mn, float _mx);

	float value (void);
	float default_value (void);
	float min (void);
	float max (void);
	string name (void);

};

#endif
