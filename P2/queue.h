#ifndef QUEUE_H
#define QUEUE_H

#include "Job.h"

struct Queue
{
	int front;
	int rear;
	int size;
	unsigned capacity;
	struct Job** jobs;
};

struct Queue* createQueue(unsigned capacity);

int isFull(struct Queue* Q);

int isEmpty(struct Queue* Q);

int enqueue(struct Queue* q, struct Job* j);

struct Job* dequeue(struct Queue* q);

#endif
