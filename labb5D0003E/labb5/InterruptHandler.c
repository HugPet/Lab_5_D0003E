/*
 * InterruptHandler.c
 *
 * Created: 2020-03-13 12:41:49
 *  Author: josvil-8
 */ 

#include "InterruptHandler.h"

void stickInterrupt(interruptHandler *self, int arg){
	if (((PINB >> 6) & 1) == 0) {
		ASYNC(self->control->north, addToQueue, NULL);
		} else if (((PINB >> 7) & 1) == 0) {
		ASYNC(self->control->south, addToQueue, NULL);
		} else if (((PINB >> 4) & 1) == 0) {
		if(self->control->light->southIsGreen){
			SYNC(self->control->light,changeSouthStatus,false);
			SYNC(self->control->light,changeNorthStatus,true);
			} else if (self->control->light->northIsGreen){
			SYNC(self->control->light,changeSouthStatus,true);
			SYNC(self->control->light,changeNorthStatus,false);
			} else {
			SYNC(self->control->light,changeSouthStatus,true);
			SYNC(self->control->light,changeNorthStatus,false);
		}
	}
	updateScreen(self->control);
}

void readFromPort(interruptHandler *self, int arg){}