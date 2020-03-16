/*
 * InterruptHandler.c
 *
 * Created: 2020-03-13 12:41:49
 *  Author: josvil-8
 */ 

#include "InterruptHandler.h"

#define CarEnteredQueueNorth 0x1
#define CarEnteredQueueSouth 0x2
#define CarEnteredBridgeNorth 0x3
#define CarEnteredBridgeSouth 0x4

void stickInterrupt(interruptHandler *self, int arg){
	if (((PINB >> 6) & 1) == 0) {
		ASYNC(self->control->north, addToQueue, NULL);
		} else if (((PINB >> 7) & 1) == 0) {
		ASYNC(self->control->south, addToQueue, NULL);
		} else if (((PINB >> 4) & 1) == 0) {
		if(self->control->light->southIsGreen){
			SYNC(self->control->light,changeSouthStatus,false);
			SYNC(self->control->light,changeNorthStatus,true);
			} else if (self->control->light->northIsGreen){
			SYNC(self->control->light,changeSouthStatus,true);
			SYNC(self->control->light,changeNorthStatus,false);
			} else {
			SYNC(self->control->light,changeSouthStatus,true);
			SYNC(self->control->light,changeNorthStatus,false);
		}
	}
	updateScreen(self->control);
}

void readFromPort(interruptHandler *self, int arg){
	//while ((UCSR0A & (1 << RXC0)) == 0) {};
	
	char data = UDR0;
	//SYNC(self->control, receiveUSART, data);
	//UDR0 &= 0;
	//UDR0 |= 0x63;

	//volatile int c = 0;
	//while(c < 10000) {c++;}
		
	UDR0 = data;
	//writeLong(data);
	//while ((UCSR0A & (1 << UDRE0)) == 0) {};
	//UDR0 = 255;
	/*
		uint8_t c = UDR0;
	
		UDR0 = c;*/
	//while(!(UCSR0A & (1 << RXC0))){}
	//SYNC(self->control->light,writeToPort,UDR0);
	//
	
}

void writeLong(long i) {
	int n = 0;
	while (n < 6) {		// a while loop for getting the first 6 digits of a number.
		int temp = i % 10;
		writeChar((char)temp + '0', 5-n);
		i = floor(i / 10);
		n += 1;
	}
}