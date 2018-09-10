#include "../Obj/Marble.h"

class Physics {
private:
	static double findDistanceChange(double accel, double vel, double elapsedTime);
	static double findVelocityChange(double accel, double elapsedTime);
	static double findAcceleration(double deg);
	static int toPixels(double dis);
	static void checkCollision(Marble& m, int* xAccel, int* yAccel, Line walls[], uint8_t wallCount);
	static void displayMarble();
  static int convertSlide(int in);
	static void moveMarbleHandler();
	static void copyWalls(Line dest[], Line src[], int wallCount);
	static void loadNextLevel();
	static void youWin();
public:
	static Marble m;
	static Line walls[];
	static int wallCount;
	static void increaseMarbleSize();
	static void decreaseMarbleSize();
	Physics();
};
