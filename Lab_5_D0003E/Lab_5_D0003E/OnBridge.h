/*
 * OnBridge.h
 *
 * Created: 2020-03-06 14:20:06
 *  Author: User
 */ 


#ifndef ONBRIDGE_H_
#define ONBRIDGE_H_
#include "TinyTimber.h"
#define NULL 0

#define initOnBridge() {initObject(), 0}

struct OnBridge_Block {
	Object Super;
	int carsOnBridge;
};

typedef struct OnBridge_Block *OnBridge;

void addCar(OnBridge *self);
void subCar(OnBridge *self);



#endif /* ONBRIDGE_H_ */