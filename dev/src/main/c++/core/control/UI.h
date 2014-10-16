#ifndef _UI
#define _UI

#include <string>
#include <Control.h>

using namespace std;


class UI
{
protected:
	Control * control;

public:
	UI(Control * _control);

	virtual void run(void) = 0;	// Event Loop

};

#endif
