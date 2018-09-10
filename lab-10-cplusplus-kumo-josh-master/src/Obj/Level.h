#include <stdint.h>

struct Coord {
	uint8_t x;
	uint8_t y;
};


struct Line {
	Coord p1;
	Coord p2;
	
	uint8_t dir;
};

class Level {
private:
	int levelNumber;
	int generateWalls();
public:
	static void copyMaze(uint8_t dest[40][32], const uint8_t src[40][32]); 
	uint8_t maze[40][32];
	uint8_t testmaze[5][5];
	Level(int levelNumber);
	Line walls[100];
	uint8_t wallCount;

};
