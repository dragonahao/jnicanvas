#ifndef _BoolParameter_
#define _BoolParameter_

#include <presentation>
#include <string>

using namespace std;

class BoolParameter : public BoolSettings
{
    private:
        // Users should not add any private members.
    protected:
        string name_, parent_;
        bool value_, default_value_;

        virtual void copy(const BoolParameter *original);
    public:
        BoolParameter();
        BoolParameter(const string &n, bool v);
        BoolParameter(const string &n, const string &p, bool v);
        BoolParameter(const BoolParameter &original);
        BoolParameter(const BoolParameter *original);

        virtual ~BoolParameter();

        virtual BoolParameter operator=(const BoolParameter &original);

        virtual string name() const {return name_;}
        virtual string parent() const {return parent_;}

        virtual bool value() const {return value_;}
        virtual void value(bool v) {value_ = v; return;}

        virtual bool default_value() const {return default_value_;}
        virtual void reset() {value_ = default_value_; return;}

};

#endif
