/*
 * controller.h
 *
 * Created: 2020-03-13 10:40:57
 *  Author: josvil-8
 */ 
#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "TinyTimber.h"
#include <avr/io.h>
#include "Queue.h"
#include "LCD.h"

//#include "sendToBridge.h"

#define initController(n,s,l) {initObject(), n,s,0,l, 0}


struct controller_Block {
	Object Super;
	Queue *north, *south;
	int carsOnBridge;
	Light *light;
	int carsPassed;
};

typedef struct controller_Block Controller;

void sendToBridge(Controller *self);
void updateScreen(Controller *self);
void removeFromBridge(Controller *self);
void checkPassage(Controller *self);
void checkEmpty(Controller *self);
void receiveUSART(Controller *self, uint8_t data);
void CheckLights(Controller *self);
#endif