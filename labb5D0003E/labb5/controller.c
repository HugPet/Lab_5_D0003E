/*
 * controller.c
 *
 * Created: 2020-03-13 10:40:46
 *  Author: josvil-8
 */ 
#include "controller.h"


void sendToBridge(Controller *self){
	if(self->light->northIsGreen && self->north->carsInQueue > 0){
		//SYNC(self->north,removeFromQueue,NULL);
		self->north->carsInQueue--;
		self->carsOnBridge++;
		AFTER(SEC(5),self,removeFromBridge,NULL);
		self->carsPassed++;
	} else if (self->light->southIsGreen && self->south->carsInQueue > 0){
		//SYNC(self->south,removeFromQueue,NULL);
		self->south->carsInQueue--;
		self->carsOnBridge++;
		AFTER(SEC(5),self,removeFromBridge,NULL);
		self->carsPassed++;
	}
	checkPassage(self);
	checkEmpty(self);
	AFTER(SEC(1),self,sendToBridge,NULL);
	updateScreen(self);
}

void CheckLights(Controller *self){
	checkPassage(self);
	checkEmpty(self);
	updateScreen(self);
	SYNC(self->light, writeToPort, NULL);
}

void removeFromBridge(Controller *self){
	self->carsOnBridge--;
	updateScreen(self);
}

void checkPassage(Controller *self) {
	if (self->carsPassed > 2) {
		self->carsPassed = 0;
		if (self->light->northIsGreen && self->south->carsInQueue) {
			SYNC(self->light, changeNorthStatus, false);
			SYNC(self->light, changeSouthStatus, true);
			//AFTER(SEC(5), self->light, changeSouthStatus, true);
		} else if (self->light->southIsGreen && self->north->carsInQueue) {
			SYNC(self->light, changeSouthStatus, false);
			SYNC(self->light, changeNorthStatus, true);
			//AFTER(SEC(5), self->light, changeNorthStatus, true);
		}
		//SYNC(self->light,writeToPort,NULL);
		//AFTER(SEC(5), self->light,writeToPort,NULL);
	}
}

void checkEmpty(Controller *self){
	if(!self->north->carsInQueue && !self->carsOnBridge){
		SYNC(self->light, changeNorthStatus, false);
		SYNC(self->light, changeSouthStatus, true);
		//SYNC(self->light, writeToPort, NULL);

	} else if (!self->south->carsInQueue && !self->carsOnBridge){
		SYNC(self->light, changeNorthStatus, true);
		SYNC(self->light, changeSouthStatus, false);
		//SYNC(self->light, writeToPort, NULL);

	}
}


void receiveUSART(Controller *self, uint8_t data) {
	if (data & 1) {
		self->north->carsInQueue++;
	} else if ((data >> 1) & 1) {
		if (self->north->carsInQueue){
			self->north->carsInQueue--;
			self->carsPassed++;
			self->carsOnBridge++;
			AFTER(SEC(5), self, removeFromBridge, NULL);
		}
	} else if ((data >> 2) & 1) {
		self->south->carsInQueue++;
	} else if ((data >> 3) & 1) {
		if (self->south->carsInQueue){
			self->south->carsInQueue--;
			self->carsPassed++;
			self->carsOnBridge++;
			AFTER(SEC(5), self, removeFromBridge, NULL);
		}
	}
	CheckLights(self);
}

void updateScreen(Controller *self){
	//printAt(self->north->carsInQueue, 0);
	//printAt(self->carsOnBridge, 2);
	//printAt(self->south->carsInQueue, 4);
}