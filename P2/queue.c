#include "queue.h"
#include "Job.h"
#include <stdlib.h>

struct Queue* createQueue(unsigned capacity)
{
        struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
	q->capacity = capacity;
	q->front = 0;
	q->size = 0;
	q->rear = capacity - 1;
	q->jobs = (struct Job**) malloc(sizeof(struct Job*) * capacity);
	
	return q;
}

int isFull(struct  Queue* q)
{
	if (q->size == q->capacity)
	{
		return 1;
	}
	return 0;
}

int isEmpty(struct Queue* q)
{
	return q->size == 0;
}

int enqueue(struct Queue* q, struct Job* j)
{
	if (isFull(q))
	{
		return 0;
	}
	q->rear = (++q->rear) % q->capacity;
	q->jobs[q->rear] = j;
	++q->size;
	return 1;
}

struct Job* dequeue(struct Queue* q)
{
	struct Job* j = q->jobs[q->front];
	q->front = (++q->front) % q->capacity;
	q->size = --q->size;
	return j;
}

	







