#include <Control.h>
#include <CmdlineUI.h>


int main(void)
{
	Control * control = new Control();
	CmdlineUI cmdlineUI(control);
	cmdlineUI.run();

	return 0;
}

