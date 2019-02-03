#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Customer.h"

typedef struct Node {
	Customer *customer;
	struct Node *next;
} Node;


typedef struct Queue {
	Node *head;
	Node *tail;
	int size;
} Queue;

// create an initializer for the queue
Queue* createQueue();

// check if the queue is empty
bool isEmpty(struct Queue* q);

// get the queue size
int getQueueSize(struct Queue* q);

// create a function to get the front element from the queue
Customer *getFrontQueueElement(struct Queue* q);

Customer *deQueue(struct Queue* q);

// create a function that adds an element to the queue
void enQueue(struct Queue* q, Customer *c);

// print each element in the queue
void printQueue(struct Queue* q);

// empty the queue
void removeContents(struct Queue* q);


#endif /* QUEUE_H */
