CC=icpc#g++#
LD=icpc#g++#
LINKGSL=-lgsl -lgslcblas -lm
#DEBUG=-g
OPTIMIZE=-O2
library=libtwopunctures.a
# enable OpenMP parallelization
OMP=#-fopenmp

${library}: all
	ar rcs $@ *.o

all:
	${CC} -c ${DEBUG} ${OMP} ${OPTIMIZE} \
		TP_Parameters.cc Equations.cc \
		FuncAndJacobian.cc TP_Utilities.cc \
		Newton.cc TwoPunctures.cc \
		TwoPunctures_c_api.cc
	# we have a GSL dependency, make sure you have the GSL headers installed
	${CC} -c ${DEBUG} ${OMP} ${OPTIMIZE} CoordTransf.cc

clean:
	rm -f *.o ${library}
