#include <assert.h>
#include <stdbool.h>

#include "Queue.h"

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

Job *getFrontQueueElement(struct Queue* q) {
	return q->head->job;
}


Job *deQueue(struct Queue* q) {
	assert(!isEmpty(q));

	Node *temp = q->head;
	Job *job = q->head->job;
	q->head = q->head->next;

	free(temp);

	q->size--;

	if(q->size == 0) {
		q->head = NULL;
		q->tail = NULL;
	}

	return job;
}

// create a function that adds an element to the queue
void enQueue(struct Queue* q, Job *job) {
	if(q->head == NULL) {
		q->head = (struct Node*)malloc(sizeof(struct Node));
		q->head->job = job;
		q->head->next = NULL;
		q->tail = q->head;
	} else {
		q->tail->next = (struct Node*)malloc(sizeof(struct Node));
		q->tail->next->job = job;
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
			jobInfo(*node->job);
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

Job *getElement(struct Queue *q, int element) {
	Node *temp = q->head;
	int i = 0;
	while (temp != NULL) {
		if (i == element) return temp->job;
		temp = temp->next;
	}
	assert(0);
	return NULL;
}

void removeElement(struct Queue *q, int element) {
	Node *prev = NULL;
	Node *temp = q->head;
	int i = 0;
	while (temp != NULL) {
		if (i == element) {
			if (prev == NULL) {
				q->head = q->head->next;
				free(temp);
			} else {
				prev->next = temp->next;
				free(temp);
			}
			return;
		}
		prev = temp;
		temp = temp->next;
	}
	assert(0);
	return;
}
