#ifndef _CmdlineUI
#define _CmdlineUI

#include <UI.h>
#include <Control.h>
#include <string>

using namespace std;


class CmdlineUI : public UI
{
private:
	string command(string cmd_);		// receive imput commands
	string help(void);			// show help

public:
	CmdlineUI(Control * control_);
	void run(void);				// Even Loop

};

#endif
