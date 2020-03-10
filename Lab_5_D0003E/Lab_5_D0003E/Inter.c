/*
 * Inter.c
 *
 * Created: 2020-03-06 14:21:59
 *  Author: User
 */ 

#include "Inter.h"


void updateAll(Inter *self, int trafficChange) {
	if (trafficChange == 1) {
		updateTrafficSignal(self->north->traf);
	}
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge);
}

void interSignal(Inter *self, int arg) {
	if (self->running) {
		while ( !(UCSR0A & (1 << RXC0)) ) {}  // Wait until data is received
										  // Read the data from the RX buffer
		//while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty
			//UDR0 = ReceivedChar;                    // Send the data to the TX buffer
		if (UDR0 == 0x6E) {
			addToNorthQueue(self);	
		} else if (UDR0 & 1) {
			sendDirectlyNorth(self);
		} else if (UDR0 == 0x73) {
			addToSouthQueue(self);
		} else if (UDR0 & 3) {
			sendDirectlySouth(self);
		} else {
			onExit(self);
		}
		updateAll(self, 0);
	}
}


void sendDirectlyNorth(Inter *self) {
	self->north->traf->bridge++;
	self->north->traf->bridge->nToS++;
	checkTimer(self);
	AFTER(SEC(5), self, removeFromBridge, NULL);
}

void sendDirectlySouth(Inter *self) {
	self->north->traf->bridge++;
	self->north->traf->bridge->sToN++;
	checkTimer(self);
	AFTER(SEC(5), self, removeFromBridge, NULL);
}

void addToNorthQueue(Inter *self) {
	SYNC(&self->north, enQ, NULL);
	updateAll(self, 0);
}

void addToSouthQueue(Inter *self) {
	SYNC(&self->south, enQ, NULL);
	updateAll(self, 0);
}

void onStart(Inter *self) {
	//initLCD();
	sendToBridge(self);
	self->running = true;
	addToNorthQueue(self);
	updateAll(self, 0);
}

void onExit(Inter *self) {
	self->running = false;
	self->north->carsInQ = 0;
	self->south->carsInQ = 0;
	self->north->traf->bridge->carsOnBridge = 0;
	updateAll(self, 0);
}

void sendToBridge(Inter *self) {
	if (self->north->traf->n) {
		ASYNC(&self->north, deQ, NULL);
		AFTER(SEC(5), self, removeFromBridge, NULL);
	} else if (self->south->traf->s){
		ASYNC(&self->south, deQ, NULL);
		AFTER(SEC(5), self, removeFromBridge, NULL);
	}

	if (self->north->carsInQ > 0 && (self->south->carsInQ == 0 || !self->north->traf->s) && self->north->traf->bridge->sToN == 0) {
		SYNC(&self->north->traf, turnNorth, true);
		SYNC(&self->north->traf, turnSouth, false);
		updateAll(self, 1);
		self->timer = 0;
	} else if (self->south->carsInQ > 0 && (self->north->carsInQ == 0 || !self->north->traf->n) && self->north->traf->bridge->nToS == 0) {
		SYNC(&self->north->traf, turnSouth, true);
		SYNC(&self->north->traf, turnNorth, false);
		updateAll(self, 1);
		self->timer = 0;
	}
	updateAll(self, 0);
	AFTER(SEC(1), self, sendToBridge, NULL);
}

void checkTimer(Inter *self) {
	if (self->timer >= 16) {
		self->timer = 0;
		if (self->north->traf->n) {
			SYNC(&self->north->traf, turnNorth, false);
			AFTER(SEC(5), &self->north->traf, turnSouth, true);
		} else if (self->north->traf->s) {
			SYNC(&self->north->traf, turnSouth, false);
			AFTER(SEC(5), &self->north->traf, turnNorth, true);
		}
		AFTER(SEC(5), self, updateAll, 1);
	} else if (self->north->traf->n || self->north->traf->s) {
		self->timer++;
	}
	updateAll(self, 0);
}

void removeFromBridge(Inter *self) {
	if (self->running) {
		ASYNC(&self->north->traf->bridge, subCar, NULL);
		updateAll(self, 0);
	}
}

void changeLight(Inter *self) {
	if (self->running){
		ASYNC(&self->north->traf, changeActive, NULL);
		updateAll(self, 1);
	}
}