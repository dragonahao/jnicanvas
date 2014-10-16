#include <string>
#include <CreateMacroCommand.h>

using namespace std;

CreateMacroCommand :: CreateMacroCommand(Settings * settings_, int ID_, string macroName_) :
	settings(settings_),
	name("CREATE_MACRO"),
	ID(ID_),
	macroName(macroName_)
{
}

void CreateMacroCommand :: execute()
{
	MacroMethod *obj = dynamic_cast<MacroMethod*> (settings);
	obj->createMacro(macroName);
}

string CreateMacroCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
