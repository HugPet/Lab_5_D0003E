#include "Light.h"
#include <avr/io.h>

bool getSouthStatus(Light *self){
	return self->southIsGreen;
}

bool getNorthStatus(Light *self){
	return self->northIsGreen;
}

void changeNorthStatus(Light *self, bool val) {
	self->northIsGreen = val;
}
void changeSouthStatus(Light *self, bool val) {
	self->southIsGreen = val;
}

void writeToPort(Light *self, uint8_t argument){
	UDR0 = argument;// (self->northIsGreen << 4)|(!(self->northIsGreen) << 5)|(self->southIsGreen << 6)|(!(self->southIsGreen) << 7);
}
