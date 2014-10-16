#ifndef _FloatSettings
#define _FloatSettings

#include <string>
#include <iostream>
#include <Settings.h>
#include <FloatProfile.h>

using namespace std;


class FloatSettings : public Settings
{

public:
	FloatSettings();

	string toXML(int level = 0);
	FloatProfile * profile(void);

        virtual string parent() const = 0;
        virtual void parent(string &p) = 0;
        virtual double min() const = 0;
        virtual void min(double m) = 0;
        virtual double max() const = 0;
        virtual void max(double m) = 0;
        virtual double value() const = 0;
        virtual void value(double v) = 0;
        virtual double default_value() const = 0;
        virtual void reset() = 0;
};

#endif
