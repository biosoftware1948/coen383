#include "../Job.h"
#include "../Queue.h"
#include "../CPU.h"


#include <stdlib.h>
#include <stdio.h>

int main()
{	
	
	printf("entered test\n");
	int NUM_JOBS=3;

	struct Job* jobs = createJobs(NUM_JOBS);
	printf("Jobs Created\n");

	struct Queue* q = createQueue();
	printf("Queue Created\n");

	for(int i = 0; i < NUM_JOBS; ++i) {
		enQueue(q, jobs[i]);
	}
	printf("Queue populated\n");
	printf("Printing Queue Contents:\n");
	printQueue(q);

	printf("Printing origtinal jobs list:\n");
	for(int i = 0; i < NUM_JOBS; ++i) {
		jobInfo(jobs[i]);
	}

	printf("Doing deQueue from Queue\n");
	deQueue(q);
	printQueue(q);

	printf("Getting front\n");
	struct Job j = getFrontQueueElement(q);
	printf("Printing that jobs info:\n");
	jobInfo(j);

	printf("Removing queue contents\n");
	removeContents(q);
	printf("printing queue (should be emnpty):\n");
	printQueue(q);


	printf("Sorting jobs by arrival time:\n");
	sort_by_arrival_time(jobs, NUM_JOBS);
	for(int i = 0; i < NUM_JOBS; ++i) {
		jobInfo(jobs[i]);
	}

	printf("Making CPU:\n");
	CPU* cpu = createCPU();

	printf("Giving CPU a job\n");
	giveCPUJob(cpu, jobs[0]);
	printf("cpu state: %d\n", cpu->cpuState);
	printf("Removing job from CPU\n");
	freeCPU(cpu);
	printf("cpu state: %d\n", cpu->cpuState);

	printf("Making a jobs copy:\n");
	Job* new_jobs = copyJobs(jobs, NUM_JOBS);
	printf("printing that copy\n");
	printAllJobs(new_jobs, NUM_JOBS);



	return 0;
}

