#ifndef _UISpec
#define _UISpec

#include <string>
#include <vector>
#include <iostream>
#include <Settings.h>
#include <ProfileSettings.h>

using namespace std;


//
// IMPORTANT!! This implementation is NOT thread safe!
//             Google for an example of a thread safe one.
//

class UISpec /* This is a singleton class */
{
private:
	static bool instanceFlag;
	static UISpec *uispec;
	vector <Settings *> settings_;
	UISpec() { /* private constructor */ }

public:
	~UISpec() { instanceFlag = false; }
	static UISpec* instance();
	int auto_register(Settings &);
	int auto_register(Settings *);

	/* gui configration functions */
	string traverse(void);
	string toXML(int _ID);
	ProfileSettings * profile(int _ID);
	ProfileSettings * profile(string _name);

	/* callback functions */
	Settings * settings(int _ID);
	Settings * settings(string _name);

};


/*  Static function to register Settings objects  */

int auto_register(Settings &);
int auto_register(Settings *);

#endif
