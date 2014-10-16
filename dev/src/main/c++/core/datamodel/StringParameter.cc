#include <StringParameter.h>

void StringParameter::copy(const StringParameter *original) {
    name_  = original->name_;
    parent_ = original->parent_;
    value_ = original->value_;
    default_value_ = original->default_value_;

    return;
}

StringParameter::StringParameter() : name_(string("")), 
                                     parent_(string("")),
                                     value_(string("")),
                                     default_value_(string("")) {
}

StringParameter::StringParameter(const string &n, string v) : name_(n),
                                                              parent_(string("")),
                                                              value_(v),
                                                              default_value_(v) {
}

StringParameter::StringParameter(const string &n, const string &p, string v) : name_(n),
                                                                               parent_(p),
                                                                               value_(v),
                                                                               default_value_(v) {
}

StringParameter::StringParameter(const StringParameter &original){
    copy(&original);
}

StringParameter::StringParameter(const StringParameter *original){
    copy(original);
}

StringParameter::~StringParameter(){
}

StringParameter StringParameter::operator=(const StringParameter &original){
    if (this != &original) copy(&original);

    return *this;
}

