/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../Pong/Pong.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int down1=0,down2=0,down0=0,pausa;
extern uint8_t key;
extern uint16_t x,y,xPaddle;
extern int tg1,tg2;												//tangente dell'angolo
extern int segnoX, segnoY, lose;	
extern unsigned short AD_current;
//extern int soundCounter;	

void RIT_IRQHandler (void)
{			
	
	/* ADC management */
	if(!pausa)
		ADC_start_conversion();	
	
	//buttons management
	
		if(key==1){
		down1++;
		reset_RIT();
		switch(down1){
			case 1:
				NVIC_EnableIRQ(EINT2_IRQn);
				pausa=0;
				x=230;
			  y=160;
			  tg1=1;
				tg2=1;
				segnoX=-1;
				segnoY=+1;
				//Pong_eraseBestScore();
				GUI_Text(100, 160, (uint8_t *) "PONG", Black, Black);
				GUI_Text(25, 300, (uint8_t *) "Premi KEY1 per iniziare", Black, Black); //pulisco scritta
				Pong_drawPaddle(AD_current*240/0xFFF);
				enable_timer(0);
				//enable_timer(1);
				break;
			default:
				break;
		}
	}
	if(key==1 && (LPC_GPIO2->FIOPIN & (1<<11)) != 0){
		down1=0;
		key=4;
		disable_RIT();
		reset_RIT();
		//NVIC_EnableIRQ(EINT1_IRQn); 
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
	
	if(key==2){
	down2++;
	reset_RIT();
		switch(down2){
			case 1:
					pausa?(pausa=0):(pausa=1);
					if(pausa){
						disable_timer(0);
						//Pong_drawBestScore();
						GUI_Text(25, 300, (uint8_t *) "Premi KEY2 per riprendere", Blue2, Yellow);
					}
					else{
						//Pong_eraseBestScore();
						GUI_Text(25, 300, (uint8_t *) "Premi KEY2 per riprendere", Black, Black);
						enable_timer(0);
					}
				break;
			default:
				break;
		}
	}
  if(key==2 && (LPC_GPIO2->FIOPIN & (1<<12)) != 0){
		down2=0;
		key=4;
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT2_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
	
 if(key==0){
	down0++;
	reset_RIT();
		switch(down0){
			case 1:
				GUI_TextReverse(150, 120, (uint8_t *) "HAI PERSO", Black, Black);
				GUI_Text(25, 160, (uint8_t *) "Premi INT0 per resettare", Black, Black); //pulisco
				GUI_Text(80, 200, (uint8_t *) "HAI PERSO", Black, Black);
				GUI_Text(100, 160, (uint8_t *) "PONG", Blue2, Yellow);
				Pong_drawScore();
				Pong_drawScore_P2();
				GUI_Text(25, 300, (uint8_t *) "Premi KEY1 per iniziare", Blue2, Yellow); //scritta
			  NVIC_EnableIRQ(EINT1_IRQn);
				break;
			default:
				break;
		}
	}
  if(key==0 && (LPC_GPIO2->FIOPIN & (1<<10)) != 0){
		down0=0;
		key=4;
		disable_RIT();
		reset_RIT();
		//NVIC_EnableIRQ(EINT0_IRQn);
		LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
	}
	
//	if(soundCounter){
//		soundCounter++;
//		if(soundCounter==3){
//			disable_timer(1);
//			reset_timer(1);
//			soundCounter=0;
//		}
//	}

	disable_RIT();
	reset_RIT();
	enable_RIT();
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
