#ifndef _PARAMETER_
#define _PARAMETER_

#include <presentation>
#include <string>

using namespace std;

// TODO: Decide if minimum and maximum are the correct solution, since there
//       are magnitudes, such as temperature, that do not have an axiomatic
//       range (like, say, saturation), but an arbitrary one. Perhaps
//       in these cases something like 
//
//           double inf = numeric_limits<double>::infinity();
//
//       (which is true infinity and can be positive and negative) should be used.
//
//       Morante.

// Class FloatParameter. Every Auxiliary function or FluxFunction or the like has
// a number of parameters, which have a name, and minimum, maximum and initial 
// (or default) values. Being thus standardized, the interface can query said
// Functions about their parameters and automatically create an appropriate
// user interface to show and modify the parameters interactively.
//
//     Virtual destructor (because classes may be derived from this one).
//
// All methods within this class should be virtual, so the derived classes can
// modify them as need be.
//
class FloatParameter : public FloatSettings {
    private:
        // Users should not add any private members.
    protected:
        string name_, parent_;
        double min_, max_, value_, default_value_;

        virtual void copy(const FloatParameter *original);
    public:
        FloatParameter();
        FloatParameter(const string &n, double v);
        FloatParameter(const string &n, double mn, double mx, double v);
        FloatParameter(const string &n, const string &p, double mn, double mx, double v);
        FloatParameter(const FloatParameter &original);
        FloatParameter(const FloatParameter *original);

        virtual ~FloatParameter();

        virtual FloatParameter operator=(const FloatParameter &original);

        virtual string name() const {return name_;}
        virtual string parent() const {return parent_;}
        virtual void parent(string &p) {parent_ = p; return;}

        virtual double min() const {return min_;}
        virtual void min(double m) {min_ = m; return;}

        virtual double max() const {return max_;}
        virtual void max(double m) {max_ = m; return;}

        virtual double value() const {return value_;}
        virtual void value(double v) {value_ = v; return;}

        virtual double default_value() const {return default_value_;}
        virtual void reset() {value_ = default_value_; return;}
};

#endif // _PARAMETERS_

