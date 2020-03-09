/*
 * Inter.c
 *
 * Created: 2020-03-06 14:21:59
 *  Author: User
 */ 

#include "Inter.h"


void interSignal(Inter *self, int arg) {
	while ( !(UCSR0A & (1 << RXC0)) ) {}  // Wait until data is received
					                  // Read the data from the RX buffer
	//while ( !(UCSR0A & (1 << UDRE0)) ) // Wait until buffer is empty
		//UDR0 = ReceivedChar;                    // Send the data to the TX buffer
	if (UDR0 & 0) {
		addToNorthQueue(self);		
	} else if (UDR0 & 1) {
		sendToBridge(self);
	} else if (UDR0 & 2) {
		addToSouthQueue(self);
	} else if (UDR0 & 3) {
		sendToBridge(self);
	} else {
		onExit(self);
	}
}

void addToNorthQueue(Inter *self) {
	SYNC(&self->north, enQ, NULL);
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
}

void addToSouthQueue(Inter *self) {
	SYNC(&self->south, enQ, NULL);
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);

}

void onStart(Inter *self) {
	initLCD();
	self->running = true;
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
}

void onExit(Inter *self) {
	self->running = false;
	self->north->carsInQ = 0;
	self->south->carsInQ = 0;
	self->north->traf->bridge->carsOnBridge = 0;
}

void sendToBridge(Inter *self) {
	if (self->running) {
		if (self->north->traf->n && self->north->traf->bridge->sToN == 0) {
			ASYNC(&self->north, deQ, NULL);
			AFTER(SEC(5), self, removeFromBridge, NULL);
		} else if (self->south->traf->s && self->north->traf->bridge->nToS == 0){
			ASYNC(&self->south, deQ, NULL);
			AFTER(SEC(5), self, removeFromBridge, NULL);
		}
		update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
		if (self->timer >= 16 && (self->north->traf->n || self->north->traf->s)) {
			self->timer = 0;
			changeLight(self);
		} else if (self->north->traf->n || self->north->traf->s) {
			self->timer++;
		}
		
		
		if (self->north->carsInQ > 0 && self->south->carsInQ == 0 && self->north->traf->bridge->sToN) {
			SYNC(&self->north->traf, turnNorth, true);
			ASYNC(&self->north, deQ, NULL);
			AFTER(SEC(5), self, removeFromBridge, NULL);		
		} else if (self->south->carsInQ > 0 && self->north->carsInQ == 0 && self->north->traf->bridge->nToS) {
			SYNC(&self->north->traf, turnSouth, true);
			ASYNC(&self->south, deQ, NULL);
			AFTER(SEC(5), self, removeFromBridge, NULL);
		}
		update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
		AFTER(SEC(1), self, sendToBridge, NULL);
	}
}

void removeFromBridge(Inter *self) {
	if (self->running) {
		ASYNC(&self->north->traf->bridge, subCar, NULL);
		update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
	}
}

void changeLight(Inter *self) {
	if (self->running){
		ASYNC(&self->north->traf, changeActive, NULL);
		update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge, self->north->traf);
	}
}