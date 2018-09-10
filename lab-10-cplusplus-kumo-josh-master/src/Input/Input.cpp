#include "Input.h"
#include "../tm4c123gh6pm.h"
#include "../Time/Timer0.h"
#include "../Math/Physics.h"

extern "C" void GPIOB_Handler();
extern "C" void EnableInterrupts();
extern "C" void DisableInterrupts();

int xSlide = 0;
int ySlide = 0;

void Set(){
	ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
    // if you have an A0-A3 revision number, you need to add an 8 usec wait here
  ySlide = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion

	ADC1_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC1_RIS_R&0x08)==0){};   // 2) wait for conversion done
    // if you have an A0-A3 revision number, you need to add an 8 usec wait here
  xSlide = ADC1_SSFIFO3_R&0xFFF;   // 3) read result
  ADC1_ISC_R = 0x0008;
}

void Input::initialize() {
	initButtons();
	EnableInterrupts();
	initSlidepot();
}

void Input::initButtons() {
	SYSCTL_RCGCGPIO_R |= 0x02;
	GPIO_PORTB_DIR_R &= ~0x30;    // (c) make sPB0-1
  GPIO_PORTB_AFSEL_R &= ~0x30;  //     disable alt funct on PB0-1
  GPIO_PORTB_DEN_R |= 0x30;     //     enable digital I/O on PB0-1
  GPIO_PORTB_PCTL_R &= ~0x000F0000; //  configure PF4 as GPIO
  GPIO_PORTB_AMSEL_R &= ~0x30;  //    disable analog functionality on PB0-1
  //GPIO_PORTB_PDR_R |= 0x0C;     //     enable weak pull-up on PB0-1
  GPIO_PORTB_IS_R &= ~0x30;     // (d) PB0-1 is edge-sensitive
  GPIO_PORTB_IBE_R &= ~0x30;    //     PB0-1 is not both edges
  GPIO_PORTB_IEV_R |= 0x30;    //     PB0-1 falling edge event

  GPIO_PORTB_ICR_R = 0x30;      // (e) clear flag4

  GPIO_PORTB_IM_R |= 0x30;      // (f) arm interrupt on PB0-2
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF00FF)|0x0000A000; // (g) priority 5

  NVIC_EN0_R = 0x00000002;      // (h) enable interrupt 30 in NVIC
}

void Input::initSlidepot() {
	SYSCTL_RCGCGPIO_R |= 0x0C;
	GPIO_PORTD_DIR_R &= ~0x0C;  // 3.5) make PD2 input
		GPIO_PORTD_AFSEL_R |= 0x0C; // 4.5) enable alternate function on PD2
		GPIO_PORTD_DEN_R &= ~0x0C;  // 5.5) disable digital I/O on PD2
		GPIO_PORTD_AMSEL_R |= 0x0C; // 6.5) enable analog functionality on PD2
	
	int delay;
	SYSCTL_RCGCADC_R |= 0x0003;   // 7) activate ADC0 
//  while((SYSCTL_PRADC_R&0x0001) != 0x0001){};   // good code, but not yet implemented in simulator
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;
  ADC0_PC_R &= ~0xF;              // 9) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;          // 10) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0008;        // 11) disable sample sequencer 3
  ADC0_EMUX_R |= 0xF000;          // 12) seq3 is continuous trigger
  ADC0_SSMUX3_R &= ~0x000F;       // 13) clear SS3 field
  ADC0_SSMUX3_R += 5;    //     set channel
  ADC0_SSCTL3_R = 0x0006;         // 14) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;           // 15) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;         // 16) enable sample sequencer 3

	ADC1_PC_R &= ~0xF;              // 9) clear max sample rate field
  ADC1_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC1_SSPRI_R = 0x3210;          // 10) Sequencer 3 is lowest priority
  ADC1_ACTSS_R &= ~0x0008;        // 11) disable sample sequencer 3
  ADC1_EMUX_R |= 0xF000;          // 12) seq3 is continuous trigger
  ADC1_SSMUX3_R &= ~0x000F;       // 13) clear SS3 field
  ADC1_SSMUX3_R += 4;    //     set channel
  ADC1_SSCTL3_R = 0x0006;         // 14) no TS0 D0, yes IE0 END0
  ADC1_IM_R &= ~0x0008;           // 15) disable SS3 interrupts
  ADC1_ACTSS_R |= 0x0008;
	
	Timer0_Init(Set, 3200000);
}

void GPIOB_Handler() {
	GPIO_PORTB_ICR_R = 0x30;
	if (GPIO_PORTB_DATA_R & 0x10) {
		Physics::decreaseMarbleSize();
	}
	if (GPIO_PORTB_DATA_R & 0x20) {
		Physics::increaseMarbleSize();
	}
}
