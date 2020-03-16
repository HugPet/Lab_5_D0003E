/*
 * Lab_5_D0003E.c
 *
 * Created: 2020-03-06 13:31:03
 * Author : User
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "Queue.h"
#include "Light.h"
#include "InterruptHandler.h"
#define FOSC 8000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC/(16*BAUD))-1)

void initScreen();

int main(void)
{
	initScreen();
	Light light = initLight(true,false);
	Queue northQ = initQueue(0);
	Queue southQ = initQueue(0);
	Controller controller = initController(&northQ,&southQ, &light);
	interruptHandler Interrupts = initInterruptHandler(&controller);
	INSTALL(&Interrupts, readFromPort, IRQ_USART0_RX);
	INSTALL(&Interrupts, stickInterrupt, IRQ_PCINT1);
	return TINYTIMBER(&controller, sendToBridge, NULL);
}

void initScreen() {
	LCDCRB = (1<<LCDMUX1)|(1<<LCDMUX0)|(1<<LCDPM2)|(1<<LCDPM1)|(1<<LCDPM2);
	LCDFRR = (0<<LCDPS2)|(0<<LCDPS1)|(0<<LCDPS0)|(1<<LCDCD2)|(1<<LCDCD1)|(1<<LCDCD0);
	LCDCCR = (0<<LCDDC2)|(0<<LCDDC1)|(0<<LCDDC0)|(1<<LCDCC3)|(1<<LCDCC2)|(1<<LCDCC1)|(1<<LCDCC0);
	LCDCRA = (1<<LCDEN)|(1<<LCDAB)|(0<<LCDIE)|(0<<LCDBL);
	
	TCCR1B = (0<<WGM13)|(1<<WGM12)|(0<<WGM11)|(0<<WGM10)|(1<<CS12)|(0<<CS11)|(1<<CS10);
	
	UCSR0B = (1 << RXEN0)|(1<<TXEN0)|(1 << RXCIE0);
	UCSR0C = (0 << USBS0)|(1 << UCSZ01) | (1 << UCSZ00);   // Set frame: 8data, 1 stp USBS0 = stop bit
	UBRR0H = MYUBRR >> 8;
	UBRR0L = MYUBRR;
	
	PRR = (0<<2);

	
	PCMSK0 = 0x0c;
	PCMSK1 = 0xd0;
	EIFR = 0xc0;
	EIMSK = 0xc0;
	PORTB = (1 << PB7)|(1 << PB6)|(1 << PB4);
	PORTE = (1 << PE3)|(1 << PE2);
	DDRB = (0<<DDB7)|(0<<DDB6);
	MCUCR = (0 << PUD);
	
}