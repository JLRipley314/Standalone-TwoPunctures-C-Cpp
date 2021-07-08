#include <stdlib.h>

#include "TwoPunctures.h"
#include "TwoPunctures_c_api.h"

using namespace TP;
/*=========================================================================*/
EXTERNC TP_t twopunctures_init(
      const int lapse_kind,
      const int npoints_A,
      const int npoints_B,
      const int npoints_phi,
      const double epsilon,
      const double offset_plus,
      const double target_M_plus,
      const double par_P_plus_x,
      const double par_P_plus_y,
      const double par_P_plus_z,
      const double par_S_plus_x,
      const double par_S_plus_y,
      const double par_S_plus_z,
      const double offset_minus,
      const double target_M_minus,
      const double par_P_minus_x,
      const double par_P_minus_y,
      const double par_P_minus_z,
      const double par_S_minus_x,
      const double par_S_minus_y,
      const double par_S_minus_z 
      )
{
   TP_t tp = new TwoPunctures;

   TwoPunctures *typed_tp = static_cast<TwoPunctures*>(tp);

   /* 
    * black hole positions: offset: distance from orign 
    */
   double center_offset_x = 0.5 * (offset_plus + offset_minus);
   typed_tp->center_offset[0] = center_offset_x;
   typed_tp->par_b = 0.5 * (offset_plus - offset_minus);

   if (lapse_kind==0) {
      typed_tp->initial_lapse = "twopunctures-averaged";
   } else 
   if (lapse_kind==1) {
      typed_tp->initial_lapse = "twopunctures-antisymmetric";
   } else
   if (lapse_kind==2) {
      typed_tp->initial_lapse = "psi^n";
   } else
   if (lapse_kind==3) {
      typed_tp->initial_lapse = "brownsville";
   } else {
      /* use default: 
       * see TP_Parameters.cc 
       */
   }

   typed_tp->target_M_plus = target_M_plus;
   typed_tp->par_P_plus[0] = par_P_plus_x;
   typed_tp->par_P_plus[1] = par_P_plus_y;
   typed_tp->par_P_plus[2] = par_P_plus_z;
   typed_tp->par_S_plus[0] = par_S_plus_x;
   typed_tp->par_S_plus[1] = par_S_plus_y;
   typed_tp->par_S_plus[2] = par_S_plus_z;

   typed_tp->target_M_minus = target_M_minus;
   typed_tp->par_P_minus[0] = par_P_minus_x;
   typed_tp->par_P_minus[1] = par_P_minus_y;
   typed_tp->par_P_minus[2] = par_P_minus_z;
   typed_tp->par_S_minus[0] = par_S_minus_x;
   typed_tp->par_S_minus[1] = par_S_minus_y;
   typed_tp->par_S_minus[2] = par_S_minus_z;

   printf("==================================================\n");
   printf("TwoPunctures C API called\n");
   printf("==================================================\n");
   printf("lapse kind = %s\n", typed_tp->initial_lapse.c_str());
   printf("--------------------------------------------------\n");
   printf("target_M_plus = %f\n", typed_tp->target_M_plus);
   printf("P_plus_x = %f\n", typed_tp->par_P_plus[0]);
   printf("P_plus_y = %f\n", typed_tp->par_P_plus[1]);
   printf("P_plus_z = %f\n", typed_tp->par_P_plus[2]);
   printf("S_plus_x = %f\n", typed_tp->par_S_plus[0]);
   printf("S_plus_y = %f\n", typed_tp->par_S_plus[1]);
   printf("S_plus_z = %f\n", typed_tp->par_S_plus[2]);
   printf("--------------------------------------------------\n");
   printf("target_M_minus = %f\n", typed_tp->target_M_minus);
   printf("P_minus_x = %f\n", typed_tp->par_P_minus[0]);
   printf("P_minus_y = %f\n", typed_tp->par_P_minus[1]);
   printf("P_minus_z = %f\n", typed_tp->par_P_minus[2]);
   printf("S_minus_x = %f\n", typed_tp->par_S_minus[0]);
   printf("S_minus_y = %f\n", typed_tp->par_S_minus[1]);
   printf("S_minus_z = %f\n", typed_tp->par_S_minus[2]);
   printf("==================================================\n");

   // number of collocation points
   typed_tp->npoints_A   = npoints_A;
   typed_tp->npoints_B   = npoints_B;
   typed_tp->npoints_phi = npoints_phi; // must be a multiple of 4

   // smoothen out the infinities at punctures
   typed_tp->TP_epsilon = epsilon;

   return tp;
}
/*=========================================================================*/
void twopunctures_destroy(TP_t self)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   delete typed_self;
}
/*=========================================================================*/
void twopunctures_run(TP_t self)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   typed_self->Run();
}
/*=========================================================================*/
void twopunctures_interpolate(TP_t self, const double *pos, double *Q)
{
   TwoPunctures *typed_self = static_cast<TwoPunctures*>(self);
   typed_self->Interpolate(pos, Q);
}
/*=========================================================================*/
using namespace TP::Z4VectorShortcuts;

int TP_g11() {return g11;} 
int TP_g12() {return g12;} 
int TP_g13() {return g13;}
int TP_g22() {return g22;}
int TP_g23() {return g23;} 
int TP_g33() {return g33;} 
int TP_K11() {return K11;} 
int TP_K12() {return K12;} 
int TP_K13() {return K13;}
int TP_K22() {return K22;}
int TP_K23() {return K23;} 
int TP_K33() {return K33;}   
int TP_Z1() {return Z1;}
int TP_Z2() {return Z2;}
int TP_Z3() {return Z3;}
int TP_Theta() {return Theta;}
int TP_lapse()  {return lapse;}
int TP_shift1() {return shift1;}
int TP_shift2() {return shift2;}
int TP_shift3() {return shift3;}
int TP_b1() {return b1;}
int TP_b2() {return b2;}
int TP_b3() {return b3;}
int TP_A1() {return A1;}
int TP_A2() {return A2;}
int TP_A3() {return A3;}
int TP_B11() {return B11;}
int TP_B21() {return B21;}
int TP_B31() {return B31;}
int TP_B12() {return B12;}
int TP_B22() {return B22;}
int TP_B32() {return B32;}
int TP_B13() {return B13;}
int TP_B23() {return B23;}
int TP_B33() {return B33;}
int TP_D111() {return D111;}
int TP_D112() {return D112;}
int TP_D113() {return D113;}
int TP_D122() {return D122;}
int TP_D123() {return D123;}
int TP_D133() {return D133;}
int TP_D211() {return D211;}
int TP_D212() {return D212;}
int TP_D213() {return D213;}
int TP_D222() {return D222;}
int TP_D223() {return D223;}
int TP_D233() {return D233;}
int TP_D311() {return D311;}
int TP_D312() {return D312;}
int TP_D313() {return D313;}
int TP_D322() {return D322;}
int TP_D323() {return D323;}
int TP_D333() {return D333;} 
int TP_K0() {return K0;} 

// total length of conserved vector
int TP_Qlen() {return Qlen;}
