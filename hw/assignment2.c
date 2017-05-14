/*
 * Multi-core System and Software : Assignment #2
 *
 *  Created on: 2017/05/01
 *      Author: Kuei-Chung Chang
 */

// ------------------- Arguments ------------------------------------------------
// argv[0]: program itself
// argv[1]: parallel approach (s:sequential, r:rowwise, c:columnwise, o:others)
// argv[2]: number of worker threads (1: for sequential algorithm)
// argv[3]: rows of matrix
// argv[4]: columns of matrix, either vector size
// argv[5]: any integer seed used for matrix and vector generating
// argv[6]: doSomething() loop counts, used to extend the Matrix-Vector computing loading
// argv[7]: 0:silence(default), 1:verbose without showing data, 2: verbose with showing data
// -------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assignment2.h"
#include "gendata.h"
#include "sequential.h"
#include "rowwise.h"
#include "columnwise.h"
#include "other.h"

int	verbose=0;	// running message type
int	loading=0;	// doSomething( ) loading

int main (int argc, char *argv[]) {

	int 	m, n, vm, numThreads;			// m: Matrix rows, n: Matrix column, vm: Vector rows, numThread:number of worker threads
	char	filename[20];					// output result filename
	Vector	*vector=NULL;        			// vector
	Matrix 	*matrix=NULL;					// matrix
	Vector	*resultVector=NULL;				// vector for production result
	int		pattern=1;						//

	char	message[100];

	if (argc <= 6) { // check enough arguments
		smesg("[Usage]: hw2_omp [approach] [nthreads] [nrmatrix] [ncmatrix] [pattern] [loading] [verbose] \n");
		smesg("Example: hw2_omp seq 4 10 10 200 1000 2 \n");
		smesg(" ------------------- Arguments ------------------------------------------------\n");
		smesg(" approach: parallel approach (seq:sequential, row:rowwise, col:columnwise, oth:others) \n");
		smesg(" nthreads: number of worker threads (integer, 1: for sequential algorithm) \n");
		smesg(" nrmatrix: row size of matrix (integer) \n");
		smesg(" ncmatrix: column size of matrix, either vector size (integer) \n");
		smesg(" pattern: any integer seed used for generating matrix and vector (integer) \n");
		smesg(" loading: doSomething() loop counts (loading x 1000), used to extend the Matrix-Vector computing loading \n");
		smesg(" verbose: 0:silence(default), 1:verbose without showing data, 2: verbose with showing data \n");
		smesg(" ------------------------------------------------------------------------------- \n");

		exit(1);
	}

	numThreads 	= atoi(argv[2]);
	m 			= atoi(argv[3]);
	vm = n 		= atoi(argv[4]);
	pattern		= atoi(argv[5]);

	loading = atoi(argv[6]);
	if (argc >= 8) verbose = atoi(argv[7]);


	sprintf(message, "Generating 2-D Matrix with pattern(%d)..... \n", pattern);
	smesg(message);
	genMatrix(m, n, &matrix, pattern);
	if (verbose == 2)	displayMatrix(matrix);

	sprintf(message, "Generating Vector with pattern(%d)..... \n", pattern);
	smesg(message);
	genVector(vm, &vector, pattern);
	if (verbose == 2)	displayVector(vector);

	smesg("Computing Product Results ..... \n");
	struct timeval start_time = GetTimeStamp();

	if (strcmp(argv[1], "seq")==0 || numThreads == 1) {	// Sequential version

		smesg("Using sequential algorithm! \n");
		sequential(matrix, vector, &resultVector);
		sprintf(filename, "%s_%d.dat", FILENAME, 1);

	} else if(strcmp(argv[1], "row")==0) { // Parallel version - Row wise

		sprintf(message, "Using row-wise parallel algorithm with %d threads! \n", numThreads);
		smesg(message);
		row_wise_parallel(numThreads ,matrix, vector, &resultVector);
		sprintf(filename, "%s_row_%d.dat", FILENAME, numThreads);

	} else if(strcmp(argv[1], "col")==0) { // Parallel version - Column wise

		sprintf(message, "Using column-wise parallel algorithm with %d threads! \n", numThreads);
		smesg(message);
		column_wise_parallel(numThreads ,matrix, vector, &resultVector);
		sprintf(filename, "%s_col_%d.dat", FILENAME, numThreads);

	} else if(strcmp(argv[1], "oth")==0) { // Parallel version - Your design

		sprintf(message, "Using MY parallel algorithm with %d threads! \n", numThreads);
		smesg(message);
		my_parallel(numThreads ,matrix, vector, &resultVector);
		sprintf(filename, "%s_oth_%d.dat", FILENAME, numThreads);

	} else {

		smesg("Using sequential algorithm! \n");
		sequential(matrix, vector, &resultVector);

	}

	struct timeval end_time = GetTimeStamp();

	if (verbose == 2)	displayVector(resultVector);

	sprintf(message, "***** Program takes (%3.3f) microseconds.\n", getExecutionTime(start_time, end_time));
	smesg(message);

	sprintf(message, "Writing product result to file [ %s ] \n", filename);
	smesg(message);
	fileOutput(filename, resultVector); // CKJ: the file will not created without results

	// free memory space
	destroyVector(vector);
	destroyVector(resultVector);
	destroyMatrix(matrix);

	return 0;
}


// Used to output debug messages
void dmesg(char* msg) {
	if (verbose) {
		printf("       ===> %s", msg);
	}
}

// Used to output application messages
void smesg(char* msg) {
	printf("==> %s", msg);
}

struct timeval GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv;
}

// CKJ: return execution time (microseconds)
double getExecutionTime(struct timeval start_time, struct timeval end_time) {
	return (double)((end_time.tv_sec - start_time.tv_sec)*1000000L + (end_time.tv_usec - start_time.tv_usec));
}
