#include <string>
#include <CalcCommand.h>

using namespace std;

CalcCommand :: CalcCommand(Settings * settings_, int ID_, float x_, float y_) :
	settings(settings_),
	name("CALC"),
	ID(ID_),
	x(x_),
	y(y_)
{
}

void CalcCommand :: execute()
{
	// Old version: uispec->calc(ID, x, y);
	CalcMethodSettings *obj = dynamic_cast<CalcMethodSettings*> (settings);
	obj->calc(x, y);
}

string CalcCommand :: toXML()
{
	string xml;
	xml = "<xml CMD='" + name + "'>\n";
	return xml;
}
