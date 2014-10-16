#ifndef _IntProfile
#define _IntProfile

#include <string>
#include <iostream>
#include <ProfileSettings.h>

using namespace std;


class IntProfile : public ProfileSettings
{
private:
	string name_;
	int value_, default_value_, min_, max_;

public:
	IntProfile(int _ID, int _t, bool _vs, bool _c, string _n, int _v, int _d, int _mn, int _mx);

	int value (void);
	int default_value (void);
	int min (void);
	int max (void);
	string name (void);

};

#endif
