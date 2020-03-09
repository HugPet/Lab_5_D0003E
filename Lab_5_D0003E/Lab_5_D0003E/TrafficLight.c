/*
 * TrafficLight.c
 *
 * Created: 2020-03-06 14:19:35
 *  Author: User
 */ 

#include "TrafficLight.h"

void turnNorth(TrafficLight *self, bool val) {
	self->n = val;
	self->s = !val;
}

void turnSouth(TrafficLight *self, bool val) {
	self->s = val;
	self->n = !val;
}

void changeActive(TrafficLight *self) {
	self->s = !self->s;
	self->n = !self->n;
}