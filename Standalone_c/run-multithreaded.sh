#!/bin/sh

# If you have compiled with -fopenmp, you can make use of
# the parallelized loops if you set the OMP environment
# variable:

export OMP_NUM_THREADS=2

./twopunctures > fieldvalues_res1.asc
