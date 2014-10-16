#include <string>
#include <AddToMacroCommand.h>

using namespace std;

AddToMacroCommand :: AddToMacroCommand(Settings * settings_, int macroID_, int cmdID_) :
	settings(settings_),
	name("ADD_TO_MACRO"),
	macroID(macroID_),
	cmdID(cmdID_)
{
}

void AddToMacroCommand :: execute()
{
	MacroMethod *obj = dynamic_cast<MacroMethod*> (settings);
	obj->addToMacro(macroID, cmdID);
}

string AddToMacroCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
