/*
 * LCD.h
 *
 * Created: 2020-03-06 14:27:46
 *  Author: User
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"
#include <stdbool.h>
#include "TrafficLight.h"

#define ENABLE cli()
#define DISABLE sei()
#define FOSC 8000000                       // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD -1



struct LCD_Block {
	Object Super;
};

typedef struct LCD_Block LCD;

#define initLCD() {initObject()}

void initScreen();
void update(int n1, int n2, int n3);
void printQS(int num);
void printQN(int num);
void printOnBridge(int num);
void writeChar(char ch, int pos);
int writeReg(int num, int reg, bool shift);
void printAt(int num, int pos);
void updateTrafficSignal(TrafficLight *traff);

#endif /* LCD_H_ */