#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Job.h"

typedef struct Node {
	Job *job;
	struct Node *next;
} Node;


typedef struct Queue {
	Node *head;
	Node *tail;
	int size;
} Queue;

struct Node* newNode(Job *j);

// create an initializer for the queue
Queue* createQueue();

// check if the queue is empty
bool isEmpty(struct Queue* q);

// get the queue size
int getQueueSize(struct Queue* q);

// create a function to get the front element from the queue
Job *getFrontQueueElement(struct Queue* q);

Job *deQueue(struct Queue* q);

// create a function that adds an element to the queue
void enQueue(struct Queue* q, Job *job);

// print each element in the queue
void printQueue(struct Queue* q);

// empty the queue
void removeContents(struct Queue* q);

Job *getElement(struct Queue *q, int element);

void removeElement(struct Queue *q, int element);


#endif /* QUEUE_H */
