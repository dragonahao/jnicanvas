#ifndef _BoolSettings
#define _BoolSettings

#include <string>
#include <iostream>
#include <Settings.h>
#include <BoolProfile.h>

using namespace std;


class BoolSettings : public Settings
{


public:
	BoolSettings();

	string toXML(int level = 0);
	BoolProfile * profile(void);

        virtual string parent() const = 0;
	virtual bool value () const = 0;
	virtual void value (bool value_) = 0;
        virtual bool default_value() const = 0;
        virtual void reset() = 0;
};

#endif
