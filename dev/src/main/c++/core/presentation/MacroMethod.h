#ifndef _MacroMethod
#define _MacroMethod

#include <string>
#include <UISpec.h>
#include <AuxMethodSettings.h>
#include <MacroCalcMethod.h>

using namespace std;


class MacroMethod : public AuxMethodSettings
{
private:
	string name_;
	vector <MacroCalcMethod *> macros_;

public:
	MacroMethod(string _n);

	string name(void);
	void createMacro(string _n);
	void addToMacro(int _macroID, int _cmdID);

};

#endif
