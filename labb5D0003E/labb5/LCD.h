/*
* lmao
*
*/

#ifndef LCD_H_
#define LCD_H_
#include <avr/io.h>
#include <stdbool.h>

void writeChar(char ch, int pos);
int writeReg(int num, int reg, bool shift);
void printAt(int num, int post);

#endif