#include "Time.h"
#include <stdlib.h>
#include <stdint.h>
#include "../Display/ST7735.h"
#include "Timer1.h"
#include "PLL.h"


int timeCount=0;
double Time::elapsedTime=0;

double Time::getTime(){
	return elapsedTime;
}

void Time::reset(){
	elapsedTime=0.00;
}

void Time::incrementTime(){
	elapsedTime += .001;
}

void Time::init() {
	PLL_Init(Bus80MHz);
	Timer1_Init(Time::incrementTime, 80000);
}
