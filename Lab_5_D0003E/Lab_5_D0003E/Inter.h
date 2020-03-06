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

#define initInter(n, s) {n, s}

struct Inter_Block {
	BeforeBridge *north;
	BeforeBridge *south;
};

typedef struct Inter_Block *Inter;

void onStart(Inter *self);
void onExit(Inter *self);
void addToQueue(Inter *self);
void sendToBridge(Inter *self);
void removeFromBridge(Inter *self);

#endif /* INTER_H_ */