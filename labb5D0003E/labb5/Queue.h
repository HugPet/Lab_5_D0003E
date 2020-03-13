
#ifndef QUEUE_H_
#define QUEUE_H_
#include "TinyTimber.h"
#include "Light.h"
#define initQueue(q) {initObject(), q}

struct Queue_Block {
	Object Super;
	int carsInQueue;
};

typedef struct Queue_Block Queue;

void removeFromQueue(Queue *self);
void addToQueue(Queue *self);

#endif