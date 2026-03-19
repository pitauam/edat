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
