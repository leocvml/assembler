/*
 * Multi-core System and Software : Assignment #1
 *
 *  Created on: 2011/11/29
 *      Author: Kuei-Chung Chang
 */
#include <stdio.h>

#include "other.h"
#include "assignment2.h"



// Write your parallel algorithm here
void my_parallel(int numThreads ,Matrix *m, Vector *v, Vector **resultVector)
{


    
	int i, j;
	*resultVector = (Vector*) my_malloc(0, sizeof(Vector));
	(*resultVector)->rSize = m->rSize;
	(*resultVector)->vPtr = (dtype *) my_malloc(0, m->rSize * sizeof(dtype));

	
 #pragma omp for
	for (i = 0; i < m->rSize; i++) {
		(*resultVector)->vPtr[i] = 0.0;
	    for (j = 0; j < m->cSize; j++) {
	    	(*resultVector)->vPtr[i] += (m->mPtr)[i][j] * (v->vPtr)[j];

	    	doSomething(); // Always call this function to extend the whole computation loading.
	    }
	}
	

}
