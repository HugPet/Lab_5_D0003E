/*
 * Inter.h
 *
 * Created: 2020-03-06 14:21:47
 *  Author: User
 */ 


#ifndef INTER_H_
#define INTER_H_
#include "LCD.h"
#include "BeforeBridge.h"

#define initInter(n, s, l) {n, s, l, 0, true}

struct Inter_Block {
	BeforeBridge *north;
	BeforeBridge *south;
	LCD *l;
	int timer;
	bool running;
};

typedef struct Inter_Block Inter;

void onStart(Inter *self);
void onExit(Inter *self);
void addToNorthQueue(Inter *self);
void addToSouthQueue(Inter *self);
void sendToBridge(Inter *self);
void removeFromBridge(Inter *self);
void changeLight(Inter *self);
void sendDirectlyNorth(Inter *self);
void sendDirectlySouth(Inter *self);
void interSignal(Inter *self, int arg);
void checkTimer(Inter *self);
void updateAll(Inter *self, int trafficChange);

#endif /* INTER_H_ */