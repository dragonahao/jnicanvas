#ifndef _XmlUI
#define _XmlUI

#include <string>
#include <UI.h>
#include <Control.h>

using namespace std;


class XmlUI : public UI
{
private:
	string command(string cmd_);		// receive imput commands
	string help(void);			// show help

public:
	XmlUI(Control * control_);
	void run(void);				// Even Loop

};

#endif
