/*
 * BeforeBridge.c
 *
 * Created: 2020-03-06 14:20:29
 *  Author: User
 */ 


void enQ(BeforeBridge *self) {
	self->carsInQ++;
}

void deQ(BeforeBridge *self) {
	self->carsInQ--;
	self->traf->bridge++;
}