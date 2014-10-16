#include <FloatProfile.h>


FloatProfile :: FloatProfile(int _ID, int _t, bool _vs, bool _c, string _n, float _v, float _d, float _mn, float _mx)
{
	// SettingsProfile protected data
	ID_ = _ID;
	type_ = _t;
	visible_ = _vs;
	changeable_ = _c;

	// FloatProfile (this class) private data
	name_ = _n;
	value_ = _v;
	default_value_ = _d;
	min_ = _mn;
	max_ = _mx;
}


string FloatProfile :: name()
{
        return name_;
}
