#include <string>
#include <IntSetCommand.h>

using namespace std;

IntSetCommand :: IntSetCommand(Settings * settings_, int ID_, int value_) :
	settings(settings_),
	name("SET"),
	ID(ID_),
	value(value_)
{
}

void IntSetCommand :: execute()
{
	IntSettings *obj = dynamic_cast<IntSettings*> (settings);
	obj->value(value);
}

string IntSetCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
