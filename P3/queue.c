#include <assert.h>
#include <stdbool.h>

#include "queue.h"

// create an initializer for the queue
Queue* createQueue() {
	Queue* q =  (Queue*) malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

bool isEmpty(struct Queue* q) {
	return (q->size == 0);
}

int getQueueSize(struct Queue* q) {
	if (q->head == NULL) return 0;
	return q->size;
}

Customer *getFrontQueueElement(struct Queue* q) {
	return q->head->customer;
}


Customer *deQueue(struct Queue* q) {
	assert(!isEmpty(q));

	Node *temp = q->head;
	Customer *c = q->head->customer;
	q->head = q->head->next;

	free(temp);

	q->size--;

	if(q->size == 0) {
		q->head = NULL;
		q->tail = NULL;
	}

	return c;
}

// create a function that adds an element to the queue
void enQueue(struct Queue* q, Customer *customer) {
	if(q->head == NULL) {
		q->head = (struct Node*)malloc(sizeof(struct Node));
		q->head->customer = customer;
		q->head->next = NULL;
		q->tail = q->head;
	} else {
		q->tail->next = (struct Node*)malloc(sizeof(struct Node));
		q->tail->next->customer = customer;
		q->tail->next->next = NULL;
		q->tail = q->tail->next;
	}
	q->size++;
}

void printQueue(struct Queue* q) {
	if(isEmpty(q)) {
		printf("There are not items in the queue\n");
	}
	else {
		Node *node = q->head;
		while(node != NULL) {
			printf("Customer: %c%03d\n", node->customer->type, node->customer->id);
			node = node->next;
		}
	}
}

// empty the queue
void removeContents(struct Queue* q) {
	while(q->head != NULL) {
		struct Node* temp = q->head;
		q->head = q->head->next;
		free(temp);
	}
	q->size = 0;
}
