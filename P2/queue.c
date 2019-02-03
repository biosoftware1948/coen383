#include <assert.h>
#include <stdbool.h>

#include "Queue.h"

struct Node* newNode(Job *j) {
	struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
	temp->job = j;
	temp->next = NULL;
	return temp;
}

// create an initializer for the queue
Queue* createQueue() {
	Queue* q =  (Queue*) malloc(sizeof(Queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

bool isEmpty(struct Queue* q) {
	return getQueueSize(q) == 0;
}

int getQueueSize(struct Queue* q) {
	int count = 0;
	Node *temp = q->head;
	while (temp != NULL) {
		temp = temp->next;
		count++;
	}
	return count;
}

Job *getFrontQueueElement(struct Queue* q) {
	assert(!isEmpty(q));
	return q->head->job;
}


Job *deQueue(struct Queue* q) {
	assert(!isEmpty(q));
	q->size--;

	struct Node * temp = q->head;
	q->head = q->head->next;

	if (q->head == NULL) {
		q->tail = NULL;
	}

	return temp->job;
}

// create a function that adds an element to the queue
void enQueue(struct Queue* q, Job *job) {
	q->size++;
	struct Node *temp = newNode(job);

	if(q->head == NULL) {
		q->head = q->tail = temp;
		return;
	}

	q->tail->next = temp;
	q->tail = temp;
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
	assert(element <= q->size);

	int count = 0;
	Node *temp = q->head;

	while (temp != NULL) {
		if (count == element) return temp->job;

		temp = temp->next;
		++count;
	}

	assert(temp != NULL);
	return NULL;
}

void removeElement(struct Queue *q, int element) {
	Node *temp = q->head, *prev;
	int count = 0;

	if (temp != NULL && element == count) {
		q->head = temp->next;
		free(temp);
		return;
	}

	while (temp != NULL && element != count) {
		prev = temp;
		temp = temp->next;
		count++;
	}

	assert (temp == NULL);

	prev->next = temp->next;
	free (temp);
}
