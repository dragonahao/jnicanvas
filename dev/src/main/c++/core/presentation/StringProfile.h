#ifndef _StringProfile
#define _StringProfile

#include <string>
#include <iostream>
#include <ProfileSettings.h>

using namespace std;


class StringProfile : public ProfileSettings
{
private:
	string name_;
	string value_, default_value_;

public:
	StringProfile(int _ID, int _t, bool _vs, bool _c, string _n, string _v, string _d);

	string value (void);
	string default_value (void);
	string name (void);

};

#endif
