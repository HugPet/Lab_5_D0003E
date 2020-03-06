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
	OnBridge bridge = initOnBridge();
	TrafficLight tL = initTrafficLight(b);
	BeforeBridge norr = initBeforeBridge(tL);
	BeforeBridge syd = initBeforeBridge(tL);
    Inter i = initInter(norr, syd);
	return TINYTIMBER(&i, onStart, NULL)
}
