/*
 * OnBridge.c
 *
 * Created: 2020-03-06 14:20:18
 *  Author: User
 */ 

void addCar(OnBridge *self) {
	self->carsOnBridge++;
}

void subCar(OnBridge *self) {
	self->carsOnBridge--;
}