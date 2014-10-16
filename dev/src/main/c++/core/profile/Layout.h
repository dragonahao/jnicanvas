#ifndef _Layout
#define _Layout

#include <presentation>


class Layout
{
private:
	UISpec * uispec_;
	Profile * profile_;
	vector <int> ID_;


public:
	Layout();

	void panelBegin(string s_);
	void panelEnd(void);
	void addChild(string s_);


};

#endif
