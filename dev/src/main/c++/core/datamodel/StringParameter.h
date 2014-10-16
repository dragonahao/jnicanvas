#ifndef _STRINGPARAMETER_
#define _STRINGPARAMETER_

#include <presentation>
#include <string>

using namespace std;

class StringParameter : public StringSettings {
    private:
        // Users should not add any private members.
    protected:
        string name_, parent_;
        string value_, default_value_;

        virtual void copy(const StringParameter *original);
    public:
        StringParameter();
        StringParameter(const string &n, string v);
        StringParameter(const string &n, const string &p, string v);
        StringParameter(const StringParameter &original);
        StringParameter(const StringParameter *original);

        virtual ~StringParameter();

        virtual StringParameter operator=(const StringParameter &original);

        virtual string name() const {return name_;}
        virtual string parent() const {return parent_;}
	virtual void parent(string &p) {parent_ = p; return;}

        virtual string value() const {return value_;}
        virtual void value(string v) {value_ = v; return;}

	virtual string default_value() const {return default_value_;}
        virtual void reset() {value_ = default_value_; return;}
};

#endif
