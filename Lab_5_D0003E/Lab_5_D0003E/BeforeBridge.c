/*
 * BeforeBridge.c
 *
 * Created: 2020-03-06 14:20:29
 *  Author: User
 */ 

#include "BeforeBridge.h"

void enQ(BeforeBridge *self) {
	self->carsInQ++;
}

void deQ(BeforeBridge *self) {
	self->carsInQ--;
	self->traf->bridge++;
	if (self->traf->n) {
		self->traf->bridge->nToS++;
	} else if (self->traf->s) {
		self->traf->bridge->sToN++;
	}
}