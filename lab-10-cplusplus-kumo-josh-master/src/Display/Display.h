//
// Created by jspspike on 4/24/18.
//


#ifndef LAB_10_CPLUSPLUS_KUMO_JOSH_DISPLAY_H
#define LAB_10_CPLUSPLUS_KUMO_JOSH_DISPLAY_H
#include <stdint.h>



class Display {
public:
	//initialize display
    static void initDisplay();
		static void test(int in);
    //right now, this just draws lines
    static void drawMaze(const uint8_t maze[40][32]);
   	//Title Screen
   	static void titleScreen(char* title1, char* title2, char* title3);		
		static void displayTest(int test);
		static void setMarble(uint8_t x, uint8_t y, uint8_t size);
		static void clearMarble(uint8_t x, uint8_t y, uint8_t size);
		static void drawMarble(uint8_t x, uint8_t y, uint8_t size);
		static void displayBlack();
		static void displayWhite();
		static void displayBlue();
};


#endif //LAB_10_CPLUSPLUS_KUMO_JOSH_DISPLAY_H
