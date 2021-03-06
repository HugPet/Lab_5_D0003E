/*
 * TrafficLight.h
 *
 * Created: 2020-03-06 14:19:49
 *  Author: User
 */ 


#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_
#include <stdbool.h>
#include <stdint.h>
#include "TinyTimber.h"
#include "OnBridge.h"
#define initTrafficLight(o) {initObject(), true, false, o}

struct TrafficLight_block {
	Object Super;
	bool s, n;
	OnBridge *bridge;
};

typedef struct TrafficLight_block TrafficLight;

void turnSouth(TrafficLight *self, bool val);
void turnNorth(TrafficLight *self, bool val);
void changeActive(TrafficLight *self);

#endif /* TRAFFICLIGHT_H_ */