#include <string>
#include <FloatSetCommand.h>

using namespace std;

FloatSetCommand :: FloatSetCommand(Settings * settings_, int ID_, float value_) :
	settings(settings_),
	name("SET"),
	ID(ID_),
	value(value_)
{
}

void FloatSetCommand :: execute()
{
	FloatSettings *obj = dynamic_cast<FloatSettings*> (settings);
	obj->value(value);
}

string FloatSetCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
