#include <StringSettings.h>
#include <sstream>


StringSettings :: StringSettings() :
	Settings(TEXTBOX_STRING)
{
}


StringProfile * StringSettings :: profile()
{
	StringProfile *stringProf = new StringProfile(
		ID(), 			\
		type(), 		\
		visible(), 		\
		changeable(),		\
		name(), 		\
		value(), 		\
		default_value() 	\
	);

	return stringProf;
}


string StringSettings :: toXML(int _level)
{
	string _xml, _tab, _visible, _changeable;

	ostringstream buff0; buff0 << ID(); string id = buff0.str();

	string value_ = value();
	string default_ = default_value();

	if ( visible() ) 
		_visible = "TRUE";
	else
		_visible = "FALSE";

	if ( changeable() ) 
		_changeable = "TRUE";
	else
		_changeable = "FALSE";


	for (int l = 0; l < _level; l++) _tab += "    ";

	_xml =  "\n";
	_xml += _tab + "<StringParameter name='" + name() + "' id = " + id + " type='" + typeName() + \
			"' visible='" + _visible + "' changeable='" + _changeable + "'>\n";
	_xml += _tab + "    <value=" + value_ + ">\n";
	_xml += _tab + "    <default=" + default_ + ">\n";
	_xml += _tab + "</StringParameter>\n\n";

	return _xml;
}
