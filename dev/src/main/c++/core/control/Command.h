#ifndef _Command
#define _Command

#include <string>

using namespace std;


class Command
{

public:
	Command();
	virtual void execute(void) = 0;
	virtual string toXML(void) = 0;

};

#endif
