#ifndef _Settings
#define _Settings

#include <string>
#include <vector>
#include <iostream>
#include <SettingsType.h>
#include <ProfileSettings.h>

using namespace std;


class Settings
{

private:
	int ID_;
	int type_;
	bool visible_;
	bool changeable_;

public:
	Settings(int _t);
	Settings * object(void);

	int ID(void);

	int type(void);
	void type(int _t);
	string typeName(void);

	bool visible(void);
	void visible(bool _v);

	bool changeable(void);
	void changeable(bool _c);

	virtual string name(void) const = 0;
	virtual string toXML(int _level = 0) = 0;
	virtual ProfileSettings * profile(void) = 0;
	virtual ProfileSettings * profile(int _recur) = 0;
};

#endif
