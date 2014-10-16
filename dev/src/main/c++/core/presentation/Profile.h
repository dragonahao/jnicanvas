#ifndef _Profile
#define _Profile

#include <string>
#include <vector>
#include <ProfileSettings.h>

using namespace std;


class Profile : public ProfileSettings
{

private:
	string name_;
	vector <ProfileSettings *> profileSettings_;

public:
	Profile(int _ID, int _t, string _n, bool _v, bool _c);
	Profile(const Profile & _profile);
	void addToProfile(ProfileSettings & _profileSettings);

	string name(void);

};

#endif
