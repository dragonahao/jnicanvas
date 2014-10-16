#include <Command.h>
#include <Settings.h>
#include <MacroMethod.h>

#ifndef _AddToMacroCommand
#define _AddToMacroCommand


class AddToMacroCommand : public Command
{
private:
	Settings * settings;
	string name;
	int macroID;
	int cmdID;

public:
	AddToMacroCommand(Settings * settings_, int macroID_, int cmdID_);
	void execute(void);
	string toXML(void);

};

#endif
