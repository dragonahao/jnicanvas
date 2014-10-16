#ifndef _StringSettings
#define _StringSettings

#include <string>
#include <iostream>
#include <Settings.h>
#include <StringProfile.h>

using namespace std;


class StringSettings : public Settings
{


public:
	StringSettings();

	string toXML(int level = 0);
	StringProfile * profile(void);

        virtual string parent() const = 0;
	virtual string value () const = 0;
	virtual void value (string value_) = 0;
        virtual string default_value() const = 0;
        virtual void reset() = 0;
};

#endif
