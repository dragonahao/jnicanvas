#include <XmlUI.h>
#include <iostream>

using namespace std;


XmlUI :: XmlUI(Control * control_) :
	UI(control_)
{
}

void XmlUI :: run()
{
	string xml, cmd;

	cout  << "    RPn command interface (XML)"  << endl << endl;

	while ( 1 ) // Event loop
	{
		cin >> xml;
		//cmd = parse(xml);
		command(cmd);
	}
}


// receive command from a string
string XmlUI :: command(string cmd_)
{
	if ( cmd_ ==  "HELP" )
	{
		help();
	}
	else if ( cmd_ ==  "LIST" )
	{
		vector <string> list;
		list = control->availablePhysics();
	}
	else if ( cmd_ ==  "NEW" )
	{
		string name_;
		control->createPhysics(name_);
	}
	else if ( cmd_ ==  "CALC" )
	{
		int ID_;
		float x_, y_;
		control->calc(ID_, x_, y_);
	}
	else if ( cmd_ ==  "CALC2" )
	{
		// dummy
		control->calc(0, .0,.0,.0,.0);
	}
	else if ( cmd_ ==  "RES" )
	{
		// dummy
		//Curve getResult();
	}
	else if ( cmd_ ==  "SETI" )
	{
		int ID_;
		int value_;
		control->set(ID_, (int)value_);
	}
	else if ( cmd_ ==  "SETF" )
	{
		int ID_;
		float value_;
		control->set(ID_, (float)value_);
	}
	else if ( cmd_ ==  "SETS" )
	{
		// dummy
		control->set(0, "DUMMY");
	}
	else if ( cmd_ ==  "MACRO" )
	{
	}
	else if ( cmd_ ==  "UISPEC" )
	{
		int ID_;
		control->showUISpecXML(ID_);
	}
	else if ( cmd_ ==  "LISTUI" )
	{
		control->listUISpec();
	}
	else
		return "\nError: XmlUI not found!\n";

}

// show help
string XmlUI :: help(void)
{
	string xml;

	xml  = "<xml info='HELP' comment='RPn XmlUI List'>";
/*
	xml += "\t" + "<cmd='HELP'"      + "	comment=' Show help'>";
	xml += "\t" + "<cmd='LIST'"      + "	comment=' List available physics'>";
	xml += "\t" + "<cmd='NEW'"       + "	comment=' Create a new physocs'>";
	xml += "\t" + "<cmd='CALC'"      + "	comment=' Calc that requires 1 coord'>";
	xml += "\t" + "<cmd='CALC2'"     + "	comment=' Calc that requires 2 coords'>";
	xml += "\t" + "<cmd='RES'"       + "	comment=' get the result from the last command'>";
	xml += "\t" + "<cmd='SETI'"      + "	comment=' Set int parameter'>";
	xml += "\t" + "<cmd='SETF'"      + "	comment=' Set float parameter'>";
	xml += "\t" + "<cmd='SETS'"      + "	comment=' Set string parameter'>";
	xml += "\t" + "<cmd='MACRO'"     + "	comment=' Create a macro'>";
	xml += "\t" + "<cmd='ADDM'"      + "	comment=' Add a command to a macro'>";
	xml += "\t" + "<cmd='ALLUISPEC'" + "	comment=' Show all user interface specification'>";
	xml += "\t" + "<cmd='UISPEC'"    + "	comment=' Show user interface specification'>";
	xml += "\t" + "<cmd='LISTUI'"    + "	comment=' List interface specification elements'>";
*/
	xml += "</xml>\n";

	return xml;
}


