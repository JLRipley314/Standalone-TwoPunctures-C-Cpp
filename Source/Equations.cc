/* TwoPunctures:  File  "Equations.c"*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "TwoPunctures.h"

namespace TP {
using namespace Utilities;

/* U.d0[ivar]   = U[ivar];  (ivar = 0..nvar-1) */
/* U.d1[ivar]   = U[ivar]_x;  */
/* U.d2[ivar]   = U[ivar]_y;  */
/* U.d3[ivar]   = U[ivar]_z;  */
/* U.d11[ivar]  = U[ivar]_xx; */
/* U.d12[ivar]  = U[ivar]_xy; */
/* U.d13[ivar]  = U[ivar]_xz;*/
/* U.d22[ivar]  = U[ivar]_yy;*/
/* U.d23[ivar]  = U[ivar]_yz;*/
/* U.d33[ivar]  = U[ivar]_zz;*/
/*=========================================================================*/
/* the Bowen-York (`BY') term [\tilde{A}_{ij}] * [\tilde{A}^{ij}] */
/*=========================================================================*/
double
TwoPunctures::BY_KKofxyz (double x, double y, double z)
{
  double r2_plus  = (x - par_b) * (x - par_b) + y * y + z * z;
  double r2_minus = (x + par_b) * (x + par_b) + y * y + z * z;
  double r_plus  = sqrt (r2_plus);
  double r_minus = sqrt (r2_minus);
  double r3_plus  = r_plus  * r2_plus;
  double r3_minus = r_minus * r2_minus;

  double n_plus[3], n_minus[3];
  n_plus[0]  = (x - par_b) / r_plus;
  n_minus[0] = (x + par_b) / r_minus;
  n_plus[1]  = y / r_plus;
  n_minus[1] = y / r_minus;
  n_plus[2]  = z / r_plus;
  n_minus[2] = z / r_minus;

  /* dot product: np_Pp = (n_+).(P_+); nm_Pm = (n_-).(P_-) */
  double np_Pp = 0;
  double nm_Pm = 0;
  for (int i = 0; i < 3; i++)
  {
    np_Pp += n_plus[i]  * par_P_plus[i];
    nm_Pm += n_minus[i] * par_P_minus[i];
  }

  /* cross product: np_Sp[i] = [(n_+) x (S_+)]_i; nm_Sm[i] = [(n_-) x (S_-)]_i*/
  double np_Sp[3], nm_Sm[3];
  np_Sp[0] = n_plus[1] * par_S_plus[2] - n_plus[2] * par_S_plus[1];
  np_Sp[1] = n_plus[2] * par_S_plus[0] - n_plus[0] * par_S_plus[2];
  np_Sp[2] = n_plus[0] * par_S_plus[1] - n_plus[1] * par_S_plus[0];
  nm_Sm[0] = n_minus[1] * par_S_minus[2] - n_minus[2] * par_S_minus[1];
  nm_Sm[1] = n_minus[2] * par_S_minus[0] - n_minus[0] * par_S_minus[2];
  nm_Sm[2] = n_minus[0] * par_S_minus[1] - n_minus[1] * par_S_minus[0];
  double AijAij = 0;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {				
      /* Bowen-York-Curvature */
      double Aij =
	+ 1.5 * (
              par_P_plus[i] * n_plus[j] 
            + par_P_plus[j] * n_plus[i]
            + np_Pp * n_plus[i] * n_plus[j]
            ) / r2_plus
	+ 1.5 * (
              par_P_minus[i] * n_minus[j] 
            + par_P_minus[j] * n_minus[i]
	    + nm_Pm * n_minus[i] * n_minus[j]
            ) / r2_minus
	- 3.0 * (
              np_Sp[i] * n_plus[j] 
            + np_Sp[j] * n_plus[i]
            ) / r3_plus
	- 3.0 * (
              nm_Sm[i] * n_minus[j] 
            + nm_Sm[j] * n_minus[i]
            ) / r3_minus;
      if (i == j)
	Aij -= +1.5 * (np_Pp / r2_plus + nm_Pm / r2_minus);
      AijAij += Aij * Aij;
    }
  }

  return AijAij;
}
/*=========================================================================*/
void
TwoPunctures::BY_Aijofxyz (double x, double y, double z, double Aij[3][3])
{ 
  double r2_plus  = (x - par_b) * (x - par_b) + y * y + z * z;
  double r2_minus = (x + par_b) * (x + par_b) + y * y + z * z;
  r2_plus  = sqrt (pow (r2_plus, 2)  + pow (TP_epsilon, 4));
  r2_minus = sqrt (pow (r2_minus, 2) + pow (TP_epsilon, 4));

  if (r2_plus < pow(TP_Tiny,2))
    r2_plus = pow(TP_Tiny,2);
  if (r2_minus < pow(TP_Tiny,2))
    r2_minus = pow(TP_Tiny,2);

  double r_plus  = sqrt (r2_plus);
  double r_minus = sqrt (r2_minus);
  double r3_plus = r_plus * r2_plus;
  double r3_minus = r_minus * r2_minus;

  double n_plus[3], n_minus[3];
  n_plus[0] = (x - par_b) / r_plus;
  n_minus[0] = (x + par_b) / r_minus;
  n_plus[1] = y / r_plus;
  n_minus[1] = y / r_minus;
  n_plus[2] = z / r_plus;
  n_minus[2] = z / r_minus;

  /* dot product: np_Pp = (n_+).(P_+); nm_Pm = (n_-).(P_-) */
  double np_Pp = 0;
  double nm_Pm = 0;
  for (int i = 0; i < 3; i++)
  {
    np_Pp += n_plus[i] * par_P_plus[i];
    nm_Pm += n_minus[i] * par_P_minus[i];
  }
  double np_Sp[3], nm_Sm[3];
  /* cross product: np_Sp[i] = [(n_+) x (S_+)]_i; nm_Sm[i] = [(n_-) x (S_-)]_i*/
  np_Sp[0] = n_plus[1] * par_S_plus[2] - n_plus[2] * par_S_plus[1];
  np_Sp[1] = n_plus[2] * par_S_plus[0] - n_plus[0] * par_S_plus[2];
  np_Sp[2] = n_plus[0] * par_S_plus[1] - n_plus[1] * par_S_plus[0];
  nm_Sm[0] = n_minus[1] * par_S_minus[2] - n_minus[2] * par_S_minus[1];
  nm_Sm[1] = n_minus[2] * par_S_minus[0] - n_minus[0] * par_S_minus[2];
  nm_Sm[2] = n_minus[0] * par_S_minus[1] - n_minus[1] * par_S_minus[0];
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {				
      /* Bowen-York-Curvature :*/
      Aij[i][j] =
        + 1.5 * (
              par_P_plus[i] * n_plus[j] 
            + par_P_plus[j] * n_plus[i]
	    + np_Pp * n_plus[i] * n_plus[j]
            ) / r2_plus
	+ 1.5 * (
              par_P_minus[i] * n_minus[j] 
            + par_P_minus[j] * n_minus[i]
	    + nm_Pm * n_minus[i] * n_minus[j]
            ) / r2_minus
	- 3.0 * (
              np_Sp[i] * n_plus[j] 
            + np_Sp[j] * n_plus[i]
            ) / r3_plus
	- 3.0 * (
              nm_Sm[i] * n_minus[j] 
            + nm_Sm[j] * n_minus[i]
            ) / r3_minus;
      if (i == j)
	Aij[i][j] -= +1.5 * (np_Pp / r2_plus + nm_Pm / r2_minus);
    }
  }
}
/*============================================================================*/
/* Nonlinear Equations */
// The system of (nvar) elliptic equations to be solved (i=0..nvar-1):
//    F_i(U[0],..,U[nvar-1] ; U_x[0],..U_x[nvar-1] ; .. ; U_zz[0]..U_zz[nvar-1]) = 0 
// must be entered in cartesian coordinates in the form
//   values[i] = F_i(U[0],..,U[nvar-1] ; U_x[0],..U_x[nvar-1] ; .. ; U_zz[0]..U_zz[nvar-1])
// Example: Poisson equation (U_xx + U_yy + U_zz = Source) for two variables:
//    values[0] = U.d11[0] + U.d22[0] + U.d33[0] - Source[0]
//    values[1] = U.d11[1] + U.d22[1] + U.d33[1] - Source[1]

// Example: Hamiltonian constraint for two Punctures with Bowen-York Curvature
/*============================================================================*/
void
TwoPunctures::NonLinEquations (double rho_adm,
     double A, double B, double X, double R,
		 double x, double r, double phi,
		 double y, double z, derivs U, double *values)
{ 
  double r_plus  = sqrt ((x - par_b) * (x - par_b) + y * y + z * z);
  double r_minus = sqrt ((x + par_b) * (x + par_b) + y * y + z * z);

  double psi =
      1. 
    + 0.5 * par_m_plus / r_plus 
    + 0.5 * par_m_minus / r_minus + U.d0[0]
    ;
  double psi2 = pow(psi,2);
  double psi7 = pow(psi,7);

  values[0] =
      U.d11[0] 
    + U.d22[0] 
    + U.d33[0] 
    + 0.125 * BY_KKofxyz (x, y, z) / psi7 
    + 2.0 * Pi / psi2/psi * rho_adm;

}
/*============================================================================*/
/* Linear Equations */
// The Jacobian of the system of (nvar) elliptic equations to be solved (i=0..nvar-1):
//    F_i(U[0],..,U[nvar-1] ; U_x[0],..U_x[nvar-1] ; .. ; U_zz[0]..U_zz[nvar-1]) = 0 
// must be entered in cartesian coordinates in the form
//   values[i] = (dF_i/dU[0])*dU.d0[0] + .. +(dF_i/dU_zz[nvar-1])*dU.d33[nvar-1]
// Example: Poisson equation (U_xx + U_yy + U_zz = Source) for two variables:
//    values[0] = dU.d11[0] + dU.d22[0] + dU.d33[0]
//    values[1] = dU.d11[1] + dU.d22[1] + dU.d33[1]

// Example: Hamiltonian constraint for two Punctures with Bowen-York Curvature
/*============================================================================*/
void
TwoPunctures::LinEquations (double A, double B, double X, double R,
	      double x, double r, double phi,
	      double y, double z, derivs dU, derivs U, double *values)
{
  
  double r_plus  = sqrt ((x - par_b) * (x - par_b) + y * y + z * z);
  double r_minus = sqrt ((x + par_b) * (x + par_b) + y * y + z * z);

  double psi =
      1. 
    + 0.5 * par_m_plus / r_plus 
    + 0.5 * par_m_minus / r_minus 
    + U.d0[0]
    ;
  double psi8 = pow(psi,8);

  values[0] = 
       dU.d11[0] 
     + dU.d22[0] 
     + dU.d33[0]
    - 0.875 * BY_KKofxyz (x, y, z) / psi8 * dU.d0[0]
    ;
}
/*============================================================================*/
} // namespace TP
