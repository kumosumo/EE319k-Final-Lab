#include "Physics.h"
#include <math.h>
#include "../Display/Display.h"
#include "../Time/Timer1.h"
#include "../Time/Timer2.h"
#include "../Input/Input.h"

#define PI 3.14159265

extern "C" void DisableInterrupts();
extern "C" void EnableInterrupts();

Physics::Physics(){
	//Time::init();
	loadNextLevel();
	Display::drawMarble(m.xPos, m.yPos, m.size);
	Timer1_Init(Physics::moveMarbleHandler, 1500000);
	Timer2_Init(Physics::displayMarble, 1300000);
	//Time::reset();
}

int Physics::wallCount = 0;
Line Physics::walls[100] = {};
Marble Physics::m;

int Physics::convertSlide(int in) {
	in *= 4;
	in /= 273;
	return in - 30;
}

double Physics::findDistanceChange(double accel, double vel, double elapsedTime) {
	float sum = .5 * accel * elapsedTime * elapsedTime;
	sum += vel * elapsedTime;
	return sum;
}

double Physics::findVelocityChange(double accel, double elapsedTime) {
	return accel * elapsedTime;
}

double Physics::findAcceleration(double deg) {
	return 9.81 * sin(deg * PI / 180.0);
}

int Physics::toPixels(double dis) {
	dis /= 10.0;
	return dis;
}

void Physics::checkCollision(Marble& m, int* xAccel, int* yAccel, Line walls[], uint8_t wallCount) {
	
	int mxPos = toPixels(m.xPos);
	int myPos = toPixels(m.yPos);
	
	for (int i = 0; i < wallCount; i++) {
		switch(walls[i].dir) {
			case 1:
				if (mxPos > walls[i].p1.x && mxPos < walls[i].p2.x && myPos - Marble::sizeConvert(m.size) - 1 <= walls[i].p1.y) {
					if (myPos + Marble::sizeConvert(m.size) > walls[i].p1.y) {
						if (m.yVel < 0 || *yAccel < 0) {
							m.yVel = 0;
							*yAccel = 0;
						}
					}
				}
				break;
			case 2:
				if (mxPos > walls[i].p1.x && mxPos < walls[i].p2.x && myPos + Marble::sizeConvert(m.size) + 2 >= walls[i].p1.y) {
					if (myPos - Marble::sizeConvert(m.size) < walls[i].p1.y) {
						if (m.yVel > 0 || *yAccel > 0) {
							m.yVel = 0;
							*yAccel = 0;
						}
					}
				}
				break;
			case 3:
				if (myPos > walls[i].p1.y && myPos < walls[i].p2.y && mxPos - Marble::sizeConvert(m.size) - 2 <= walls[i].p1.x) {
					if (mxPos + Marble::sizeConvert(m.size) > walls[i].p1.x) {
						if (m.xVel < 0 || *xAccel < 0) {
							m.xVel = 0;
							*xAccel = 0;
						}
					}
				}
				break;
			case 4:
				if (myPos > walls[i].p1.y && myPos < walls[i].p2.y && mxPos + Marble::sizeConvert(m.size) + 2 >= walls[i].p1.x) {
					if (mxPos - Marble::sizeConvert(m.size) < walls[i].p1.x) {
						if (m.xVel > 0 || *xAccel > 0) {
							m.xVel = 0;
							*xAccel = 0;
						}
					}
				}
		}
	}
	
	if (mxPos - Marble::sizeConvert(m.size) < 0 && *xAccel < 0) {
		m.xVel = 0;
		*xAccel = 0;
	} else if (mxPos + Marble::sizeConvert(m.size) > 128 && *xAccel > 0) {
		*xAccel = 0;
	}
	
	if (myPos - Marble::sizeConvert(m.size) < 0 && *yAccel < 0) {
		m.yVel = 0;
		*yAccel = 0;
	} else if (myPos + Marble::sizeConvert(m.size) > 160 && *yAccel > 0) {
		*yAccel = 0;
	}
}

int f = 0;

struct MCopy {
	int x;
	int y;
	
	int size;
};

MCopy mcopy = {0, 0, 2};

void Physics::displayMarble() {
	Display::drawMarble(mcopy.x, mcopy.y, mcopy.size);
}

void Physics::decreaseMarbleSize() {
	if (mcopy.size < 3)
		mcopy.size++;
}

void Physics::increaseMarbleSize() {
	if (mcopy.size > 1)
		mcopy.size--;
}

void Physics::copyWalls(Line dest[], Line src[], int wallCount) {
	for (int i = 0; i < wallCount; i++) {
		dest[i] = src[i];
	}
}

int currLevel = 0;

void Physics::youWin() {
	Display::displayBlack();
	Display::titleScreen("Congradulations!", "You win!", "");
	while(true){}
}

void Physics::loadNextLevel() {
	DisableInterrupts();
	m.xPos = 120.0;
	m.yPos = 80.0;
	if (currLevel > 2)
		youWin();
	Level l(currLevel);
	copyWalls(Physics::walls, l.walls, l.wallCount);
	Physics::wallCount = l.wallCount;
	currLevel++;
	EnableInterrupts();
}


void Physics::moveMarbleHandler() {
	
	if (toPixels(m.xPos) + Marble::sizeConvert(m.size) > 96 && toPixels(m.xPos) - Marble::sizeConvert(m.size) < 104 && toPixels(m.yPos) + Marble::sizeConvert(m.size) > 156)
		loadNextLevel();
	
	m.size = mcopy.size;
	
	int xDeg = convertSlide(xSlide);
	int yDeg = convertSlide(ySlide);
	
	int xAccel = xDeg;//findAcceleration(xDeg);
	int yAccel = yDeg;//findAcceleration(yDeg);
	
	checkCollision(m, &xAccel, &yAccel, walls, wallCount);
	//double xDiff = findDistanceChange(xAccel, m.xVel, elapsedTime);
	//double yDiff = findDistanceChange(yAccel, m.yVel, elapsedTime);
	
	//m.xVel += findVelocityChange(xAccel, elapsedTime);
	//m.yVel += findVelocityChange(yAccel, elapsedTime);
	
	m.xPos += xAccel;
	m.yPos += yAccel;
	
	mcopy.x = toPixels(m.xPos);
	mcopy.y = toPixels(m.yPos);
}
