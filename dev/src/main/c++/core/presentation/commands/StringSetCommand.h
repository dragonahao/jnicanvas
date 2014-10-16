#include <Command.h>
#include <Settings.h>
#include <StringSettings.h>

#ifndef _StringSetCommand
#define _StringSetCommand


class StringSetCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	string value;

public:
	StringSetCommand(Settings * settings_, int ID_, string value_);
	void execute(void);
	string toXML(void);

};

#endif
