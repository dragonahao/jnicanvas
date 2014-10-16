#ifndef _SettingsType
#define _SettingsType

#include <string>

using namespace std;

/*
 *
 * SettingsType List defines which type of information the GUI layer will have to deal with.
 *
 * When updating this list, also update typeName[] array inside Settings class constructor i
 * following the same order these informations are presented here.
 *
*/
enum SettingsType { 
	PHYSICS,	// set()	- Configurable / PanelSettings
	SUBPHYSICS,	// set()	- Configurable / PanelSettings
	CALC_METHOD,	// calc()	- Configurable / PanelSettings - with action button
	AUX_METHOD,	// set()	- Configurable / PanelSettings
	TEXTBOX_INT,	// set()	- IntSettings
	TEXTBOX_FLOAT,	// set()	- FloatSettings
	TEXTBOX_STRING,	// set()	- TextSettings
	TEXTBOX_BOOL,	// set()	- BoolSettings
	SPINNER,	// set()	- IntSettings
	RADIOBUTTON,	// set()	- OptionSettings
	CHECKBOX,	// set()	- BoolSettings
	DROPDOWNLIST	// set()	- OptionSettings
};

const string typeName_[] = { 
	"PHYSICS",
	"SUBPHYSICS",
	"CALC_METHOD",
	"AUX_METHOD",
	"TEXTBOX_INT", \
	"TEXTBOX_FLOAT",
	"TEXTBOX_STRING",
	"TEXTBOX_BOOL",
	"SPINNER",
	"RADIOBUTTON",
	"CHECKBOX",
	"DROPDOWNLIST" };

#endif
