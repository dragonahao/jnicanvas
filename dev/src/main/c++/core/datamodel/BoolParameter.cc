#include <BoolParameter.h>

void BoolParameter::copy(const BoolParameter *original) {
    name_  = original->name_;
    parent_ = original->parent_;
    value_ = original->value_;
    default_value_ = original->default_value_;

    return;
}

BoolParameter::BoolParameter() : name_(string("")), 
                                 parent_(string("")),
                                 value_(true),
                                 default_value_(true) {
}

BoolParameter::BoolParameter(const string &n, bool v) : name_(n),
                                                        parent_(string("")),
                                                        value_(v),
                                                        default_value_(v) {
}

BoolParameter::BoolParameter(const string &n, const string &p, bool v) : name_(n),
                                                                         parent_(p),
                                                                         value_(v),
                                                                         default_value_(v) {
}

BoolParameter::BoolParameter(const BoolParameter &original){
    copy(&original);
}

BoolParameter::BoolParameter(const BoolParameter *original){
    copy(original);
}

BoolParameter::~BoolParameter(){
}

BoolParameter BoolParameter::operator=(const BoolParameter &original){
    if (this != &original) copy(&original);

    return *this;
}

