TARGET1  	:= hw1
TARGET2  	:= hw2_omp
TARGET3		:= hw3_mpi
WARN    	:= -W -Wall -Wstrict-prototypes -Wmissing-prototypes
INCLUDE 	:= 
PROFILE 	:= -pg
PARALLEL_OMP:= -fopenmp -O0
CFLAGS  	:= -D_REENTRANT ${WARN} ${INCLUDE} -lpthread ${PROFILE}
CC      	:= gcc

hw2: assignment2.o sequential.o rowwise.o columnwise.o other.o
	$(CC) -o ${TARGET2} ${PARALLEL_OMP} assignment2.o gendata.o sequential.o other.o columnwise.o rowwise.o

assignment2.o: assignment2.c assignment2.h gendata.h sequential.h
	$(CC) -c ${PARALLEL_OMP} assignment2.c

rowwise.o: rowwise.c rowwise.h
	$(CC) -c ${PARALLEL_OMP} rowwise.c
	
columnwise.o: columnwise.c columnwise.h
	$(CC) -c ${PARALLEL_OMP} columnwise.c
	
other.o: other.c other.h
	$(CC) -c ${PARALLEL_OMP} other.c
	
gendata.o: gendata.c gendata.h
	$(CC) -c gendata.c
	
sequential.o: sequential.c sequential.h
	$(CC) -c sequential.c	

.PHONY: clean

clean:
	rm -rf assignment2.o sequential.o rowwise.o columnwise.o other.o hw2_omp result_*
