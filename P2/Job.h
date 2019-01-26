#ifndef JOB_H
#define JOB_H
#include <stdlib.h>

struct Job
{
	int arrivalTime;
	float runTime;
	int priority;
};

struct Job* createJob(int arrivalTime, float runTime, int priority);
#endif
