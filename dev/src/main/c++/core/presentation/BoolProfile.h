#ifndef _BoolProfile
#define _BoolProfile

#include <string>
#include <iostream>
#include <ProfileSettings.h>

using namespace std;


class BoolProfile : public ProfileSettings
{
private:
	string name_;
	bool value_, default_value_;

public:
	BoolProfile(int _ID, int _t, bool _vs, bool _c, string _n, bool _v, bool _d);

	bool value (void);
	bool default_value (void);
	string name (void);

};

#endif
