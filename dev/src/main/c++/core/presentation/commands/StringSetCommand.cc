#include <string>
#include <StringSetCommand.h>

using namespace std;

StringSetCommand :: StringSetCommand(Settings * settings_, int ID_, string value_) :
	settings(settings_),
	name("SET"),
	ID(ID_),
	value(value_)
{
}

void StringSetCommand :: execute()
{
	StringSettings *obj = dynamic_cast<StringSettings*> (settings);
	obj->value(value);
}

string StringSetCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
