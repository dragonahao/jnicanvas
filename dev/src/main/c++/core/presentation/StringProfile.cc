#include <StringProfile.h>


StringProfile :: StringProfile(int _ID, int _t, bool _vs, bool _c, string _n, string _v, string _d)
{
	// SettingsProfile protected data
	ID_ = _ID;
	type_ = _t;
	visible_ = _vs;
	changeable_ = _c;

	// StringProfile (this class) private data
	name_ = _n;
	value_ = _v;
	default_value_ = _d;
}


string StringProfile :: name()
{
        return name_;
}
