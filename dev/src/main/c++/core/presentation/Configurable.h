#ifndef _Configurable
#define _Configurable

#include <string>
#include <vector>
#include <Settings.h>
#include <ProfileSettings.h>
#include <Profile.h>

using namespace std;


class Configurable : public Settings
{

private:
	vector <Settings *> settings_;

public:
	Configurable(int _t);
	void addToUI(Settings & _settings);
	void addToUI(vector <Settings *> _settings);
	void addToUI(Settings & _settings, bool _v, bool _c);

	string toXML(int _level);
	ProfileSettings * profile(void);

};

#endif
