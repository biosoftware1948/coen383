#include "../Job.h"
#include "../queue.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{	
	printf("\n\nentered");
	struct Queue* q = createQueue(10);
	struct Job* j = createJob(0, 10, 5);
	printf("\nCreated job with arrival time: %d, runtime: %f, priority: %d", 0, 10, 5);
	enqueue(q, j);

	printf("\n\nEnqued, size: %d\n", q->size);
	struct Job* j_out = dequeue(q);
 	printf("\njob has arrival time: %d, runtime: %f, priority: %d", j_out->arrivalTime, j_out->runTime, j_out->priority);	

	return 0;
}

