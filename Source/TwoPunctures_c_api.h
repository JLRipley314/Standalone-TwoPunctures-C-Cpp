/*
 * C api for the standalone TwoPunctures code
 */
#ifndef _TWOPUNCTURES_C_API_H_
#define _TWOPUNCTURES_C_API_H_

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/*===========================================================================*/
/* An opaque type for the TwoPunctures class */
typedef void* TP_t;
/*===========================================================================*/
/* Member functions of TwoPunctures class */

EXTERNC TP_t twopunctures_init(
      const int lapse_kind,
      const int par_b,
      const int npoints_A,
      const int npoints_B,
      const int npoints_phi,
      const double epsilon,
      const double target_M_plus,
      const double par_P_plus_x,
      const double par_P_plus_y,
      const double par_P_plus_z,
      const double par_S_plus_x,
      const double par_S_plus_y,
      const double par_S_plus_z,
      const double target_M_minus,
      const double par_P_minus_x,
      const double par_P_minus_y,
      const double par_P_minus_z,
      const double par_S_minus_x,
      const double par_S_minus_y,
      const double par_S_minus_z 
      );
EXTERNC void twopunctures_destroy(TP_t self);
EXTERNC void twopunctures_run(TP_t self);
EXTERNC void twopunctures_interpolate(TP_t self, const double *pos, double *Q);
/*===========================================================================*/
/* named constants for accessing solution vector */

EXTERNC int TP_g11() ; 
EXTERNC int TP_g12() ; 
EXTERNC int TP_g13() ;
EXTERNC int TP_g22() ;
EXTERNC int TP_g23() ; 
EXTERNC int TP_g33() ; 
EXTERNC int TP_K11() ; 
EXTERNC int TP_K12() ; 
EXTERNC int TP_K13() ;
EXTERNC int TP_K22() ;
EXTERNC int TP_K23() ; 
EXTERNC int TP_K33() ;   
EXTERNC int TP_Z1() ;
EXTERNC int TP_Z2() ;
EXTERNC int TP_Z3() ;
EXTERNC int TP_Theta() ;
EXTERNC int TP_lapse()  ;
EXTERNC int TP_shift1() ;
EXTERNC int TP_shift2() ;
EXTERNC int TP_shift3() ;
EXTERNC int TP_b1() ;
EXTERNC int TP_b2() ;
EXTERNC int TP_b3() ;
EXTERNC int TP_A1() ;
EXTERNC int TP_A2() ;
EXTERNC int TP_A3() ;
EXTERNC int TP_B11() ;
EXTERNC int TP_B21() ;
EXTERNC int TP_B31() ;
EXTERNC int TP_B12() ;
EXTERNC int TP_B22() ;
EXTERNC int TP_B32() ;
EXTERNC int TP_B13() ;
EXTERNC int TP_B23() ;
EXTERNC int TP_B33() ; 
EXTERNC int TP_D111();
EXTERNC int TP_D112();
EXTERNC int TP_D113();
EXTERNC int TP_D122();
EXTERNC int TP_D123();
EXTERNC int TP_D133();
EXTERNC int TP_D211();
EXTERNC int TP_D212();
EXTERNC int TP_D213();
EXTERNC int TP_D222();
EXTERNC int TP_D223();
EXTERNC int TP_D233();
EXTERNC int TP_D311();
EXTERNC int TP_D312();
EXTERNC int TP_D313();
EXTERNC int TP_D322();
EXTERNC int TP_D323();
EXTERNC int TP_D333(); 
EXTERNC int TP_K0(); 

/* total length of conserved vector */
EXTERNC int TP_Qlen();

/*===========================================================================*/
#endif /* _TWOPUNCTURES_C_API_H_ */
