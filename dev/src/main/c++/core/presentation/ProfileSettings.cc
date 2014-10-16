#include <ProfileSettings.h>


ProfileSettings :: ProfileSettings()
{
}

int ProfileSettings :: ID()
{
	return ID_;
}


int ProfileSettings :: type()
{
	return type_;
}


string ProfileSettings :: typeName()
{
	return typeName_[type_];
}

bool ProfileSettings :: visible(void)
{
	return visible_;
}


bool ProfileSettings :: changeable(void)
{
	return changeable_;
}


