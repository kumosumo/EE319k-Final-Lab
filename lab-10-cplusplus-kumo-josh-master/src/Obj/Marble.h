#include <stdint.h>
#include "Level.h"


class Marble {
public:
	static int sizeConvert(int index);
	float xPos;
	float yPos;
	uint8_t size;
	float xVel;
	float yVel;
	Marble();
};

