#include <Settings.h>
#include <UISpec.h>


Settings :: Settings(int _t) : 
	type_(_t),
	visible_(true),
	changeable_(true)
{
	ID_ = auto_register(*this);
}


Settings * Settings :: object()
{
	return this;
}


int Settings :: ID()
{
	return ID_;
}


int Settings :: type()
{
	return type_;
}


void Settings :: type(int _t)
{
	type_ = _t;
}


string Settings :: typeName()
{
	return typeName_[type_];
}

bool Settings :: visible(void)
{
	return visible_;
}


void Settings :: visible(bool _v)
{
	visible_ = _v;
}


bool Settings :: changeable(void)
{
	return changeable_;
}


void Settings :: changeable(bool _C)
{
	changeable_ = _C;
}


