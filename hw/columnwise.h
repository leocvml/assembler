/*
 * Multi-core System and Software : Assignment #1
 *
 *  Created on: 2011/11/29
 *      Author: Kuei-Chung Chang
 */

#ifndef COLUMNWISE_H_
#define COLUMNWISE_H_

#include "gendata.h"
#include "assignment2.h"

void column_wise_parallel(int nthreads, Matrix *m, Vector *v, Vector **resultVector);

#endif /* COLUMNWISE_H_ */
