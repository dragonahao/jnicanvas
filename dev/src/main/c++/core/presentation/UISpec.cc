#include <UISpec.h>
#include <presentation>
#include <typeinfo>
#include <sstream> 

/* UISpec public methods and control */

bool UISpec :: instanceFlag = false;

UISpec* UISpec :: uispec = NULL;


UISpec* UISpec :: instance()
{
	if(! instanceFlag)
	{
		uispec = new UISpec();
		instanceFlag = true;
		return uispec;
	}
	else
	{
		return uispec;
	}
}


int UISpec :: auto_register(Settings & _settings)
{
	settings_.push_back(& _settings);
	return settings_.size();
}


int UISpec :: auto_register(Settings * _settings)
{
	settings_.push_back(_settings);
	return settings_.size();
}


/* gui configration functions */

string UISpec :: traverse()
{
	string res = "";

	for (int i=0; i<settings_.size(); i++)
	{
		ostringstream buff0;
		buff0 << settings_[i]->ID();
		string id = buff0.str();
		res += id + " - " + settings_[i]->name() + " - " + settings_[i]->typeName() + "\n";
	}
	return res;
}


string UISpec :: toXML(int ID_)
{
	cout << endl;
	cout << "Show XML settings ID " << ID_ << endl;
	cout << "===================================" << endl;
	return settings_[ID_]->toXML();
}


ProfileSettings * UISpec :: profile(int _ID)
{
	ProfileSettings * profileSettings = settings_[_ID]->profile();
	
	return profileSettings;
}


ProfileSettings * UISpec :: profile(string _name)
{
	int _ID;

	for (int i=0; i<settings_.size(); i++)
	{
		if ( _name == settings_[i]->name() )
		{
			_ID = i;
			break;
		}
	}

	ProfileSettings * profileSettings = settings_[_ID]->profile();
	
	return profileSettings;
}


/* callback functions */
Settings * UISpec :: settings(int _ID)
{
	return settings_[_ID];
}


Settings * UISpec :: settings(string _name)
{
	for (int i=0; i<settings_.size(); i++)
	{
		if ( _name == settings_[i]->name() )
		{
			return settings_[i];
		}
	}
}


/*********************************************************
 *
 * Static function used to register Settings objects
 *
 */


int auto_register(Settings & _settings)
{
	UISpec *uispec;
	uispec = UISpec :: instance();
	return uispec->auto_register(_settings) -1;
}


int auto_register(Settings * _settings)
{
	UISpec *uispec;
	uispec = UISpec :: instance();
	return uispec->auto_register(_settings) -1;
}


