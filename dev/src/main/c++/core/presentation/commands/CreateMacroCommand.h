#include <Command.h>
#include <Settings.h>
#include <MacroMethod.h>

#ifndef _CreateMacroCommand
#define _CreateMacroCommand


class CreateMacroCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	string macroName;

public:
	CreateMacroCommand(Settings * settings_, int ID_, string macroName);
	void execute(void);
	string toXML(void);

};

#endif
