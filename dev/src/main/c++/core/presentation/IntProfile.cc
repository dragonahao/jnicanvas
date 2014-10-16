#include <IntProfile.h>


IntProfile :: IntProfile(int _ID, int _t, bool _vs, bool _c, string _n, int _v, int _d, int _mn, int _mx)
{
	// SettingsProfile protected data
	ID_ = _ID;
	type_ = _t;
	visible_ = _vs;
	changeable_ = _c;

	// IntProfile (this class) private data
	name_ = _n;
	value_ = _v;
	default_value_ = _d;
	min_ = _mn;
	max_ = _mx;
}


string IntProfile :: name()
{
        return name_;
}
