#include "Queue.h"

void removeFromQueue(Queue *self){
	self->carsInQueue--;
}

void addToQueue(Queue *self){
	self->carsInQueue++;
}