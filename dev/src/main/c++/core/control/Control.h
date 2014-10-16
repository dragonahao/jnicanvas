#ifndef _Control
#define _Control

#include <string>
#include <vector>
#include <Physics.h>

using namespace std;


class Control
{
private:
	Physics *physics_;
	UISpec *uispec_;						// users interface specification
	
public:
	Control();


	// Control commands
	vector <string> availablePhysics(void);
	void createPhysics(string _name);				// create a new physocs
	bool checkPhysics(void);					// check if physics is already reated


	// Callback commands from Presentation Layer
	void calc(int _ID, float _x, float _y);				// calc that requires 1 coord
	void calc(int _ID, float _x1, float _y1, float _x2, float _y2);	// calc that requires 2 coords
	void set(int _ID, int _value);					// set int parameter
	void set(int _ID, float _value);				// set float parameter
	void set(int _ID, string _value);				// set string parameter
	void set(int _ID, bool _value);					// set bool parameter
	void createMacro(int _ID, string _name);			// create or add a command to a macro
	void addToMacro(int _ID, int _macroID, int _cmdID);		// add a command to a macro


	// UISpec commands
	string showUISpecXML(int _ID);					// show user interface specification
	string listUISpec(void);					// list interface specification elements
	Settings *object(int _ID);					// return a parameter or a method


	// Dispatcher commands
	string listCommandHistory(void);				// list command history
	//Curve getCurve(void);						// get the result from the last calc command
	//Info getInfo(void);						// get the result from the last ?info? command


};

#endif
