#include <Command.h>
#include <Settings.h>
#include <CalcMethodSettings.h>

#ifndef _CalcCommand
#define _CalcCommand


class CalcCommand : public Command
{
private:
	Settings * settings;
	string name;
	int ID;
	float x, y;

public:
	CalcCommand(Settings * settings_, int ID_, float x_, float y_);
	void execute(void);
	string toXML(void);

};

#endif
