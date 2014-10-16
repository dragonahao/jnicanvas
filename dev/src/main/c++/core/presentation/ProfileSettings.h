#ifndef _ProfileSettings
#define _ProfileSettings

#include <string>
#include <vector>
#include <iostream>
#include <SettingsType.h>

using namespace std;


class ProfileSettings
{

protected:
	int ID_;
	int type_;
	bool visible_;
	bool changeable_;

public:
	ProfileSettings();

	int ID(void);
	int type(void);
	string typeName(void);
	bool visible(void);
	bool changeable(void);

	virtual string name(void) = 0;

};

#endif
