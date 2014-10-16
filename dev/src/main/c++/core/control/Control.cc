#include <iostream>
#include <Control.h>
#include <Dispatcher.h> 
#include <commands>

using namespace std;


Control :: Control()
{
	physics_ = NULL;
	uispec_ = UISpec :: instance(); // UISpec is a singleton class
}


////////////////////////////////////////////////////////////////////////////
//
// CONTROL COMMANDS
//
////////////////////////////////////////////////////////////////////////////

// list available physics
vector <string> Control :: availablePhysics(void)
{
	vector <string> physicsList;

	physicsList.push_back("TestPhys");
	physicsList.push_back("Quad");
	physicsList.push_back("Quad2");

	return physicsList;
}

// create a new physics
void Control :: createPhysics(string _name)
{
	if ( _name ==  "TestPhys" )
		physics_ = new Physics();

	else if ( _name ==  "Quad" )
		physics_ = new Physics();

	else if ( _name ==  "Quad2" )
		physics_ = new Physics();

	else
		cout << "Error: Unknown physics name!" << endl << endl;
}


// check if physics is already created
bool Control :: checkPhysics(void)
{
	if ( physics_ == NULL )
		return false;
	else
		return true;
}



// get result from the last calc command
/*
Curve Control :: getCurve(void)
{
	cout << endl << "getCurve() NOT IMPLEMENTED!" << endl;
}

// get result from the last calc command
Info Control :: getInfo(void)
{
	cout << endl << "getInfo() NOT IMPLEMENTED!" << endl;
}

*/


////////////////////////////////////////////////////////////////////////////
// 
// CALLBACK COMMANDS
//
////////////////////////////////////////////////////////////////////////////

// calc that requires 1 coord
void Control :: calc(int _ID, float _x, float _y)
{
	CalcCommand * command = new CalcCommand(uispec_->settings(_ID), _ID, _x, _y);
	submit(command);
}

// calc that requires 2 coords
void Control :: calc(int _ID, float _x1, float _y1, float _x2, float _y2)
{
	cout << endl << "NOT IMPLEMENTED!" << endl;
}

// set int parameter
void Control :: set(int _ID, int _value)
{
	IntSetCommand * command = new IntSetCommand(uispec_->settings(_ID), _ID, _value);
	submit(command);
}

// set float parameter
void Control :: set(int _ID, float _value)
{
	FloatSetCommand * command = new FloatSetCommand(uispec_->settings(_ID), _ID, _value);
	submit(command);
}

// set string parameter
void Control :: set(int _ID, string _value)
{
	StringSetCommand * command = new StringSetCommand(uispec_->settings(_ID), _ID, _value);
	submit(command);
}


// set bool parameter
void Control :: set(int _ID, bool _value)
{
	BoolSetCommand * command = new BoolSetCommand(uispec_->settings(_ID), _ID, _value);
	submit(command);
}


// create a macro
void Control :: createMacro(int _ID, string _name)
{
	CreateMacroCommand * command = new CreateMacroCommand(uispec_->settings(_ID), _ID, _name);
	submit(command);
}


// add a command to a macro
void Control :: addToMacro(int _ID, int _macroID, int _cmdID)
{
	AddToMacroCommand * command = new AddToMacroCommand(uispec_->settings(_ID), _macroID, _cmdID);
	submit(command);
}


////////////////////////////////////////////////////////////////////////////
//
// UISpec COMMANDS
//
////////////////////////////////////////////////////////////////////////////

// show user interface specification
string Control :: showUISpecXML(int _ID)
{
	return uispec_->toXML(_ID);

}


// list interface specification elements
string Control :: listUISpec(void)
{
	return uispec_->traverse();
}


// return a parameter or a method
Settings * Control :: object(int _ID)
{
	return uispec_->settings(_ID);
}


///////////////////////////////////////////////////////////////////
//
// DISPATCHER COMMANDS
//
///////////////////////////////////////////////////////////////////

string Control :: listCommandHistory(void)
{
	Dispatcher *dispatcher;
	dispatcher = Dispatcher :: instance();
	return dispatcher->listHistory();
}


