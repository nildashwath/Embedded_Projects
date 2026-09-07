#include "stm32f4xx.h"


#define SYSTICK_LOAD_VAL		16000
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)
#define SYSTICK_CTRL_TICKINT	(1U<<1)

#define ONE_SEC_LOAD			16000000



void systickDelayMs(int delay){
	/*******************configure the systick*******************/
	//Reload with number of clocks per millisecond
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//clear systick current value register
	SysTick->VAL = 0;
	//Enable systick and select internal clk src
	SysTick-> CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i = 0; i < delay ; i++){
		//wait until the countflag is set

		while((SysTick->CTRL & CTRL_COUNTFLAG)==0){}
	}

	SysTick->CTRL = 0;
}

void systick_1hz_interrupt(void){
	//load the systick values
	SysTick->LOAD = ONE_SEC_LOAD - 1; //here we count from 0 that's why -1

	//clear systick current value register
	SysTick->VAL = 0;

	//Enable systick and select internal clk src
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	//Enable the Systick interrupt
	SysTick->CTRL |= SYSTICK_CTRL_TICKINT;

}
//We don't need to enable systick in NVIC.
