#include <BoolSettings.h>
#include <sstream>


BoolSettings :: BoolSettings() :
	Settings(CHECKBOX)
{
}


BoolProfile * BoolSettings :: profile()
{
	BoolProfile *profile = new BoolProfile(
		ID(), 			\
		type(), 		\
		visible(), 		\
		changeable(),		\
		name(), 		\
		value(), 		\
		default_value()		\
	);

	return profile;
}


string BoolSettings :: toXML(int _level)
{
	string _xml, _tab, _visible, _changeable, _value, _default;

	ostringstream buff0; buff0 << ID(); string id = buff0.str();

	if ( value() ) 
		_value = "TRUE";
	else
		_value = "FALSE";

	if ( default_value() )
		_default = "TRUE";
	else
		_default = "FALSE";

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
	_xml += _tab + "<BoolParameter name='" + name() + "' id = " + id + " type='" + typeName() + 
		"' visible='" + _visible + "' changeable='" + _changeable + "'>\n";
	_xml += _tab + "    <value=" + _value + ">\n";
	_xml += _tab + "    <default=" + _default + ">\n";
	_xml += _tab + "</BoolParameter>\n\n";

	return _xml;
}
