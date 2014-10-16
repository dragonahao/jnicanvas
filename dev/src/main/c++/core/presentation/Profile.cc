#include <Profile.h>


Profile :: Profile(int _ID, int _t, string _n, bool _v, bool _c)
{
	// ProfileSettings protected data
	ID_ = _ID;
	type_ = _t;
	visible_ = _v;
	changeable_ = _c;

	// Profile (this class) private data
	name_ = _n;
}


Profile :: Profile(const Profile & _p)
{
	ID_ = _p.ID_;
	type_ = _p.type_;
	visible_ = _p.visible_;
	changeable_ = _p.changeable_;
	name_ = _p.name_;
}


void Profile :: addToProfile(ProfileSettings & _profileSettings)
{
	profileSettings_.push_back(& _profileSettings);
}


string Profile :: name(void)
{
	return name_;
}

