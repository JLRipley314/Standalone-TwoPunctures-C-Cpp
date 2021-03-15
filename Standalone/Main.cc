#include <stdio.h>
#include "TwoPunctures.h"

int main() {

	fprintf(stderr, "##### This is TwoPunctures-Standalone #####\n");

	fprintf(stderr, "Reading parameters...\n\n");
	
	TP::TwoPunctures tp;

	// amend default parameters
        // this is a quick fix until we have a parfile parser
	tp.par_b             =  6;

	tp.target_M_plus     =  0.5;
	tp.par_P_plus[0]     =  0.2;
	tp.par_P_plus[1]     =  0.0;
	tp.par_P_plus[2]     =  0.0;
	tp.par_S_plus[0]     =  0.0;
	tp.par_S_plus[1]     =  0.0;
	tp.par_S_plus[2]     =  0.0;

	tp.target_M_minus    =  0.5;
	tp.par_P_minus[0]    = -0.2;
	tp.par_P_minus[1]    =  0.0;
	tp.par_P_minus[2]    =  0.0;
	tp.par_S_minus[0]    =  0.0;
	tp.par_S_minus[1]    =  0.0;
	tp.par_S_minus[2]    =  0.0;
	
	// number of collocation points
        tp.npoints_A   = 20;
        tp.npoints_B   = 20;
        tp.npoints_phi = 16; // must be a multiple of 4

        // smoothen out the infinities at punctures
	tp.TP_epsilon = 1e-6;

        // Solve the constraint equations
	fprintf(stderr, "Running Preparation code...\n");
	tp.Run();
	
        // Interpolate at selected points 
	fprintf(stderr, "Now interpolate at some positions\n");
	using namespace TP::Z4VectorShortcuts; // to write g11, K11, lapse, etc.
	const int dim = 3;
	double Q[Qlen], pos[dim];

        double xmin = -10.0, xmax = 10.0;
        double ymin = -10.0, ymax = 10.0;
        double zmin = -10.0, zmax = 10.0;

        int i[dim], points = 10;

	int printIndices[] = { g11, K11, lapse, shift1, shift2, shift2, -1 };
	printf("%s %s %s %s %s %s %s %s %s\n", "xcoord", "ycoord", "zcoord", "g11", "K11", "lapse", "shift1", "shift2", "shift3" );
	
	for(i[0]=0;i[0]<points;i[0]++) {
           pos[0] = xmin + i[0] *  (xmax - xmin) / points;
           for(i[1]=0;i[1]<points;i[1]++) {
              pos[1] = ymin + i[1] * (ymax - ymin) / points;
              for(i[2]=0;i[2]<points;i[2]++) {
                 pos[2] = zmin + i[2] * (zmax - zmin) / points;
                      
                 fprintf(stderr, "Interpolating at point number (%d,%d,%d), position (%f,%f,%f)\n",
                        i[0],i[1],i[2],pos[0],pos[1],pos[2]);
                 tp.Interpolate(pos,Q);

                 printf("%5e %5e %5e ", pos[0], pos[1], pos[2]);
                 for(int p=0;printIndices[p]>=0;p++) {
                    printf("%5e ", Q[printIndices[p]]);
                 }
	         printf("\n");  
              }
           }
        } // end of 3-loop

	return 0;
}
