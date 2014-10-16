#include <BoolProfile.h>


BoolProfile :: BoolProfile(int _ID, int _t, bool _vs, bool _c, string _n, bool _v, bool _d)
{
	// SettingsProfile protected data
	ID_ = _ID;
	type_ = _t;
	visible_ = _v;
	changeable_ = _c;

	// BoolProfile (this class) private data
	name_ = _n;
	value_ = _v;
	default_value_ = _d;
}


string BoolProfile :: name()
{
        return name_;
}
