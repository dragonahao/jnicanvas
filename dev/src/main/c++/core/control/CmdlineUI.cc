#include <iostream>
#include <CmdlineUI.h>

using namespace std;


CmdlineUI :: CmdlineUI(Control * control_) :
	UI(control_)
{
}


// Event Loop
void CmdlineUI :: run()
{
	string cmd_;

	cout << endl << "    RPn command interface" << endl << endl;

	while ( 1 ) // Event loop
	{
		cout << "Enter command: ";
		cin >> cmd_;
		if ( cmd_ == "QUIT" )
		{
			cout << endl;
			break;
		}
		cout << command(cmd_);
		cout << endl << endl << "===================================" << endl << endl;
	}
}


// receive command from a string
string CmdlineUI :: command(string cmd_)
{
	if ( cmd_ ==  "HELP" )
	{
		return help();
	}
	else if ( cmd_ ==  "LIST" )
	{
		vector <string> list;
		list = control->availablePhysics();

		cout << endl << "Available physics:" << endl << endl;
		for (int p = 0; p < list.size(); p++)
			cout << "    - " << list[p] << endl;

		return "";

	}
	else if ( cmd_ ==  "NEW" )
	{
		if ( control->checkPhysics() )
			return "Physics already created!\n";
		string name_;
		control->availablePhysics();
		cout << "Enter physics name: ";
		cin >> name_;
		control->createPhysics(name_);
		return "OK\n\n";
		
	}
	else if ( cmd_ ==  "CALC" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		float x_, y_;
		cout << "Enter object ID: ";
		cin >> ID_;
		cout << "Enter coords(x,y): ";
		cin >> x_ >> y_;
		control->calc(ID_, x_, y_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "CALC2" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		// dummy
		control->calc(0, .0,.0,.0,.0);
	}
	else if ( cmd_ ==  "RES" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		// dummy
		//Curve getCurve();
	}
	else if ( cmd_ ==  "SETI" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		int value_;
		cout << "Enter object ID: ";
		cin >> ID_;
		cout << "Enter new value: ";
		cin >> value_;
		control->set(ID_, (int)value_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "SETF" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		float value_;
		cout << "Enter object ID: ";
		cin >> ID_;
		cout << "Enter new value: ";
		cin >> value_;
		control->set(ID_, (float)value_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "SETS" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		string value_;
		cout << "Enter object ID: ";
		cin >> ID_;
		cout << "Enter new value: ";
		cin >> value_;
		control->set(ID_, (string)value_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "SETB" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		string namevalue_;
		bool value_;
		cout << "Enter object ID: ";
		cin >> ID_;
		cout << "Enter new value: ";
		cin >> namevalue_;
		if ( namevalue_ == "TRUE" )
			value_ = true;
		else
			value_ = false;
		control->set(ID_, (bool)value_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "MACRO" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		string value_;
		cout << "Enter macro panel ID: ";
		cin >> ID_;
		cout << "Enter new macro name: ";
		cin >> value_;
		control->createMacro(ID_, (string)value_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "ADDM" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		int macroID_;
		int cmdID_;
		cout << "Enter macro panel ID: ";
		cin >> ID_;
		cout << "Enter macro command ID: ";
		cin >> macroID_;
		cout << "Enter calc command ID: ";
		cin >> cmdID_;
		control->addToMacro(ID_, macroID_, cmdID_);
		return "OK\n\n";
	}
	else if ( cmd_ ==  "UISPEC" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		int ID_;
		cout << "Enter object ID: ";
		cin >> ID_;
		return control->showUISpecXML(ID_);
	}
	else if ( cmd_ ==  "LISTUI" )
	{
		if ( not control->checkPhysics() )
			return "Physics not created!\n";
		return control->listUISpec();
	}
	else if ( cmd_ ==  "HIST" )
	{
		return control->listCommandHistory();
	}
	else
		return "\nError: CmdlineUI not found!\n";

}

// show help
string CmdlineUI :: help(void)
{
	cout << endl;
	cout << "\t" << "HELP"      << "	- Show help" << endl;
	cout << "\t" << "LIST"      << "	- List available physics" << endl;
	cout << "\t" << "NEW"       << "	- Create a new physocs" << endl;
	cout << "\t" << "CALC"      << "	- Calc that requires 1 coord" << endl;
	cout << "\t" << "CALC2"     << "	- Calc that requires 2 coords" << endl;
	cout << "\t" << "RES"       << "	- get the result from the last command" << endl;
	cout << "\t" << "SETI"      << "	- Set int parameter" << endl;
	cout << "\t" << "SETF"      << "	- Set float parameter" << endl;
	cout << "\t" << "SETS"      << "	- Set string parameter" << endl;
	cout << "\t" << "SETB"      << "	- Set bool parameter" << endl;
	cout << "\t" << "MACRO"     << "	- Create a macro" << endl;
	cout << "\t" << "ADDM"      << "	- Add a command to a macro" << endl;
	cout << "\t" << "UISPEC"    << "	- Show user interface specification" << endl;
	cout << "\t" << "LISTUI"    << "	- List interface specification elements" << endl;
	cout << "\t" << "HIST"      << "	- List command history" << endl;
	cout << "\t" << "QUIT"      << "	- Quit RPn" << endl;
	// Not to be used by command line input
	//	cout << "   " << "OBJ"   << " - Return a parameter or a method" << endl;
	cout << endl;

	return "OK\n\n";
}


