/*
 * Multi-core System and Software : Assignment #1
 *
 *  Created on: 2011/11/29
 *      Author: Kuei-Chung Chang
 */

#ifndef ROWWISE_H_
#define ROWWISE_H_

#include "gendata.h"
#include "assignment2.h"
#include "sequential.h"

void *thread_function(int *partition);
void row_wise_parallel(int nthreads, Matrix *m, Vector *v, Vector **resultVector);

#endif /* ROWWISE_H_ */
