/*
 * openmp.h
 *
 *  Created on: 2011/12/4
 *      Author: kjchang
 */

#ifndef OPENMP_H_
#define OPENMP_H_

#include "gendata.h"
#include "assignment2.h"
#include <omp.h>

void openmp_parallel(int nthreads, Matrix *m, Vector *v, Vector **resultVector);

#endif /* OPENMP_H_ */
