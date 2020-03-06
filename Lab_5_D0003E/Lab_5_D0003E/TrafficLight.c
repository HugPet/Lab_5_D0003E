/*
 * TrafficLight.c
 *
 * Created: 2020-03-06 14:19:35
 *  Author: User
 */ 

void changeNorth(TrafficLight *self, bool val) {
	self->n = val;
}

void changeSouth(TrafficLight *self, bool val) {
	self->s = val;
}