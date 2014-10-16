#include <IntSettings.h>
#include <sstream>


IntSettings :: IntSettings() :
	Settings(TEXTBOX_INT)
{
}


IntProfile * IntSettings :: profile()
{
	IntProfile *profile = new IntProfile(
		ID(), 			\
		type(), 		\
		visible(), 		\
		changeable(),		\
		name(), 		\
		value(), 		\
		default_value(), 	\
		min(), 			\
		max() 			\
	);

	return profile;
}


string IntSettings :: toXML(int _level)
{
	string _xml, _tab, _visible, _changeable;

	ostringstream buff0; buff0 << ID(); string id = buff0.str();
	ostringstream buff2; buff2 << value(); string _value = buff2.str();
	ostringstream buff3; buff3 << default_value(); string _default = buff3.str();
	ostringstream buff4; buff4 << min(); string _min = buff4.str();
	ostringstream buff5; buff5 << max(); string _max = buff5.str();

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
	_xml += _tab + "<IntParameter name='" + name() + "' id=" + id + " type='" + typeName() + \
			"' visible='" + _visible + "' changeable='" + _changeable + "'>\n";
	_xml += _tab + "    <value=" + _value + ">\n";
	_xml += _tab + "    <default=" + _default + ">\n";
	_xml += _tab + "    <min=" + _min + ">\n";
	_xml += _tab + "    <max=" + _max + ">\n";
	_xml += _tab + "</IntParameter>\n\n";

	return _xml;
}
