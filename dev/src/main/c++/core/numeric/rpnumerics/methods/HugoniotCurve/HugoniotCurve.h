#ifndef _HUGONIOTCURVE_
#define _HUGONIOTCURVE_

#include <vector>
#include "ColorCurve.h"
#include "Curve.h"
#include "ReferencePoint.h"

// Forward declaration.
//
class SubPhysics;

#define UNDEFINED_HUGONIOT (-1)
#define EXPLICIT_HUGONIOT    0
#define IMPLICIT_HUGONIOT    1

// Abstract Base Class for both implicit and explicit Hugoniot curves.
//
class HugoniotCurve {
    private:
    protected:
        ReferencePoint reference_point;

        const FluxFunction         *f;
        const AccumulationFunction *a;
        const Boundary             *boundary;

        int method_;
        std::string info_;

        SubPhysics *subphysics;
    public:
        HugoniotCurve(const FluxFunction *ff, const AccumulationFunction *aa, const Boundary *bb) : f(ff), a(aa), boundary(bb), subphysics(0) {
            info_ = std::string("Abstract HugoniotCurve");

            method_ = UNDEFINED_HUGONIOT; // If this method shows up then the programmer forgot to set this.
        }

        HugoniotCurve(const FluxFunction *ff, const AccumulationFunction *aa, const Boundary *bb, SubPhysics *s) : f(ff), a(aa), boundary(bb), subphysics(s){
        }

//        HugoniotCurve(const Boundary *bb) : boundary(bb){
//        }

        virtual ~HugoniotCurve(){
        }

        // Parameters:
        //
        //      ref: The reference point for this particular curve.
        //
        //     type: Identifies special cases of ref.point (generic, on a specific side of the domain, 
        //           on a secondary bifurcation, etc.).
        //
        //        c: Output.
        // 
        virtual void curve(const ReferencePoint &ref, int type, std::vector<Curve> &c) = 0;

        virtual void curve(const ReferencePoint &ref, int type, std::vector<HugoniotPolyLine> &classified_curve){
            std::vector<Curve> cc;

            curve(ref, type, cc);

            ColorCurve colorcurve(*f, *a);

            for (int i = 0; i < cc.size(); i++){
                if (cc[i].curve.size() > 0){

                    std::vector<RealVector> segmented_curve;
                    for (int j = 0; j < cc[i].curve.size() - 1; j++){
                        segmented_curve.push_back(cc[i].curve[j]);
                        segmented_curve.push_back(cc[i].curve[j + 1]);
                    }

                    std::vector<HugoniotPolyLine> temp_classified_curve;
                    std::vector<RealVector> transition_list;

                    colorcurve.classify_segmented_curve(segmented_curve, ref, temp_classified_curve, transition_list);

                    for (int j = 0; j < temp_classified_curve.size(); j++) classified_curve.push_back(temp_classified_curve[j]);
                }
            }

            return;
        }

        // Derived classes will fill these two vectors, name being the descriptor of type.
        //
        virtual void list_of_reference_points(std::vector<int> &type, std::vector<std::string> &name) const = 0;

        int implemented_method() const {return method_;}

        std::string Hugoniot_info() const {return info_;}

        virtual void equilibria(const std::vector<Curve> &curve, const ReferencePoint& ref, const RealVector &p, std::vector<RealVector> &ep){return;}
};

#endif // _HUGONIOTCURVE_

