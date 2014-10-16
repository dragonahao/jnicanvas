#include "FloatParameter.h"

void FloatParameter::copy(const FloatParameter *original) {
    name_  = original->name_;
    parent_ = original->parent_;
    min_   = original->min_;
    max_   = original->max_;
    value_ = original->value_;
    default_value_ = original->default_value_;

    return;
}

FloatParameter::FloatParameter() : name_(string("")), 
                                   parent_(string("")), 
                                   min_(0.0),
                                   max_(0.0),
                                   value_(0.0),
                                   default_value_(0.0) {
}

FloatParameter::FloatParameter(const string &n, double v) : name_(n),
                                                            parent_(string("")),
                                                            min_(v),
                                                            max_(v),
                                                            value_(v),
                                                            default_value_(v) {
}

FloatParameter::FloatParameter(const string &n, double mn, double mx, double v) : name_(n),
                                                                                  parent_(string("")),
                                                                                  min_(mn),
                                                                                  max_(mx),
                                                                                  value_(v),
                                                                                  default_value_(v) {
}

FloatParameter::FloatParameter(const string &n, const string &p, double mn, double mx, double v) : name_(n),
                                                                                                   parent_(p),
                                                                                                   min_(mn),
                                                                                                   max_(mx),
                                                                                                   value_(v),
                                                                                                   default_value_(v) {
}

FloatParameter::FloatParameter(const FloatParameter &original){
    copy(&original);
}

FloatParameter::FloatParameter(const FloatParameter *original){
    copy(original);
}

FloatParameter::~FloatParameter(){
}

FloatParameter FloatParameter::operator=(const FloatParameter &original){
    if (this != &original) copy(&original);

    return *this;
}

