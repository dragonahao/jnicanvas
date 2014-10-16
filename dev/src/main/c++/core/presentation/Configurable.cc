#include <Configurable.h>
#include <sstream>


Configurable :: Configurable(int _t) : 
	Settings(_t)
{
}


void Configurable :: addToUI(Settings & _settings)
{
	settings_.push_back(&_settings);
}


void Configurable :: addToUI(vector <Settings *> _settings)
{
	for (int i=0; i<settings_.size()-1; i++)
		settings_.push_back(_settings[i]);
}


void Configurable :: addToUI(Settings & _settings, bool _v, bool _c)
{
	_settings.visible(_v);
	_settings.changeable(_c);

	settings_.push_back(&_settings);
}


string Configurable :: toXML(int _level)
{
	string _tab, _xml;

	ostringstream buff0; buff0 << ID(); string id = buff0.str();

	for (int l = 0; l < _level; l++) _tab += "    ";

	_level++;

	_xml  = "\n";
	_xml += _tab + "<Method name='" + name() + "' id=" + id + " type='" + typeName() + "'>\n";
	for (int i = 0; i < settings_.size(); i++)
	{
		_xml += settings_[i]->toXML(_level);
	}
 	_xml += _tab + "</Method>\n\n";

	return _xml;
}


ProfileSettings * Configurable :: profile(void)
{
	Profile * _profile = new Profile(ID(), type(), name(), visible(), changeable());

/* Profile does not return recursuv profile because numeric programer does not adds child settings
	for (int i = 0; i < settings_.size(); i++)
	{
		ProfileSettings * _profileSettings = settings_[i]->profile();
		_profile->addToProfile(*_profileSettings);
	}
*/

	return _profile;
}
