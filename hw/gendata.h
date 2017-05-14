/*
 * gendata.h
 *
 *  Created on: 2011/11/30
 *      Author: kjchang
 */

#ifndef GENDATA_H_
#define GENDATA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double dtype;

// rSize x cSize Matrix
typedef struct matrix_t {
	int 	rSize;	// Matrix rows
	int 	cSize;	// Matrix columns
	dtype 	**mPtr;	// Matrix pointer
} Matrix;

// rSize x 1 Vector
typedef struct vector_t {
	int 	rSize;	// Vector size
	dtype 	*vPtr;	// Vector pointer
} Vector;

void *my_malloc (int id, int bytes);

void genVector (int r, Vector **v, int pattern);
void displayVector(Vector *v);
void destroyVector(Vector *v);

void genMatrix (int r, int c, Matrix **v, int pattern);
void displayMatrix(Matrix *m);
void destroyMatrix(Matrix *m);

void fileOutput(char *filename, Vector *v);
void fileInput(char *filename, Vector **v);

void doSomething(void);

char* threadID(pthread_t *tid);

#endif /* GENDATA_H_ */
