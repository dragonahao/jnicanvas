/*
 * IMPA - Fluid Dynamics Laboratory
 *
 * RPn Project
 *
 * @(#) ShockContinuationMethod3D2D.cc
 */

/*
 * ---------------------------------------------------------------
 * Includes:
 */
#include "ShockContinuationMethod3D2D.h"

/*
 * ---------------------------------------------------------------
 * Definitions:
 */

int ShockContinuationMethod3D2D::debugshock = 0;



ShockContinuationMethod3D2D::ShockContinuationMethod3D2D() : ShockMethod(){
//    Uref = 0;
}

ShockContinuationMethod3D2D::ShockContinuationMethod3D2D(int d, FluxFunction *f, AccumulationFunction *a, Boundary *b) : ShockMethod(d, f, a, b){
//    Uref = 0;
}

ShockContinuationMethod3D2D::~ShockContinuationMethod3D2D() {
//    if (Uref != 0) delete [] Uref;
}

void ShockContinuationMethod3D2D::print_matrix(const char *name, int m, int n, double *A) {
    printf("%s = \n", name);
    for (int i = 0; i < m; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%e ", A[i * n + j]);
        }
        printf("]\n");
    }
    return;
}

// Vectorial product in 3D:
//
//     c = a x b,
//
// where a, b and c are arrays of size = 3, which the user
// must create.
//

void ShockContinuationMethod3D2D::vectprod(double *a, double *b, double *c) {
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];

    return;
}

double ShockContinuationMethod3D2D::dotprod(int n, double x[], double y[]) {
    double p = 0.0;
    for (int i = 0; i < n; i++) p += x[i] * y[i];
    return p;
}

void ShockContinuationMethod3D2D::normalize(int n, double x[]) {
    double norm = 0.0;
    norm = euclidean_norm(n, &x[0]);
    for (int i = 0; i < n; i++) x[i] /= norm;
    return;
}

double ShockContinuationMethod3D2D::euclidean_norm(int n, double x[]) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) norm += x[i] * x[i];

    return sqrt(norm);
}

void ShockContinuationMethod3D2D::curveCalc(const RealVector &ref, bool local_shock, const RealVector &in, int increase, int family, int type_of_shock, const RealVector *orig_direction, int number_ignore_doub_contact, FluxFunction *ff, AccumulationFunction *aa, Boundary *boundary,
                         std::vector<RealVector> &shockcurve, int &info_shockcurve, std::vector<RealVector> &shockcurve_alt, int &info_shockcurve_alt,double newtonTolerance){
    // ReferencePoint data
    ReferencePoint temp(ref, ff, aa, 0);

    curveCalc(SHOCK_CURVE_IS_INITIAL, temp, local_shock, in, increase, family, type_of_shock, orig_direction, number_ignore_doub_contact, ff, aa, boundary, shockcurve, info_shockcurve, shockcurve_alt, info_shockcurve_alt,  newtonTolerance);

    return;
 }

 int ShockContinuationMethod3D2D::curveCalc(int is_initial, const ReferencePoint &ref, bool local_shock, const RealVector &in, int increase, int family, int type_of_shock, const RealVector *orig_direction, int number_ignore_doub_contact, FluxFunction *ff, AccumulationFunction *aa, Boundary *boundary,
                         std::vector<RealVector> &shockcurve, int &info_shockcurve, std::vector<RealVector> &shockcurve_alt, int &info_shockcurve_alt,double newtonTolerance){

    shock_is_initial = is_initial;

    fluxFunction_=ff;
    accFunction_=aa;
    boundary_=boundary;
    dimension_=in.size();
    family_=family;
    eps=newtonTolerance;
    type = _SHOCK_GENERAL_ACCUMULATION_;
    tolerance=1e-15;
    delta = 1e-10; // Was: 1e-10
//    Uref = new double[ref.point.size()];
//     
//     for (int i = 0; i < ref.point.size(); i++) {
//         Uref[i]=ref.point.component(i);

//    }

    // Initial Point
    initial_point = in;
     
    // ReferencePoint data
    ref_point = ref.point;

    Fref = ref.F; 
    Gref = ref.G;
    
    // Curve proper 

    return curve(increase, shockcurve);
}
    
    

int ShockContinuationMethod3D2D::curve(int direction, vector<RealVector> & output) {
    int maxStepsNumber = 100000;
//    int maxStepsNumber = 1000;
    
    int edge=0;

//    vector<RealVector> output;

    int info = curve(family_, maxStepsNumber, direction, output, edge);

//    for (int i = 0; i < output.size(); i++) {
//        cout<<"Saida do curve: "<<output.at(i)<<endl;

//    }

    return edge;
}

//ShockContinuationMethod3D2D::ShockContinuationMethod3D2D(const ShockContinuationMethod3D2D & copy) {
//
//}

//ShockMethod * ShockContinuationMethod3D2D::clone() const {
//    return new ShockContinuationMethod3D2D(*this);
//
//}


// FUNCTION shockspeed
//
// This function computes the shock speed, given two points,
// Up and Um, as in Eq. (3.2).
//
// Parameters:
//              n: Dimension of the space.
//         family: The family.
//    typeofspeed: 0 if Um == Up,
//                 1 otherwise.
//           type: _SHOCK_SIMPLE_ACCUMULATION_ or _SHOCK_GENERAL_ACCUMULATION_.
//             Up: "Plus" point.
//             Um: "Minus" point.
//
// Returns:
//     The speed as a double.
//

double ShockContinuationMethod3D2D::shockspeed(int n, int family, double Um[], double Up[]) {
    // Compute F(Up), F(Um):
    double Fp[n], Fm[n];

    const FluxFunction & shock_flux_object = fluxFunction();
    const AccumulationFunction & shock_accumulation_object = accumulationFunction();
    shock_flux_object.fill_with_jet(n, Up, 0, Fp, 0, 0);
    shock_flux_object.fill_with_jet(n, Um, 0, Fm, 0, 0);

    /*
            printf("\nUp = (");
            for (int i = 0; i < n; i++){
                printf("%f", Up[i]);
                if (i < n - 1) printf(", ");
            }
            printf(")\n");

            printf("Fp = (");
            for (int i = 0; i < n; i++){
                printf("%g", Fp[i]);
                if (i < n - 1) printf(", ");
            }
            printf(")\n");
     */
    double Gp[n], Gm[n];
    if (type == _SHOCK_SIMPLE_ACCUMULATION_) {
        for (int i = 0; i < n; i++) {
            Gp[i] = Up[i];
            Gm[i] = Um[i];
        }
    } else {
        shock_accumulation_object.fill_with_jet(n, Up, 0, Gp, 0, 0);
        shock_accumulation_object.fill_with_jet(n, Um, 0, Gm, 0, 0);
    }

    // The speed
    double s = 0, den = 0;
    int i;

    for (i = 0; i < n; i++) {
        s += (Fp[i] - Fm[i])*(Gp[i] - Gm[i]);
        den += (Gp[i] - Gm[i])*(Gp[i] - Gm[i]);
    }
    // Colocar aqui um error se den = 0
    //        printf("s = %g, den = %g\n", s, den);
    return s / den;
}

/* EVENTUALLY THIS IS GOING AWAY!
int Shockcurve_Adaptive_Hypersurface_Newton::shock_init(double Uref[], int family, int increase, double Unext[], double epsilon){
    // Compute the eigenpair at Uref:
    // Find the Jacobian of the field at U-:
    double A[n][n], B[n][n];

    fill_with_jet(shock_flux_object,         n, Uref, 1, 0, &A[0][0], 0);
    fill_with_jet(shock_accumulation_object, n, Uref, 1, 0, &B[0][0], 0);

    // Find the eigenpairs of J:
    vector<eigenpair> e;
    Eigen::eig(n, &A[0][0], &B[0][0], e);

    // The i-th eigenvalue must be real. // The eigenvalues must be chosen carefully in the n-dimensional case
    if (e[family].i != 0){
        #ifdef TEST_SHOCK
            printf("Inside shockinit(): Init step, eigenvalue %d is complex: % f %+f.\n", family, e[family].r, e[family].i);
        #endif
        return ABORTED_PROCEDURE;
    }

    // Extract the indx-th right-eigenvector of J:
    int i;
    double r[n];
    for (i = 0; i < n; i++) r[i] = e[family].vrr[i];
    //for (i = 0; i < n; i++) printf("r(%d) = % f\n", i, r[i]);

    // Set epsilon, see Eq. (2.3).
    // double epsilon = 1e-1;

    // Find U+right and U+left.
    double Upr[n], Upl[n];
    for (i = 0; i < n; i++){
        Upr[i] = Uref[i] + epsilon*r[i];
        Upl[i] = Uref[i] - epsilon*r[i];
    }

    // Compute the speed at Upr, Upl and Uref
    double spr, spl, sm;
    spr = shockspeed(n, family, 1, Uref, Upr);
    spl = shockspeed(n, family, 1, Uref, Upl);
    sm  = shockspeed(n, family, 0, Uref,  Uref); // shock speed deve apenas contemplar o caso de 2 ptos diferentes.

    // Choose the point according to the increase/decrease of the speed:  // ESTA COMPARACAO DEVE SER FEITA DEPOIS DA CORRECAO PELO METODO DE NEWTON !!!! IMPORTANTE!!!

    printf("\n\n\n");
    printf("Family: %d, increase = %d\n", family, increase);
    printf("spr = %f, sm = %f, spl = %f\n", spr, sm, spl);
    for (i = 0; i < n; i++) printf("Upr[%d] = %f     Upl[%d] = %f\n", i, Upr[i], i, Upl[i]);

    // Speed should increase
    if (increase == 1){
        if (spl > sm && sm > spr)      {for (i = 0; i < n; i++) Unext[i] = Upl[i]; printf("shock init: 1\n");}
        else if (spl < sm && sm < spr) {for (i = 0; i < n; i++) Unext[i] = Upr[i]; printf("shock init: 2\n");}
        else if ((spl < sm && sm > spr) || (spl > sm && sm < spr)) { printf("3\n"); return ABORTED_PROCEDURE;}
    }
    // Speed should decrease
    else if (increase == -1){
        if (spl < sm && sm < spr)      {for (i = 0; i < n; i++) Unext[i] = Upl[i]; printf("shock init: 4\n");}
        else if (spl > sm && sm > spr) {for (i = 0; i < n; i++) Unext[i] = Upr[i]; printf("shock init: 5\n");}
        else if ((spl < sm && sm > spr) || (spl > sm && sm < spr)) { printf("6\n"); return ABORTED_PROCEDURE;}
    }
    else return ABORTED_PROCEDURE;

    return SUCCESSFUL_PROCEDURE;curve
}
 */


//void ShockContinuationMethod3D2D::fill_with_jet(const RpFunction & flux_object, int n, double *in, int degree, double *F, double *J, double *H) {
//    RealVector r(n);

////   printf("Valor de fluxobject %p\n",&flux_object);



////    cout << "Tamanho em fill: " << n << endl;
//    double *rp = r;
//    for (int i = 0; i < n; i++) rp[i] = in[i];
////    cout << "Entrada em fill: " << r << endl;
//    // Will this work? There is a const somewhere in fluxParams.
//    //FluxParams fp(r);
//    //flux_object->fluxParams(FluxParams(r)); // flux_object->fluxParams(fp);

//    WaveState state_c(r);

//    JetMatrix c_jet(n);
////    cout << "Depois da linha 296 " << c_jet.size() << endl;
//    flux_object.jet(state_c, c_jet, degree);
////    cout << "Depois de flux object: " << n << endl;

//    // Fill F
//    if (F != 0) for (int i = 0; i < n; i++) F[i] = c_jet(i);

//    // Fill J
//    if (J != 0) {
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                J[i * n + j] = c_jet(i, j);
//            }
//        }
//    }

//    // Fill H
//    if (H != 0) {
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                for (int k = 0; k < n; k++) {
//                    H[(i * n + j) * n + k] = c_jet(i, j, k); // Check this!!!!!!!!
//                }
//            }
//        }
//    }
////    cout << "Dentro de fill with jet shock" << endl;
//    return;
//}

// Creamos um metodo que transforma as coordenadas no espaco (a1,a2) em um ponto em 3D contido no plano dado por plane_point, v1 e v2

void ShockContinuationMethod3D2D::plane_mapping(double plane_point[], double a1, double a2, double v1[], double v2[], double p[]) {
    for (int i = 0; i < dimension(); i++) p[i] = plane_point[i] + a1 * v1[i] + a2 * v2[i];
    return;
}

// COMENTAR

int ShockContinuationMethod3D2D::plane_start(int family, double Upr[], double Upl[], double v1[], double v2[], double epsilon) { // TO DO: CONVENCAO SAIDAS E ENTRADAS !!!!!!!!!
    //  EXPLICAR TUDO POR FAVOR PETICAO DO DAN
    int n = dimension();
    const FluxFunction & shock_flux_object = fluxFunction();
    const AccumulationFunction & shock_accumulation_object = accumulationFunction();
    double A[n][n], B[n][n];

//    cout << "Em  plane start"<< endl;    printf("*****************************\n");
//    fill_with_jet(shock_flux_object, n, Uref, 1, 0, &A[0][0], 0);
    shock_flux_object.fill_with_jet(n, initial_point.components(), 1, 0, &A[0][0], 0);

//    cout << "Depois  plane start" << endl;
//    fill_with_jet(shock_accumulation_object, n, Uref, 1, 0, &B[0][0], 0); // TODO: Add "type", etc.
    shock_accumulation_object.fill_with_jet(n, initial_point.components(), 1, 0, &B[0][0], 0); // TODO: Add "type", etc.

//    cout << "Depois  accum start" << endl;
    // Find the eigenpairs:
    // TODO: Check LAPACK's docs for the case when the number of eigenpairs is insufficient (less than the dimension of space).
    vector<eigenpair> e;
    int info;
//    cout <<"Valor de type:"<<type<<endl;
    
//    cout<<"A: "<<endl;
//    for (int i = 0; i < n ; i++) {
//        for (int j = 0; j < n; j++) {
//            cout<<A[i][j]<<" ";
//        }
//                cout<<endl;
//    }


//        cout<<"B: "<<endl;
//    for (int i = 0; i < n ; i++) {
//        for (int j = 0; j < n; j++) {
//            cout<<B[i][j]<<" ";
//        }
//        cout<<endl;
//    }

// for (int i = 0; i < n ; i++) {
//     cout <<"Uref "<<Uref[i]<<endl;
// }


    if (type == _SHOCK_SIMPLE_ACCUMULATION_) info = Eigen::eig(n, &A[0][0], e);
    else info = Eigen::eig(n, &A[0][0], &B[0][0], e);
//    cout <<"Tamanho de e"<<e.size()<<endl;

    // The i-th eigenvalue must be real. // The eigenvalues must be chosen carefully in the n-dimensional case.
    // ALL eigenvalues must be real. Extend this by using a for cycle.
    if (e[family].i != 0) {
        printf("Inside shockinit(): Init step, eigenvalue %d is complex: % f %+f.\n", family, e[family].r, e[family].i);
        return ABORTED_PROCEDURE;
    }

    // Extract the indx-th right-eigenvector of J:
    int i;
    double r[n];
    for (i = 0; i < n; i++) r[i] = e[family].vrr[i];
    //for (i = 0; i < n; i++) printf("r(%d) = % f\n", i, r[i]);

    // Matrix whose rows are the valid eigenvectors (one less than the dimension of space).
    double M[n - 1][n];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = e[i].vrr[j];
        }
    }

    // TODO: Generalize using Gram-Schmidt
    if (n == 3) {
        int opp_family;
        if (family == 0) opp_family = 1;
        else if (family == 1) opp_family = 0;

        double vec[n];
        vectprod(&M[family][0], &M[opp_family][0], vec);

        //std::cout << "Vector product: (" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << std::endl;


        for (int j = 0; j < n; j++) M[family][j] = vec[j];
        normalize(3, &M[family][0]);
    } else return ABORTED_PROCEDURE;

    for (int j = 0; j < n; j++) {
        v1[j] = M[0][j];
        v2[j] = M[1][j];
    }

    //    for (int i=0; i < n; i++) printf("v1(%d)=%e\n", i, v1[i]);
    //    for (int i=0; i < n; i++) printf("v2(%d)=%e\n", i, v2[i]);

    // Find U+right and U+left.
    for (i = 0; i < n; i++) {
//        Upr[i] = Uref[i] + epsilon * r[i];
//        Upl[i] = Uref[i] - epsilon * r[i];

        Upr[i] = initial_point.component(i) + epsilon * r[i];
        Upl[i] = initial_point.component(i) - epsilon * r[i];
    }

    printf("ShockContinuationMethod3D2D. plane start. r = (%f, %f, %f)\n", r[0], r[1], r[2]);

    return SUCCESSFUL_PROCEDURE;
}

// TODO: mudar os nomes apropiadamente. plane(Uprevious, direction, vec_previous1, vec_previous2, plane_point, v1, v2, epsilon);

int ShockContinuationMethod3D2D::plane(double Uprevious[], double direction[], double vec_previous1[], double vec_previous2[], double plane_point[], double v1[], double v2[], double epsilon) {
    int n = dimension();
    for (int i = 0; i < n; i++) plane_point[i] = Uprevious[i] + epsilon * direction[i];

    vectprod(direction, vec_previous1, v1);
    double norm = 0;
    for (int i = 0; i < n; i++) norm += v1[i] * v1[i];
    norm = sqrt(norm);

    if (norm <= 1e-6) { // Verifying that we are are not calculating non-sense
        // TODO: Use a tolerance, not a fixed value
        vectprod(direction, vec_previous2, v1); // TODO: verificar a importancia da orientacao.
    }

    vectprod(direction, v1, v2);

    normalize(3, v1);
    normalize(3, v2);

    return SUCCESSFUL_PROCEDURE;
}


// TODO: LEVAR OS JATOS PARA FORA, E MISTURAR AMBOS JATOS
// Alternative for nabla_H1 calculated with equations 1 and 3

void ShockContinuationMethod3D2D::jet_H1(double *p, double &H1, double *nabla_H1) {
        const FluxFunction & shock_flux_object = fluxFunction();
    if (type == _SHOCK_SIMPLE_ACCUMULATION_) {


//        double F0[3];
//        fill_with_jet(shock_flux_object, 3, Uref, 0, &F0[0], 0, 0);

        double F[3];
        double A[3][3];

        shock_flux_object.fill_with_jet(3, p, 1, &F[0], &A[0][0], 0);

//        H1 = (F[0] - F0[0])*(p[2] - Uref[2]) - (F[2] - F0[2])*(p[0] - Uref[0]);
        H1 = (F[0] - Fref.component(0))*(p[2] - ref_point.component(2)) - (F[2] - Fref.component(2))*(p[0] - ref_point.component(0));

//        nabla_H1[0] = A[0][0]*(p[1] - Uref[1]) - (A[1][0]*(p[0] - Uref[0]) + (F[1] - F0[1])); // estas ecuaciones deben ser cambiadas para coincidir con el estandar establecido.
//        nabla_H1[1] = A[0][1]*(p[1] - Uref[1]) + (F[0] - F0[0]) - A[1][1]*(p[0] - Uref[0]);
//        nabla_H1[2] = A[0][2]*(p[1] - Uref[1]) - A[1][2]*(p[0] - Uref[0]);
        nabla_H1[0] = A[0][0]*(p[1] - ref_point.component(1)) - (A[1][0]*(p[0] - ref_point.component(0)) + (F[1] - Fref.component(1)));
        nabla_H1[1] = A[0][1]*(p[1] - ref_point.component(1)) + (F[0] - Fref.component(0)) - A[1][1]*(p[0] - ref_point.component(0));
        nabla_H1[2] = A[0][2]*(p[1] - ref_point.component(1)) - A[1][2]*(p[0] - ref_point.component(0));

    } else {
        const AccumulationFunction & shock_accumulation_object = accumulationFunction();
//        double F0[3];
//        double G0[3];

        double F[3];
        double G[3];
        double A[3][3];
        double B[3][3];

        double diff_F0, diff_F1, diff_F2;
        double diff_G0, diff_G1, diff_G2;

//        fill_with_jet(shock_flux_object, 3, Uref, 0, &F0[0], 0, 0);
//        fill_with_jet(shock_accumulation_object, 3, Uref, 0, &G0[0], 0, 0);

        shock_flux_object.fill_with_jet(3, p, 1, &F[0], &A[0][0], 0);
        shock_accumulation_object.fill_with_jet(3, p, 1, &G[0], &B[0][0], 0);

//        diff_F0 = F[0] - F0[0]; // [F1]
//        diff_F1 = F[1] - F0[1]; // [F2]
//        diff_F2 = F[2] - F0[2]; // [F3]

//        diff_G0 = G[0] - G0[0]; // [G1]
//        diff_G1 = G[1] - G0[1]; // [G2]
//        diff_G2 = G[2] - G0[2]; // [G3]
        diff_F0 = F[0] - Fref.component(0); // [F1]
        diff_F1 = F[1] - Fref.component(1); // [F2]
        diff_F2 = F[2] - Fref.component(2); // [F3]

        diff_G0 = G[0] - Gref.component(0); // [G1]
        diff_G1 = G[1] - Gref.component(1); // [G2]
        diff_G2 = G[2] - Gref.component(2); // [G3]

        H1 = diff_F0 * diff_G2 - diff_F2*diff_G0;

        nabla_H1[0] = A[0][0] * diff_G2 + diff_F0 * B[2][0] - A[2][0] * diff_G0 - diff_F2 * B[0][0]; // dF1_dW1 * [G3] + [F1]*dG3_dW1 - dF3_dW1*[G1] - [F3]*dG1_dW1
        nabla_H1[1] = A[0][1] * diff_G2 + diff_F0 * B[2][1] - A[2][1] * diff_G0 - diff_F2 * B[0][1]; // dF1_dW2 * [G3] + [F1]*dG3_dW2 - dF3_dW2*[G1] - [F3]*dG1_dW2
        nabla_H1[2] = A[0][2] * diff_G2 + diff_F0 * B[2][2] - A[2][2] * diff_G0 - diff_F2 * B[0][2]; // dF1_dW3 * [G3] + [F1]*dG3_dW3 - dF3_dW3*[G1] - [F3]*dG1_dW3
    }

    return;
}

// Nabla H2. The user will reserve space for Uref, p and out, all
// arrays of size = 3.
//
// In the formulae the point is refered to as p*, here it is p.
//
// type: _SHOCK_SIMPLE_ACCUMULATION_ or _SHOCK_GENERAL_ACCUMULATION_.
//

void ShockContinuationMethod3D2D::jet_H2(double *p, double &H2, double *nabla_H2) {
 const FluxFunction & shock_flux_object = fluxFunction();
    const AccumulationFunction & shock_accumulation_object = accumulationFunction();
    if (type == _SHOCK_SIMPLE_ACCUMULATION_) {
//        double F0[3];
//        fill_with_jet(shock_flux_object, 3, Uref, 0, &F0[0], 0, 0);

        double F[3];
        double A[3][3];
        shock_flux_object.fill_with_jet(3, p, 1, &F[0], &A[0][0], 0);

//        H2 = (F[1] - F0[1])*(p[2] - Uref[2]) - (F[2] - F0[2])*(p[1] - Uref[1]);
        H2 = (F[1] - Fref.component(1))*(p[2] - ref_point.component(2)) - (F[2] - Fref.component(2))*(p[1] - ref_point.component(1));

//        nabla_H2[0] = A[1][0]*(p[2] - Uref[2]) - A[2][0]*(p[1] - Uref[1]);
//        nabla_H2[1] = A[1][1]*(p[2] - Uref[2]) - (A[2][1]*(p[1] - Uref[1]) + (F[2] - F0[2]));
//        nabla_H2[2] = A[1][2]*(p[2] - Uref[2]) + (F[1] - F0[1]) - A[2][2]*(p[1] - Uref[1]);
        nabla_H2[0] = A[1][0]*(p[2] - ref_point.component(2)) - A[2][0]*(p[1] - ref_point.component(1));
        nabla_H2[1] = A[1][1]*(p[2] - ref_point.component(2)) - (A[2][1]*(p[1] - ref_point.component(1)) + (F[2] - Fref.component(2)));
        nabla_H2[2] = A[1][2]*(p[2] - ref_point.component(2)) + (F[1] - Fref.component(1)) - A[2][2]*(p[1] - ref_point.component(1));
    } else {
//        double F0[3];
//        double G0[3];

        double F[3];
        double G[3];
        double A[3][3];
        double B[3][3];

        double diff_F0, diff_F1, diff_F2;
        double diff_G0, diff_G1, diff_G2;

//        fill_with_jet(shock_flux_object, 3, Uref, 0, &F0[0], 0, 0);
//        fill_with_jet(shock_accumulation_object, 3, Uref, 0, &G0[0], 0, 0);

        shock_flux_object.fill_with_jet(3, p, 1, &F[0], &A[0][0], 0);
        shock_accumulation_object.fill_with_jet(3, p, 1, &G[0], &B[0][0], 0);

//        diff_F0 = F[0] - F0[0]; // [F1]
//        diff_F1 = F[1] - F0[1]; // [F2]
//        diff_F2 = F[2] - F0[2]; // [F3]

//        diff_G0 = G[0] - G0[0]; // [G1]
//        diff_G1 = G[1] - G0[1]; // [G2]
//        diff_G2 = G[2] - G0[2]; // [G3]
        diff_F0 = F[0] - Fref.component(0); // [F1]
        diff_F1 = F[1] - Fref.component(1); // [F2]
        diff_F2 = F[2] - Fref.component(2); // [F3]

        diff_G0 = G[0] - Gref.component(0); // [G1]
        diff_G1 = G[1] - Gref.component(1); // [G2]
        diff_G2 = G[2] - Gref.component(2); // [G3]

        H2 = diff_F1 * diff_G2 - diff_F2*diff_G1;

        nabla_H2[0] = A[1][0] * diff_G2 + diff_F1 * B[2][0] - A[2][0] * diff_G1 - diff_F2 * B[1][0]; // dF2_dW1 * [G3] + [F2]*dG3_dW1 - dF3_dW1*[G2] - [F3]*dG2_dW1
        nabla_H2[1] = A[1][1] * diff_G2 + diff_F1 * B[2][1] - A[2][1] * diff_G1 - diff_F2 * B[1][1]; // dF2_dW2 * [G3] + [F2]*dG3_dW2 - dF3_dW2*[G2] - [F3]*dG2_dW2
        nabla_H2[2] = A[1][2] * diff_G2 + diff_F1 * B[2][2] - A[2][2] * diff_G1 - diff_F2 * B[1][2]; // dF2_dW3 * [G3] + [F2]*dG3_dW3 - dF3_dW3*[G2] - [F3]*dG2_dW3
    }

    return; 
}

void ShockContinuationMethod3D2D::jet_N(double plane_point[], double a1, double a2, double v1[], double v2[], double N[], double *DN) {
    double H1, nablaH1[3], H2, nablaH2[3], p[3];

    plane_mapping(plane_point, a1, a2, v1, v2, p);
    //    printf("This is the initial plane_point = (%le, %le, %le)\n", plane_point[0], plane_point[1], plane_point[2]);
    //    printf("This is the point to be passed to the jets p = (%le, %le, %le)\n", p[0], p[1], p[2]);

    jet_H1(p, H1, nablaH1);
    jet_H2(p, H2, nablaH2);

    //    printf("This is the nablaH1 for calculating the jacobian = (%le, %le, %le)\n", nablaH1[0], nablaH1[1], nablaH1[2]);
    //    printf("This is the nablaH2 for calculating the jacobian = (%le, %le, %le)\n", nablaH2[0], nablaH2[1], nablaH2[2]);

    N[0] = H1;
    N[1] = H2;

    //    for (int i = 0; i < n - 1; i++) printf("Inside Newton_plane: N[%d] = %e\n", i, N[i]);

    DN[0] = dotprod(3, nablaH1, v1);
    DN[1] = dotprod(3, nablaH1, v2);
    DN[2] = dotprod(3, nablaH2, v1);
    DN[3] = dotprod(3, nablaH2, v2);

    return;
}

int ShockContinuationMethod3D2D::solver(int nn, double *A, double *b, double *x) {
    double eps = 1e-10;
    double det, anorm;

    /*    printf("Inside solver:\n");
          printf("    A = ");
          for (int i = 0; i < nn; i++){
              if (i == 0) printf("[");
              else printf("        [");
              for (int j = 0; j < nn; j++){
                  printf("%e ", A[i*nn + j]);
              }
              printf("]\n");
          }*/

    switch (nn) {
        case 1:
            if (fabs(A[0]) <= eps) return ABORTED_PROCEDURE;

            x[0] = b[0] / A[0];

            return SUCCESSFUL_PROCEDURE;
            break;

        case 2:
            det = A[0] * A[3] - A[1] * A[2];
            anorm = 0.0;
            for (int i = 0; i < nn * nn; i++) anorm += A[i] * A[i];

            //          printf("det = %g, isnan = %d\n", det, isnan(det));

            if (fabs(det) <= (eps * anorm)) return ABORTED_PROCEDURE;

            x[0] = (b[0] * A[3] - b[1] * A[1]) / det;
            x[1] = (A[0] * b[1] - A[2] * b[0]) / det;

            return SUCCESSFUL_PROCEDURE;
            break;

        case 3:
            det = A[0]*(A[4] * A[8] - A[5] * A[7])
                    - A[3]*(A[1] * A[8] - A[7] * A[2])
                    + A[6]*(A[1] * A[5] - A[4] * A[2]);

            anorm = 0;
            for (int i = 0; i < nn * nn; i++) anorm += A[i] * A[i];

            if (fabs(det) <= (eps * anorm)) return ABORTED_PROCEDURE;

            x[0] = (b[0]*(A[4] * A[8] - A[7] * A[5])
                    - b[1]*(A[1] * A[8] - A[7] * A[2])
                    + b[2]*(A[1] * A[5] - A[4] * A[2])
                    ) / det;

            x[1] = (-b[0] * (A[3] * A[8] - A[6] * A[5])
                    + b[1] * (A[0] * A[8] - A[6] * A[2])
                    - b[2] * (A[0] * A[5] - A[3] * A[2])
                    ) / det;

            x[2] = (b[0] * (A[3] * A[7] - A[6] * A[4])
                    - b[1] * (A[0] * A[7] - A[6] * A[1])
                    + b[2] * (A[0] * A[4] - A[3] * A[1])
                    ) / det;

            return SUCCESSFUL_PROCEDURE;
            break;

        default: // 4 or greater
            int i, j;
            int dim = nn;
            int nrhs = 1;
            int lda = nn;
            int ipiv[nn];
            int ldb = nn;
            int info;

            // Create a transposed copy of A to be used by LAPACK's dgesv:
            double B[nn][nn];
            for (i = 0; i < nn; i++) {
                for (j = 0; j < nn; j++) B[j][i] = A[i * nn + j];
            }

            // Create a copy of b to be used by LAPACK's dgesv:
            double bb[nn];
            for (i = 0; i < nn; i++) bb[i] = b[i];

            dgesv_(&dim, &nrhs, &B[0][0], &lda, &ipiv[0], &bb[0], &ldb, &info);

            if (info == 0) {
                for (i = 0; i < nn; i++) x[i] = bb[i];
                return SUCCESSFUL_PROCEDURE;
            } else return ABORTED_PROCEDURE;
            break;
    }

}

//ShockContinuationMethod3D2D::ShockContinuationMethod3D2D(int dim, int family,const  FluxFunction & f, const AccumulationFunction & a, const Boundary  & b, double Ur[], double tol, double epsilon, int t) :
//            ShockMethod(dim,f,a,b),
//family_(family),
//eps(epsilon),
//type(t),
//tolerance(tol) {
//    delta = 1e-10;
//    Uref = new double[3];
//    for (int i = 0; i < dimension(); i++) Uref[i] = Ur[i];
//
//}


// Init for the case when the initial point is Uref.
//
// Given the family and the increase condition, return a plane and a reference vector.
//

int ShockContinuationMethod3D2D::init(int family, int increase, Plane &plane, RealVector &refvec, double &rfs, double &es) {

    int n = dimension();
    const FluxFunction & shock_flux_object = fluxFunction();
    const AccumulationFunction & shock_accumulation_object = accumulationFunction();

    /* In the first step we need to initialize the shock curve in the chosen direction */
//    cout<<"Inicializando com init inteiro"<<endl;
    double Upr[n], Upl[n]; // These are two possible initial points for the shock curve
    double v1[n], v2[n]; // These are the two vectors on the first plane.  (notice that we use the SAME plane for both Upr and Upl).
    double epsilon = eps;
    double init_epsilon = 3.0*eps;

    double epsilon_start = epsilon;
    int rebounds_first_step = 0;

    //  Now we make our first run of the Newton method.
    double pr[3], pl[3];

    // Check if norm(Upr - pr) < delta.
    double Upr_pr[n];
    double Upl_pl[n];

    double normr, norml;

    int count_do = 0;

    int info_r, info_l;

    printf("BEGIN INIT.\n");
    do {
        plane_start(family, Upr, Upl, v1, v2, init_epsilon); //printf("here 1\n");

        std::cout << "After plane start: v1 = (" << v1[0] << ", " << v1[1] << ", " << v1[2] << "), v2 = (" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;

        info_r = Newton_plane(Upr, v1, v2, pr); //printf("here 2\n");
        info_l = Newton_plane(Upl, v1, v2, pl); //printf("here 3\n");

        for (int i = 0; i < n; i++) {
            Upr_pr[i] = Upr[i] - pr[i];
            Upl_pl[i] = Upl[i] - pl[i];
        }

        init_epsilon /= 2.0;
        rebounds_first_step++;

        normr = euclidean_norm(3, Upr_pr);
        norml = euclidean_norm(3, Upl_pl);

        count_do++;
//    } while (max(normr, norml) > 5e-1 /*delta*/ && count_do < 20);
    } while ((info_r == SHOCK_NEWTON_CONVERGENCE_ERROR || info_l == SHOCK_NEWTON_CONVERGENCE_ERROR) /*delta*/ && count_do < 20);
    printf("END INIT.\n");

    if (debugshock == 1){
        std::cout << "After do-while (count_do = " << count_do <<  "): v1 = (" << v1[0] << ", " << v1[1] << ", " << v1[2] << "), v2 = (" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;
    }

//    double epsilon_fix = epsilon;

    // Check if the speed is monotonic
    vector<eigenpair> e;

    double A[n][n];
//    fill_with_jet(shock_flux_object, n, Uref, 1, 0, &A[0][0], 0);
    shock_flux_object.fill_with_jet(n, initial_point.components(), 1, 0, &A[0][0], 0);

    if (type == _SHOCK_SIMPLE_ACCUMULATION_) Eigen::eig(n, &A[0][0], e);
    else {
        double B[n][n];
//        fill_with_jet(shock_accumulation_object, n, Uref, 1, 0, &B[0][0], 0);
        shock_accumulation_object.fill_with_jet(n, initial_point.components(), 1, 0, &B[0][0], 0);
        Eigen::eig(n, &A[0][0], &B[0][0], e);
    }


    if (debugshock == 1){
        std::cout << "    After EIGEN" << std::endl;
    }

    double sm = e[family].r;
//    double sr = shockspeed(n, family, Uref, pr);
//    double sl = shockspeed(n, family, Uref, pl);

    double sr = shockspeed(n, family, initial_point.components(), pr);
    double sl = shockspeed(n, family, initial_point.components(), pl);

    if (debugshock == 1){
        std::cout << "    After shockspeed" << std::endl;
    }

    /* printf("Family: %d, increase = %d\n", family, increase);
    printf("sr = %f, sm = %f, sl = %f\n", sr, sm, sl);
    for (int i = 0; i < n; i++) printf("pr[%d] = %e     pl[%d] = %e\n", i, pr[i], i, pl[i]); */

    double Uprevious[n];

    if ( shock_is_initial == SHOCK_CURVE_AT_BOUNDARY ) {
        for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
//        v1[0] = v1[1] = v1[2] = 1.0;
//        v2[0] = -1.0; v2[1] = v2[2] = 1.0;
    }
    else if ( shock_is_initial == SHOCK_CURVE_AT_SINGLEPHASE ) {
        if (increase == WAVE_FORWARD) for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
        else                          for (int i = 0; i < n; i++) Uprevious[i] = pr[i];
    }
    // Speed should increase
    else if (increase == WAVE_FORWARD) {
        if (sl > sm && sm > sr) {
            for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
            /*printf("shock init: 1\n");*/
        } else if (sl < sm && sm < sr) {
            for (int i = 0; i < n; i++) Uprevious[i] = pr[i];
            /*printf("shock init: 2\n");*/
        } else if ((sl < sm && sm > sr) || (sl > sm && sm < sr)) {
            if (debugshock == 1){
                printf("3\n");
            }

            return ABORTED_PROCEDURE;
        }
//        } else if ( (sl < sm && sm > sr) || (sl > sm && sm < sr) ) {
//            printf("6\n");
//            for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
////            v1[0] = v1[1] = v1[2] = 1.0;
////            v2[0] = -1.0; v2[1] = v2[2] = 1.0;
//        }
    }// Speed should decrease
    else if (increase == WAVE_BACKWARD) {
        if (sl < sm && sm < sr) {
            for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
            /*printf("shock init: 4\n");*/
        } else if (sl > sm && sm > sr) {
            for (int i = 0; i < n; i++) Uprevious[i] = pr[i];
            /*printf("shock init: 5\n");*/
        } else if ((sl < sm && sm > sr) || (sl > sm && sm < sr)) {
            if (debugshock == 1){
                printf("6\n");
            }

            return ABORTED_PROCEDURE;
        }
//        } else if ( (sl < sm && sm > sr) || (sl > sm && sm < sr) ) {
//            printf("6\n");
//            for (int i = 0; i < n; i++) Uprevious[i] = pl[i];
////            v1[0] = v1[1] = v1[2] = 1.0;
////            v2[0] = -1.0; v2[1] = v2[2] = 1.0;
//        }
    } else return ABORTED_PROCEDURE;

    // Output: plane

//    std::cout << "Filling plane: v1 = (" << v1[0] << ", " << v1[1] << ", " << v1[2] << "), v2 = (" << v2[0] << ", " << v2[1] << ", " << v2[2] << ")" << std::endl;
    for (int i = 0; i < n; i++) {
        plane.vec[0].component(i) = v1[i];
        plane.vec[1].component(i) = v2[i];

        plane.point.component(i) = Uprevious[i];
    }

    // Output: reference vector
//    for (int i = 0; i < n; i++) refvec.component(i) = Uprevious[i] - Uref[i];
    for (int i = 0; i < n; i++) refvec.component(i) = Uprevious[i] - initial_point.component(i);

    

    es = epsilon_start;
    rfs = rebounds_first_step;

    return SUCCESSFUL_PROCEDURE;
}

// Init for the case when the initial point is NOT Uref.
//
// No family and the increase condition are necessary. Returns a plane and a reference vector.
//

int ShockContinuationMethod3D2D::init(const Plane &init_plane, const RealVector &init_refvec, Plane &plane, RealVector &refvec, double &rebounds_first_step, double &epsilon_start) {
    // Output: plane
    for (int i = 0; i < dimension(); i++) {
        plane.vec[0].component(i) = init_plane.vec[0].component(i);
        plane.vec[1].component(i) = init_plane.vec[1].component(i);

        plane.point.component(i) = init_plane.point.component(i);
    }

    // Output: reference vector
    for (int i = 0; i < dimension(); i++) refvec.component(i) = init_refvec.component(i);

    return SUCCESSFUL_PROCEDURE;
}

// Compute the shockcurve using the Newton method.
//

int ShockContinuationMethod3D2D::curve(int family, double maxnum, int increase, std::vector<RealVector> &out, int &edge) {
    out.clear();
    int n = dimension();
    // rv will be used to store temporarily the output.
    RealVector rv(n);

    // Store the initial point
//    for (int i = 0; i < n; i++) rv.component(i) = Uref[i];
    rv = initial_point;
    out.push_back(rv);

    double epsilon = eps;
    double epsilon_fix = 3.0*epsilon;

    Plane init_plane(n);
    RealVector refvec(n);
    double rebounds_first_step, epsilon_start;
    int info_init = init(family, increase, init_plane, refvec, rebounds_first_step, epsilon_start);
    if (info_init == ABORTED_PROCEDURE) return ABORTED_PROCEDURE;

//    // So far we are only testing
//    if (!shock_is_initial){
//    std::cout << "info_init: " << info_init << std::endl;
//    std::cout << "Init plane point:  " << init_plane.point << std::endl;
//    std::cout << "Init plane vec[0]: " << init_plane.vec[0] << std::endl;
//    std::cout << "Init plane vec[1]: " << init_plane.vec[1] << std::endl;


//        init_plane.point.component(0) = -0.5;
//        init_plane.point.component(1) =  0.0;
//        init_plane.point.component(2) =  0.5;

//        init_plane.vec[0].component(0) = -1.0;
//        init_plane.vec[0].component(1) = 1.0;
//        init_plane.vec[0].component(2) = 1.0;

//        init_plane.vec[1].component(0) = 1.0;
//        init_plane.vec[1].component(1) = 1.0;
//        init_plane.vec[1].component(2) = -1.0;


//    std::cout << "info_init: " << info_init << std::endl;
//    std::cout << "Init plane point:  " << init_plane.point << std::endl;
//    std::cout << "Init plane vec[0]: " << init_plane.vec[0] << std::endl;
//    std::cout << "Init plane vec[1]: " << init_plane.vec[1] << std::endl;


////        std::cout << "Paused..." << std::endl;
////        int temp;
////        std::cin >> temp;
//    }


    // TODO: Extract Uprevious = plane.point, v1 = plane.vec[0], plane.vec[1], etc.
    double Uprevious[n], v1[n], v2[n];
    for (int i = 0; i < n; i++) {
        Uprevious[i] = init_plane.point.component(i);
        v1[i] = init_plane.vec[0].component(i);
        v2[i] = init_plane.vec[1].component(i);
    }


    // The curve proper
    int num = 1;
    int counter_rebounds = 0; // This is an auxiliary variable used for counting the number of consecutive points that need only one iteration of the adaptative method.


    while (num < maxnum) {

        printf("ShockContinuationMethod3D2D::curve. v1 = (%f, %f, %f), v2 = (%f, %f, %f)\n", v1[0], v1[1], v1[2], v2[0], v2[1], v2[2]);
        double temp[3];
        vectprod(v1, v2, temp);
        normalize(3, temp);

        normalize(3, refvec.components());
        printf("ShockContinuationMethod3D2D::curve. refvec = (%f, %f, %f), v1 x v2 = (%f, %f, %f)\n", refvec[0], refvec[1], refvec[2], temp[0], temp[1], temp[2]);

        epsilon = epsilon_fix;
        double normprevious;
        double old_previous[n];
        int counter;
        int inner_counter = 0;
        int info_newton;

        do {
            counter = 0; // counter counts the number of adaptative runs needed for arriving to the desired tolerance, i.e. normprevious > delta.
            double H1, nH1[n];
            double H2, nH2[n];

            jet_H1(Uprevious, H1, nH1);
            jet_H2(Uprevious, H2, nH2);

            double direction[n];
            vectprod(nH1, nH2, direction);
            normalize(n, direction);

            // Check if direction is congruent with refvec
            if (dotprod(3, direction, refvec.components()) < 0) for (int i = 0; i < n; i++) direction[i] = -direction[i];

            double vec_previous1[n];
            double vec_previous2[n];
            for (int i = 0; i < n; i++) {
                vec_previous1[i] = v1[i];
                vec_previous2[i] = v2[i];
            }

            double plane_point[n];

            //plane(Uprevious, direction, vec_previous1, vec_previous2, plane_point, v1, v2, epsilon);

            for (int i = 0; i < 3; i++){
                plane_point[i] = Uprevious[i] + epsilon * direction[i];

                v1[i] = nH1[i];
                v2[i] = nH2[i];
            }
            normalize(3, v1);
            normalize(3, v2);

            // Update refvec and do Newton
            for (int i = 0; i < n; i++) old_previous[i] = Uprevious[i];
            info_newton = Newton_plane(plane_point, v1, v2, Uprevious); // printf("here 2\n");
            //if (info == SHOCK_NEWTON_CONVERGENCE_ERROR) return ABORTED_PROCEDURE;

            if (debugshock == 1){
                std::cout << "ShockContinuationMethod3D2D::curve(). info_newton = " << info_newton << std::endl;
            }

            double Uprevious_plane_point[n];
            for (int i = 0; i < n; i++) {
                Uprevious_plane_point[i] = Uprevious[i] - plane_point[i];
            }
            normprevious = euclidean_norm(3, Uprevious_plane_point);
            epsilon /= 2.0;
            counter++;

            inner_counter++;
            if (inner_counter > 10) return ABORTED_PROCEDURE;
//        } while (normprevious > delta && inner_counter < 100);
        } while (info_newton == SHOCK_NEWTON_CONVERGENCE_ERROR && inner_counter < 20);

        // BELOW THE ADAPTIVE METHOD FOR THE SIZE OF THE VECTOR

        if (counter == 1) { // Whenever the last point needs none adaptations to converge, counter is 1.
            // Therefore we must re-adapt the epsilon_fix for the next calculation until
            // this happens again.

            counter_rebounds++; // This will count the number of points that passed easily through the convergence method.
            //printf("counter_rebounds   =%d\n", counter_rebounds  );
            //printf("rebounds_first_step=%d\n",rebounds_first_step);

            if (counter_rebounds <= rebounds_first_step) { // Whenever the number of re-adjustments is not too big
                // we can keep using a bigger epsilon_fix for the nextrun.
                if (epsilon_fix < epsilon_start) epsilon_fix *= 2;
            } else {
                counter_rebounds = 0; // When we have too many readjustments implying we arrived to the biggest
                // epsilon accepted, we should keep the biggest possible epsilon
                // bounded by epsilon_start.
                epsilon_fix /= 2;
            }
        }
        ///////

        // Check for NAN's
        for (int i = 0; i < n; i++) {
            if (isnan(rv.component(i))) {
                printf("Aborting... num = %d\n", num);
                return ABORTED_PROCEDURE;
            }
        }

        // New: Check if the point is within the boundary
        //        int out_edge;
        RealVector p(n), q(n), r(n);
        p = out[out.size() - 1]; // Previous point
        for (int i = 0; i < n; i++) q.component(i) = Uprevious[i];

        int info_intersect = boundary().intersection(p, q, r, edge);

        if (info_intersect == 1) { // Both inside
            out.push_back(q);
        } else if (info_intersect == -1) { // Both outside
            //            cout << "No primeiro else" << endl;
            return ABORTED_PROCEDURE;
        } else { // New point outside
            out.push_back(r);

            //            edge = out_edge;
            return ABORTED_PROCEDURE;
        }

        // Update the refvec
        for (int i = 0; i < n; i++) refvec[i] = Uprevious[i] - old_previous[i];
        num++;
    }

    return SUCCESSFUL_PROCEDURE;
}

//void ShockContinuationMethod3D2D::Newton_plane(double plane_point[], double v1[], double v2[], double *pnew) {
int ShockContinuationMethod3D2D::Newton_plane(double plane_point[], double v1[], double v2[], double *pnew) {//Upr, v1, v2, pr

    // The initial point to be used in the Newton method is (a1,a2)=0 that corresponds to the plane_point in the plane coordinates.

    double N[2];
    double DN[2][2];
    double aold[2] = {0., 0.}; // We need to initialize a at 0.
    double anew[2], err[2];
//    double norm_delta_a = 2. * tolerance; /* just to make its way through the while... this is the norm of the difference of the vectors.  Should we adimensionalize norm_delta_a, w.r. to
//                                          the first error? */

    double norm_delta_a = 2e-2; /* just to make its way through the while... this is the norm of the difference of the vectors.  Should we adimensionalize norm_delta_a, w.r. to
                                          the first error? */

    int iterations = 1;
    // double norm_delta_a;


    //   printf("*********** Inside Newton_plane, before while.\n");

    while (iterations < 10 && norm_delta_a > 1e-2 && norm_delta_a < 10.0) { // was: norm_delta_a > tolerance


        //       printf("Inside Newton_plane: iterations = %d < 10 = %d\n", iterations, iterations < 10);

        //       printf("Inside Newton_plane: (norm_delta_a = %e > tolerance = %e) = %d\n", norm_delta_a, tolerance, norm_delta_a > tolerance);

        //       printf("Inside Newton_plane: norm_delta_a < 1.0 = %d\n", norm_delta_a < 1.0);


        // Now we calculate the jet of N at p, and at xold

        jet_N(plane_point, aold[0], aold[1], v1, v2, &N[0], &DN[0][0]); // We calculate the JET for the expression of the Rankine-Hugoniot Locus system at the plane.

        //        int info =
        solver(dimension() - 1, &DN[0][0], &N[0], &err[0]);

        //       printf("solver.info = %d\n", info);


        // Approximation given by the Newton Method over the plane
        for (int i = 0; i < dimension() - 1; i++) {
            anew[i] = aold[i] - err[i];
            aold[i] = anew[i];
        }
        
                                   printf("    Newton_plane. tolerance = %e\n", tolerance);
        for (int i=0 ; i < 2; i++) printf("    Newton_plane. anew[%d] = %e\n", i, anew[i]);
        for (int i=0 ; i < 2; i++) printf("    Newton_plane. err [%d] = %e\n", i, err[i]);

        // Print anew (delete later)

        //jet_N(plane_point, aold[0], aold[1], v1, v2, &N[0], &DN[0][0]);
        //for (int i = 0; i < n - 1; i++) printf("After the solver: N[%d] = %e\n", i, N[i]);

        // Norm of delta_x
        norm_delta_a = 0;
        norm_delta_a = euclidean_norm(dimension() - 1, &err[0]);

        //       printf("norm_delta_a=%e\n", norm_delta_a);

        iterations++;
    }

    if (iterations >= 10) return SHOCK_NEWTON_CONVERGENCE_ERROR; // Added by Morante: 2013/05/29


    // jet_N(plane_point, aold[0], aold[1], v1, v2, &N[0], &DN[0][0]);
    plane_mapping(plane_point, anew[0], anew[1], v1, v2, pnew);

    return SHOCK_NEWTON_CONVERGENCE_OK;
}
