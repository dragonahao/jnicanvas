#ifndef _MacroCalcMethod
#define _MacroCalcMethod

#include <string>
#include <CalcMethodSettings.h>
#include <UISpec.h>

using namespace std;


class MacroCalcMethod : public CalcMethodSettings
{
private:
	string name_;
	UISpec *uispec_;
	vector <CalcMethodSettings *> calcs_;

public:
	MacroCalcMethod(string _n);

	string name(void) const;
	void addCalcToMacro(int _ID);

	string calc(float _x, float _y);
};

#endif
