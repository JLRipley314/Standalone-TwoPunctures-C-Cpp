CC=g++
LD=g++
LINKGSL=-lgsl -lgslcblas -lm
#DEBUG=-g
OPTIMIZE=-O2
binary=twopunctures
# enable parallelization
OMP=-fopenmp

# This exemplary makefile shows how to include the twopunctures code
# as a (static) library, but you can of course also compile everything
# together without this intermediate step.
TP_INC=-I../libtwopunctures
TP_LINK=../libtwopunctures/libtwopunctures.a

thebinary:
	make -C ../libtwopunctures
	${CC} -c ${DEBUG} ${OMP} ${OPTIMIZE} ${TP_INC} Main.cc
	${LD} ${OMP} -o ${binary} Main.o ${TP_LINK} ${LINKGSL}

clean:
	rm -f *.o ${binary}
