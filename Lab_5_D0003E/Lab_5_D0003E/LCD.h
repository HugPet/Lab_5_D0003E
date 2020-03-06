/*
 * LCD.h
 *
 * Created: 2020-03-06 14:27:46
 *  Author: User
 */ 


#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>

struct LCD_Block {

};

typedef struct LCD_Block *LCD;

void initLCD();
void update(int n1, int n2, int n3);
void printQS(int num);
void printQN(int num);
void printOnBridge(int num);
void writeChar(char ch, int pos);
int writeReg(int num, int reg, bool shift);
void printAt(int num, int pos);
#endif /* LCD_H_ */