#include <string>
#include <BoolSetCommand.h>

using namespace std;

BoolSetCommand :: BoolSetCommand(Settings * settings_, int ID_, bool value_) :
	settings(settings_),
	name("SET"),
	ID(ID_),
	value(value_)
{
}

void BoolSetCommand :: execute()
{
	BoolSettings *obj = dynamic_cast<BoolSettings*> (settings);
	obj->value(value);
}

string BoolSetCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
