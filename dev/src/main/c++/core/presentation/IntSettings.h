#ifndef _IntSettings
#define _IntSettings

#include <string>
#include <iostream>
#include <Settings.h>
#include <IntProfile.h>

using namespace std;


class IntSettings : public Settings
{

public:
	IntSettings();

	string toXML(int level = 0);
	IntProfile * profile(void);

        virtual string parent() const = 0;
        virtual void parent(string &p) = 0;
        virtual int min() const = 0;
        virtual void min(int mn) = 0;
        virtual int max() const = 0;
        virtual void max(int mx) = 0;
        virtual int value() const = 0;
        virtual void value(int v) = 0;
        virtual int default_value() const = 0;
        virtual void reset() = 0;
};

#endif
