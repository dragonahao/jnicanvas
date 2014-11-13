#ifndef _FLUXSINGLEPHASEVAPORADIMENSIONALIZED_
#define _FLUXSINGLEPHASEVAPORADIMENSIONALIZED_

#include <stdio.h>
#include <stdlib.h>
#include "FluxFunction.h"

#include "FluxSinglePhaseVaporAdimensionalized_Params.h"
#include "Thermodynamics.h"

class FluxSinglePhaseVaporAdimensionalized : public FluxFunction {
    private:
        // Thermodynamics
        Thermodynamics *thermo;
    protected:
    public:
        FluxSinglePhaseVaporAdimensionalized(const FluxSinglePhaseVaporAdimensionalized &);
        FluxSinglePhaseVaporAdimensionalized(const FluxSinglePhaseVaporAdimensionalized_Params &, Thermodynamics *t);
        FluxSinglePhaseVaporAdimensionalized * clone() const;

        ~FluxSinglePhaseVaporAdimensionalized();

        int jet(const WaveState &u, JetMatrix &m, int degree) const;
};

#endif // _FLUXSINGLEPHASEVAPORADIMENSIONALIZED_
