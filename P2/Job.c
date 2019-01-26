#include <stdlib.h>
#include "Job.h"

struct Job* createJob(int arrivalTime, float runTime, int priority)
{
	struct Job* j = (struct Job*) malloc(sizeof(struct Job));
	j->arrivalTime = arrivalTime;
	j->runTime = runTime;
	j->priority = priority;
	return j;
}
