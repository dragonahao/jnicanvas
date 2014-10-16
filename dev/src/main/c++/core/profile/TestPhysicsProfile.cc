#include <TestPhysicsProfile.h>


TestPhysicsProfile :: TestPhysicsProfile()
{
}

ProfileSettings * TestPhysicsProfile :: profile()
{
	UISpec * _uispec = UISpec :: instance();


	ProfileSettings * _profile = _uispec->profile(0);

	Profile *obj = dynamic_cast<Profile*> (_profile);

	obj->addToProfile(*_uispec->profile(1));


	return _profile;
}
