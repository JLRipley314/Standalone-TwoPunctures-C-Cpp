#!/bin/bash

# If you have compiled with -fopenmp, you can make use of
# the parallelized loops if you set the OMP environment
# variable:

#export OMP_NUM_THREADS=32
export OMP_NUM_THREADS=2

./twopunctures | tee fieldvalues.asc

#
# You can now display the values using gnuplot, ie.
#
# to see the lapse:
#   plot "fieldvalues.asc" using 1:4 w lp
# to see the g00:
#   plot "fieldvalues.asc" using 1:2 w lp
#
