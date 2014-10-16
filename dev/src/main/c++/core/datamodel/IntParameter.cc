#include "IntParameter.h"

void IntParameter::copy(const IntParameter *original) {
    name_  = original->name_;
    parent_ = original->parent_;
    min_   = original->min_;
    max_   = original->max_;
    value_ = original->value_;
    default_value_ = original->default_value_;

    return;
}

IntParameter::IntParameter() : name_(string("")), 
                               parent_(string("")), 
                               min_(0),
                               max_(0),
                               value_(0),
                               default_value_(0) {
}

IntParameter::IntParameter(const string &n, int v) : name_(n),
                                                     parent_(string("")),
                                                     min_(v),
                                                     max_(v),
                                                     value_(v),
                                                     default_value_(v) {
}

IntParameter::IntParameter(const string &n, int mn, int mx, int v) : name_(n),
                                                                     parent_(string("")),
                                                                     min_(mn),
                                                                     max_(mx),
                                                                     value_(v),
                                                                     default_value_(v) {
}

IntParameter::IntParameter(const string &n, const string &p, int mn, int mx, int v) : name_(n),
                                                                                      parent_(p),
                                                                                      min_(mn),
                                                                                      max_(mx),
                                                                                      value_(v),
                                                                                      default_value_(v) {
}

IntParameter::IntParameter(const IntParameter &original){
    copy(&original);
}

IntParameter::IntParameter(const IntParameter *original){
    copy(original);
}

IntParameter::~IntParameter(){
}

IntParameter IntParameter::operator=(const IntParameter &original){
    if (this != &original) copy(&original);

    return *this;
}

