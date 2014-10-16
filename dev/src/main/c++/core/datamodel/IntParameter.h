#ifndef _INTPARAMETER_
#define _INTPARAMETER_

#include <presentation>
#include <string>

using namespace std;

class IntParameter : public IntSettings {
    private:
        // Users should not add any private members.
    protected:
        string name_, parent_;
        int min_, max_, value_, default_value_;

        virtual void copy(const IntParameter *original);
    public:
        IntParameter();
        IntParameter(const string &n, int v);
        IntParameter(const string &n, int mn, int mx, int v);
        IntParameter(const string &n, const string &p, int mn, int mx, int v);
        IntParameter(const IntParameter &original);
        IntParameter(const IntParameter *original);

        virtual ~IntParameter();

        virtual IntParameter operator=(const IntParameter &original);

        virtual string name() const {return name_;}
        virtual string parent() const {return parent_;}
        virtual void parent(string &p) {parent_ = p; return;}

        virtual int min() const {return min_;}
        virtual void min(int m) {min_ = m; return;}

        virtual int max() const {return max_;}
        virtual void max(int m) {max_ = m; return;}

        virtual int value() const {return value_;}
        virtual void value(int v) {value_ = v; return;}

        virtual int default_value() const {return default_value_;}
        virtual void reset() {value_ = default_value_; return;}
};

#endif // _INTPARAMETERS_

