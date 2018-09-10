#include "Marble.h"

Marble::Marble() {
	this->xVel = 0;
	this->yVel = 0;
	this->size = 2;
	this->xPos = 120.0;
	this->yPos = 80.0;
}

int Marble::sizeConvert(int index) {
	return (18 - index * 2) / 2;
}
