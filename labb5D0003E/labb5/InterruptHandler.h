/*
 * InterruptHandler.h
 *
 * Created: 2020-03-13 12:42:04
 *  Author: josvil-8
 */ 
#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_
#include "controller.h"
#include <avr/io.h>
#include <math.h>


#define initInterruptHandler(c) {initObject(), c}

struct interruptHandler_Block {
	Object Super;
	Controller *control;
};

typedef struct interruptHandler_Block interruptHandler;
void writeLong(long i);
void stickInterrupt(interruptHandler *self, int arg);
void readFromPort(interruptHandler *self, int arg);
#endif