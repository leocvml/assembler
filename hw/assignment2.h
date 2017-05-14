/*
 * assignment2.h
 *
 *  Created on: 2011/12/4
 *      Author: kjchang
 */

#ifndef ASSIGNMENT2_H_
#define ASSIGNMENT2_H_

#define	FILENAME	"result"

#include <sys/time.h>
#include <omp.h>

void dmesg(char* msg);
void smesg(char* msg);
struct timeval GetTimeStamp();
double getExecutionTime(struct timeval start_time, struct timeval end_time) ;

#endif /* ASSIGNMENT2_H_ */
