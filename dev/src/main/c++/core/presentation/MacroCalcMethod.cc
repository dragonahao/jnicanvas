#include <MacroCalcMethod.h>


MacroCalcMethod :: MacroCalcMethod(string _n) :
	name_(_n)
{
	uispec_ = UISpec :: instance(); // UISpec is a singleton class
}


void MacroCalcMethod :: addCalcToMacro(int _ID)
{
	Settings *calcMethod = uispec_->settings(_ID);
	CalcMethodSettings *obj = dynamic_cast<CalcMethodSettings*> (calcMethod);
	calcs_.push_back(obj);
	// Do not add to UI!
	//addToUI(static_cast<Settings&>(*obj));
}


string MacroCalcMethod :: calc(float _x, float _y)
{
	for ( int i=0; i<calcs_.size(); i++ )
	{
		calcs_[i]->calc(_x, _y);
	}

	return "OK";
}


string MacroCalcMethod :: name(void) const
{
	return name_;
}


