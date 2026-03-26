#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct _Queue
{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};


Queue *queue_new(){

    int i;
    Queue *new_queue = NULL;

    if(!(new_queue = (Queue*)malloc(sizeof(Queue)))){
        return NULL;
    }

    for (i = 0; i < MAX_QUEUE; i++) {
        new_queue->data[i] = NULL;
    }   

    new_queue->front = &(new_queue->data[0]);
    new_queue->rear = &(new_queue->data[0]);
    
    return new_queue;
}

void queue_free(Queue *pq) { 
	free((void *)pq); 
}

Bool queue_is_empty(const Queue *q){

	if(!q){
		return TRUE;
	}

	if(q->rear == q->front){
		return TRUE;
	}

	return FALSE;
}
Bool _queue_is_full(const Queue *q) {

	if (q == NULL) {
		return TRUE;
	}
	if ((q->rear + 1 - q->front) % MAX_QUEUE == 0) {
		return TRUE;
	}

	return FALSE;
}

Status queue_push(Queue *q, void *ele){

	if(!q ||!ele ||  (_queue_is_full(q) == TRUE)){
		return ERROR;
	}

	*(q->rear) = (void *)ele;
	q->rear = q->data + (q->rear + 1 - q->data) % MAX_QUEUE;

	return OK;
}

void *queue_pop(Queue *q) {

	void *e = NULL;
	if ((q == NULL) || (queue_is_empty(q) == TRUE)) {
		return NULL;
	}
	e = *(q->front);
	*(q->front) = NULL;
	q->front = q->data + (q->front + 1 - q->data) % MAX_QUEUE;

	return e;
}

void *queue_getFront(const Queue *q) {

	if ((q == NULL) || (queue_is_empty(q) == TRUE)) {
		return NULL;
	}

	return *(q->front);
}

void *queue_getBack(const Queue *q) {

	void **last_elem;
	if ((q == NULL) || (queue_is_empty(q) == TRUE)) {
		return NULL;
	}

	if (q->rear == q->data) {
		last_elem = ((Queue *)q)->data + MAX_QUEUE - 1;
	} else {
		last_elem = q->rear - 1;
	}

	return *last_elem;
}

size_t queue_size(Queue *q){

	if(!q){
		return 0;
	}

	return (size_t)((q->rear - q->front + MAX_QUEUE) % MAX_QUEUE);
}

int queue_print(FILE *fp, Queue *q, p_queue_ele_print f){

	size_t i;
	size_t total_elements;
	int total =0;
	int len =0;
	void **current = NULL;

	if(!fp || !q || !f){
		return -1;
	}

	total_elements = queue_size(q);
	current = q->front;

	for(i = 0; i < total_elements; i++){
		len = f(fp, *current);
		if (len < 0) {
			return -1;
		}
		total += len;
		if (i + 1 < total_elements) {
			total += fprintf(fp, "\n");
		}
		current = q->data + (current + 1 - q->data) % MAX_QUEUE;
	}

	return total;
}