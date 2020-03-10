/*
 * BeforeBridge.h
 *
 * Created: 2020-03-06 14:20:49
 *  Author: User
 */ 


#ifndef BEFOREBRIDGE_H_
#define BEFOREBRIDGE_H_
#include "TinyTimber.h"
#include "TrafficLight.h"

#define initBeforeBridge(t) {initObject(), 5, t}

struct BeforeBridge_Block {
	Object Super;
	int carsInQ;
	TrafficLight *traf;
};

typedef struct BeforeBridge_Block BeforeBridge;

void enQ(BeforeBridge *self);
void deQ(BeforeBridge *self);

#endif /* BEFOREBRIDGE_H_ */