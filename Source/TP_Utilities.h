#ifndef __TwoPunctures_Utilities__
#define __TwoPunctures_Utilities__

/* TwoPunctures:  File  "utilities.h"*/
/* these functions have no dependency on the TP parameters */


#include <math.h>
#include "TwoPunctures.h"

namespace TP {
namespace Utilities {

#define Pi  3.14159265358979323846264338328
#define Pih 1.57079632679489661923132169164	/* Pi/2*/
#define Piq 0.78539816339744830961566084582	/* Pi/4*/

#define TINY 1.0e-20
inline void swap(double a, double b) {double temp=a; a=b; b=temp;}

void nrerror (char error_text[]);
int *ivector (long nl, long nh);
double *dvector (long nl, long nh);
int **imatrix (long nrl, long nrh, long ncl, long nch);
double **dmatrix (long nrl, long nrh, long ncl, long nch);
double ***d3tensor (long nrl, long nrh, long ncl, long nch, long ndl,
		    long ndh);
void free_ivector (int *v, long nl, long nh);
void free_dvector (double *v, long nl, long nh);
void free_imatrix (int **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix (double **m, long nrl, long nrh, long ncl, long nch);
void free_d3tensor (double ***t, long nrl, long nrh, long ncl, long nch,
		    long ndl, long ndh);

int minimum2 (int i, int j);
int minimum3 (int i, int j, int k);
int maximum2 (int i, int j);
int maximum3 (int i, int j, int k);
int pow_int (int mantisse, int exponent);

void chebft_Zeros (double u[], int n, int inv);
void chebft_Extremes (double u[], int n, int inv);
void chder (double *c, double *cder, int n);
double chebev (double a, double b, double c[], int m, double x);
void fourft (double *u, int N, int inv);
void fourder (double u[], double du[], int N);
void fourder2 (double u[], double d2u[], int N);
double fourev (double *u, int N, double x);

double norm1 (double *v, int n);
double norm2 (double *v, int n);
double scalarproduct (double *v, double *w, int n);

} // namespac Utilities
} // namespace TP

#endif /* __TwoPunctures_Utilities__ */
