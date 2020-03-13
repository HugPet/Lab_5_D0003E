
#ifndef LIGHT_H_
#define LIGHT_H_
#include "TinyTimber.h"
#include <stdbool.h>

#define initLight(n,s) {initObject(), n, s}

struct Light_Block {
	Object Super;
	bool northIsGreen, southIsGreen;
};

typedef struct Light_Block Light;

void changeNorthStatus(Light *self, bool val);
void changeSouthStatus(Light *self, bool val);
void writeToPort(Light *self);
bool getNorthStatus(Light *self);
bool getSouthStatus(Light *self);
#endif /* GUI_H_ */