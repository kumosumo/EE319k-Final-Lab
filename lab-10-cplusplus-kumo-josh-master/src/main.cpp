#include <stdio.h>
#include <stdint.h>
#include "Display/ST7735.h" 
#include "Display/Display.h"
#include "Input/Input.h"
#include "tm4c123gh6pm.h"
#include "Math/Physics.h"
#include "DAC/dac.h"
#include "Time/PLL.h"

long timeElapsed =0;


void SysTick_Init(unsigned long period){ 
  NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_RELOAD_R = period;
	NVIC_SYS_PRI3_R=(NVIC_SYS_PRI3_R&0x00FFFFFF)| 0x20000000;
	NVIC_ST_CTRL_R |= 0x07;
}



#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define PF4       (*((volatile uint32_t *)0x40025040))


extern "C" void DisableInterrupts();
extern "C" void EnableInterrupts();

void init() {
	DisableInterrupts();
	Display::initDisplay();
	DAC_Init();
	SysTick_Init(1500);
	Input::initialize();
}

int main(void) {

	init();
	
	Display::displayBlack();
	Display::titleScreen("Sand Marble", "Maze", "Josh and Kumo");
	for (int i = 0; i < 5000000; i++){}
	
	Physics p;
	EnableInterrupts();
	while(1){
	}

	return 0;
}


