/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			GLCD.h
** Descriptions:		Has been tested SSD1289、ILI9320、R61505U、SSD1298、ST7781、SPFD5408B、ILI9325、ILI9328、
**						HX8346A、HX8347A
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-3-10
** Version:				1.3
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/

#include "LPC17xx.h"

void Pong_startScreen(void);
void Pong_drawScore(void);
void Pong_drawScore_P2(void);
void Pong_drawBestScore(void);
void Pong_eraseBestScore(void);
void Pong_drawBall(void);
void Pong_updateBall(void);
void Pong_eraseBall(void);
void Pong_drawPaddle(uint16_t xPaddle);
void Pong_drawPaddle_P2(void);
void Pong_erasePaddle(uint16_t xPaddle);
void Pong_erasePaddle_P2(void);
void Pong_initPaddle_P2(void);
void Pong_lose(void);
void Pong_win(void);
//void Pong_lowNote(void);
//void Pong_highNote(void); 


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
