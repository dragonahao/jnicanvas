#include <Command.h>
#include <Settings.h>
#include <IntSettings.h>

#ifndef _IntSetCommand
#define _IntSetCommand


class IntSetCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	int value;

public:
	IntSetCommand(Settings * settings_, int ID_, int value_);
	void execute(void);
	string toXML(void);

};

#endif
