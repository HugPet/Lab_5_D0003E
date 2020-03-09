/*
 * OnBridge.c
 *
 * Created: 2020-03-06 14:20:18
 *  Author: User
 */ 

#include "OnBridge.h"


void addCar(OnBridge *self) {
	self->carsOnBridge++;
}

void subCar(OnBridge *self) {
	self->carsOnBridge--;
	if (self->nToS > 0) {
		self->nToS--;
	} else if (self->sToN > 0) {
		self->sToN--;
	}
}