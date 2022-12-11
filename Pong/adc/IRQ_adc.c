/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../led/led.h"
#include "../Pong/Pong.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

int count=0;
unsigned short AD_current=0x800;  ////////////800 
unsigned short AD_last = 0x800;     /* Last converted value               */

void ADC_IRQHandler(void) {
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(AD_current < AD_last-130 || AD_current > AD_last+130){
		count++;
		if(count>3){
		Pong_erasePaddle(AD_last*240/0xFFF);	
		Pong_drawPaddle(AD_current*240/0xFFF);	
		count=0;
		AD_last = AD_current;
		}
		
  }	
}
