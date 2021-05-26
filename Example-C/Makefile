CC=icc#gcc
LD=icc#gcc
LINKGSL=-lgsl -lgslcblas -lm
#DEBUG=-g
OPTIMIZE=-O2
binary=twopunctures
# enable parallelization
OMP=#-fopenmp

# This exemplary makefile shows how to include the twopunctures code
# as a (static) library, but you can of course also compile everything
# together without this intermediate step.
TP_INC=  ../Source
TP_LINK= ../Source/libtwopunctures.a
CPP_LINK= -lstdc++ ## need c++ std lib at linking

thebinary:
	make -C ${TP_INC}
	${CC} -c ${DEBUG} ${OMP} ${OPTIMIZE} -I${TP_INC} Main.c
	${LD} ${OMP} -o ${binary} Main.o ${TP_LINK} ${LINKGSL} $(CPP_LINK)

clean:
	rm -f *.o ${binary}
