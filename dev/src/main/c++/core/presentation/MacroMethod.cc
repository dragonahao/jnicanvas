#include <sstream>
#include <MacroMethod.h>

using namespace std;


MacroMethod :: MacroMethod(string _n) :
	name_(_n)
{
}


void MacroMethod :: createMacro(string _n)
{
	MacroCalcMethod * calc = new MacroCalcMethod(_n);
	macros_.push_back(calc);
	addToUI(static_cast<Settings&>(*macros_[macros_.size()-1]));
}


void MacroMethod :: addToMacro(int _macroID, int _cmdID)
{
	for (int i=0; i<macros_.size(); i++)
	{
		if ( macros_[i]->ID() == _macroID )
			macros_[i]->addCalcToMacro(_cmdID);
	}
}


string MacroMethod :: name(void)
{
	return name_;
}


