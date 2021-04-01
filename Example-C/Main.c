#include <stdio.h>
#include "TwoPunctures_c_api.h"

int main() {

   fprintf(stderr, "##### This is TwoPunctures-Standalone #####\n");

   fprintf(stderr, "Reading parameters...\n\n");

   // amend default parameters
   // this is a quick fix until we have a parfile parser
   int par_b =  6;

   double target_M_plus =  0.5;
   double par_P_plus_x =  0.2;
   double par_P_plus_y =  0.0;
   double par_P_plus_z =  0.0;
   double par_S_plus_x =  0.0;
   double par_S_plus_y =  0.0;
   double par_S_plus_z =  0.0;

   double target_M_minus =  0.5;
   double par_P_minus_x = -0.2;
   double par_P_minus_y =  0.0;
   double par_P_minus_z =  0.0;
   double par_S_minus_x =  0.0;
   double par_S_minus_y =  0.0;
   double par_S_minus_z =  0.0;

   // number of collocation points
   int npoints_A   = 20;
   int npoints_B   = 20;
   int npoints_phi = 16; // must be a multiple of 4

   // smoothen out the infinities at punctures
   double epsilon = 1e-6;
	
   TP_t tp = twopunctures_init(
         par_b,
         npoints_A,
         npoints_B,
         npoints_phi,
         epsilon,
         target_M_plus,
         par_P_plus_x,
         par_P_plus_y,
         par_P_plus_z,
         par_S_plus_x,
         par_S_plus_y,
         par_S_plus_z,
         target_M_minus,
         par_P_minus_x,
         par_P_minus_y,
         par_P_minus_z,
         par_S_minus_x,
         par_S_minus_y,
         par_S_minus_z 
         );

   // Solve the constraint equations
   fprintf(stderr, "Running Preparation code...\n");
   twopunctures_run(tp);

   // Interpolate at selected points 
   fprintf(stderr, "Now interpolate at some positions\n");
   const int dim = 3;
   double Q[TP_Qlen()], pos[dim];

   double xmin = -10.0, xmax = 10.0;
   double ymin = -10.0, ymax = 10.0;
   double zmin = -10.0, zmax = 10.0;

   int i[dim], points = 10;

   int printIndices[] = { 
      TP_g11(), 
      TP_K11(), 
      TP_lapse(), 
      TP_shift1(), 
      TP_shift2(), 
      TP_shift2(), 
      -1 
   };
   printf("%s %s %s %s %s %s %s %s %s\n", 
         "xcoord", 
         "ycoord", 
         "zcoord", 
         "g11", 
         "K11", 
         "lapse", 
         "shift1", 
         "shift2", 
         "shift3" 
      );

   for(i[0]=0;i[0]<points;i[0]++) {
      pos[0] = xmin + i[0] *  (xmax - xmin) / points;
      for(i[1]=0;i[1]<points;i[1]++) {
         pos[1] = ymin + i[1] * (ymax - ymin) / points;
         for(i[2]=0;i[2]<points;i[2]++) {
            pos[2] = zmin + i[2] * (zmax - zmin) / points;
                
            fprintf(stderr, "Interpolating at point number (%d,%d,%d), position (%f,%f,%f)\n",
                  i[0],i[1],i[2],pos[0],pos[1],pos[2]);
            twopunctures_interpolate(tp,pos,Q);

            printf("%5e %5e %5e ", pos[0], pos[1], pos[2]);
            for(int p=0;printIndices[p]>=0;p++) {
               printf("%5e ", Q[printIndices[p]]);
            }
            printf("\n");  
         }
      }
   }

   twopunctures_destroy(tp);
   return 0;
}
