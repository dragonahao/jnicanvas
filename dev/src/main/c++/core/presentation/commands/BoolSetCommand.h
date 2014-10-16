#include <Command.h>
#include <Settings.h>
#include <BoolSettings.h>

#ifndef _BoolSetCommand
#define _BoolSetCommand


class BoolSetCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	bool value;

public:
	BoolSetCommand(Settings * settings_, int ID_, bool value_);
	void execute(void);
	string toXML(void);

};

#endif
