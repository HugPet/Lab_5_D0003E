/*
 * Lab_5_D0003E.c
 *
 * Created: 2020-03-06 13:31:03
 * Author : User
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "Inter.h"

int main(void)
{
	initScreen();
	LCD l = initLCD();
	OnBridge bridge = initOnBridge();
	TrafficLight tL = initTrafficLight(&bridge);
	BeforeBridge norr = initBeforeBridge(99, &tL);
	BeforeBridge syd = initBeforeBridge(55, &tL);
    Inter i = initInter(&norr, &syd, &l);
	onStart(&i);
	INSTALL(&i, interSignal, IRQ_USART0_RX);
	//INSTALL(&i, interSignal, IRQ_USART0_TX);
	//INSTALL(&i, interSignal, IRQ_USART0_UDRE);
	//return TINYTIMBER(&i, sendToBridge, NULL);
	return TINYTIMBER(&i, sendToBridge, NULL);


}

