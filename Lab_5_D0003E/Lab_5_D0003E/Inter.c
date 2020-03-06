/*
 * Inter.c
 *
 * Created: 2020-03-06 14:21:59
 *  Author: User
 */ 

void addToQueue(Inter *self) {
	//ASYNC(&self->north, enQ, NULL);
}

void onStart(Inter *self) {
	initLCD();
}

void onExit(Inter *self) {
	
}

void sendToBridge(Inter *self) {
	if (self->north->traf->n) {
		ASYNC(&self->north, deQ, NULL);
	} else if (self->south->traf->s){
		ASYNC(&self->south, deQ, NULL);
	} else {
		return;
	}
	AFTER(SEC(5), self, removeFromBridge, NULL);
	AFTER(SEC(1), self, sendToBridge, NULL);
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge);
}

void removeFromBridge(Inter *self) {
	ASYNC(&self->north->traf->bridge, subCar, NULL);
	update(self->north->carsInQ, self->south->carsInQ, self->north->traf->bridge->carsOnBridge);

}