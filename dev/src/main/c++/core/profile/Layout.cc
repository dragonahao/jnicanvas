#include <Layout.h>


Layout :: Layout()
{
	uispec_ = UISpec :: instance();
	profile_ = dynamic_cast<Profile*> (uispec_->profile(0));
	ID_.push_back(0);
}


void Layout :: panelBegin(string s_)
{
	Profile *p_ = dynamic_cast<Profile*> (uispec_->profile(s_));
	profile_->addToProfile(*p_);

	ID_.push_back(p_->ID());

}


void Layout :: panelEnd(void)
{
	ID_.pop_back();
}


void Layout :: addChild(string s_)
{
	profile_->addToProfile(*uispec_->profile(s_));
}


