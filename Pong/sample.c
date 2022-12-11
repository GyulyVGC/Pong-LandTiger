/*
In emulazione vanno impostati:
	-	attivo bouncing pulsanti
	-	attiva non idealita' potenziometro
	-	RIT, TIM0, TIM1 scalati
*/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "Pong/Pong.h" 
#include "RIT/RIT.h"
#include "adc/adc.h"
#include "button_EXINT/button.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	Pong_startScreen();
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	ADC_init();	
	BUTTON_init();												//al boot solo EINT1 e' abilitato
	init_timer(0, 500000 );								/* 20ms*/
//  init_timer(1, 1000000 );								/* 40ms*/
//	LPC_PINCON->PINSEL1 |= (1<<21);
//	LPC_PINCON->PINSEL1 &= ~(1<<20);
//	LPC_GPIO0->FIODIR |= (1<<26);	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);				
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

