#include <Command.h>
#include <Settings.h>
#include <FloatSettings.h>

#ifndef _FloatSetCommand
#define _FloatSetCommand


class FloatSetCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	float value;

public:
	FloatSetCommand(Settings * settings_, int ID_, float value_);
	void execute(void);
	string toXML(void);

};

#endif
