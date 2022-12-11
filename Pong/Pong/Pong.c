
/* Includes ------------------------------------------------------------------*/
#include "../GLCD/GLCD.h" 
#include "../GLCD/AsciiLib.h"
#include "stdio.h"
#include "stdlib.h"
#include "../timer/timer.h"


int i,j,lose=0;
//char* s;
int /*bestScore=100,*/score=0, score_P2=0;												
uint16_t xPaddle, xPaddle_P2=140;									//posizione centrale corrente del paddle
int direzione_P2=-1;	       											  //se 1 allora muove verso dx, se -1 allora muove verso sx
uint16_t x,y;																			//posizione centrale corrente della palla
int tg1,tg2;																					
int segnoX, segnoY;																//+1 oppue -1, variazione crescente o decrescente delle coordinate
//int soundCounter=0;																//usato dal RIT per stoppare il suono

//void Pong_drawBestScore(){
//	char charScore[5];
//	sprintf(charScore,"%d",bestScore);
//	GUI_Text(50,10,(uint8_t*)"Miglior punteggio: ", White, Black);
//	GUI_Text(200,10,(uint8_t *)charScore, White, Black);
//}

//void Pong_eraseBestScore(){
//	char charScore[5];
//	sprintf(charScore,"%d",bestScore);
//	GUI_Text(50,10,(uint8_t*)"Miglior punteggio: ", Black, Black);
//	GUI_Text(200,10,(uint8_t *)charScore, Black, Black);
//}

void Pong_drawScore(){
	char charScore[5];
	sprintf(charScore,"%d",score);
	//s=strcat(charScore,"  ");
	GUI_Text(10,160,(uint8_t *)charScore, Yellow, Black);
}

void Pong_drawScore_P2(){               //stampato sottosopra!!!
	char charScore[5];
	sprintf(charScore,"%d",score_P2);
	//s=strcat(charScore,"  ");
	GUI_TextReverse(230,170,(uint8_t *)charScore, Cyan, Black);
}

//void Pong_lowNote(){ //muri
//	soundCounter=1;
//	disable_timer(1);
//	reset_timer(1);
//	init_timer(1,180000);
//	enable_timer(1);
//}

//void Pong_highNote(){ //paddle
//	soundCounter=1;
//	disable_timer(1);
//	reset_timer(1);
//	init_timer(1,50000);
//	enable_timer(1);
//}

void Pong_drawPaddle(uint16_t xPaddleFunct){
	xPaddle=xPaddleFunct;
	for(i=0;i<10;++i){
		if(xPaddle<20){
			xPaddle=17;
			LCD_DrawLine(5,288-i,29,288-i,Yellow);
		}
		else if(xPaddle>220){
			xPaddle=222;
			LCD_DrawLine(211,288-i,234,288-i,Yellow);
		}
		else 
		LCD_DrawLine(xPaddle-12,288-i,xPaddle+12,288-i,Yellow);
	}
}

void Pong_drawPaddle_P2(){
		if(xPaddle_P2==65)
			direzione_P2=1;
	else if(xPaddle_P2==170)
			direzione_P2=-1;
	
	for(i=0;i<10;++i){
		LCD_DrawLine(xPaddle_P2-direzione_P2*56,32+i,xPaddle_P2-direzione_P2*60,32+i,Black);
		LCD_DrawLine(xPaddle_P2+direzione_P2*56,32+i,xPaddle_P2+direzione_P2*60,32+i,Cyan);
	}
	xPaddle_P2=xPaddle_P2+direzione_P2*5;
}

void Pong_erasePaddle(uint16_t xPaddle){
	for(i=0;i<10;++i){
		if(xPaddle<20)
			LCD_DrawLine(5,288-i,29,288-i,Black);
		else if(xPaddle>220)
			LCD_DrawLine(211,288-i,234,288-i,Black);
		else 
		LCD_DrawLine(xPaddle-12,288-i,xPaddle+12,288-i,Black);
	}
}

void Pong_initPaddle_P2(){
	for(i=0;i<10;++i){
		LCD_DrawLine(140-60,32+i,140+60,32+i,Cyan);
	}
}

void Pong_startScreen(){
	LCD_Clear(Black);
	
	for(i=0;i<5;++i){
		//LCD_DrawLine(0,i,239,i,Red);								  //up field
		LCD_DrawLine(i,0,i,319,Red);									//left field
		LCD_DrawLine(239-i,0,239-i,319,Red);					//right field
	}
	GUI_Text(100, 160, (uint8_t *) "PONG", Blue2, Yellow);
	Pong_drawScore();
	Pong_drawPaddle(120);
	Pong_drawScore_P2();
	Pong_initPaddle_P2();
	//Pong_drawBestScore();
	GUI_Text(25, 300, (uint8_t *) "Premi KEY1 per iniziare", Blue2, Yellow);
}

void Pong_drawBall(){
	if(x<25 && y>155 && y<175){
		//score player 1: do nothing
	}
	else if(x>205 && y>155 && y<175){
		//score player 2: do nothing
	}
	else if(x>=10&&x<=230&&y>=10){
		for(i=-2;i<=2;++i){
			for(j=-2;j<=2;++j){
				LCD_DrawLine(x+i,y+j,x+i,y+j,Red);
			}
		}	
	}
}

void Pong_eraseBall(){
	if(x<25 && y>155 && y<175){
		//score player 1: do nothing
	}
	else if(x>205 && y>155 && y<175){
		//score player 2: do nothing
	}
	else if(x>=10&&x<=230&&y>=10){
		for(i=-2;i<=2;++i){
			for(j=-2;j<=2;++j){
				LCD_DrawLine(x+i,y+j,x+i,y+j,Black);
			}
		}	
	}
}

void Pong_lose(){
		disable_timer(0);
		score=0;
	  score_P2=0;
		NVIC_DisableIRQ(EINT2_IRQn);
		NVIC_EnableIRQ(EINT0_IRQn);
		GUI_TextReverse(150, 120, (uint8_t *) "HAI VINTO", Yellow, Blue2);				//stampato sottosopra!!!
		GUI_Text(80, 200, (uint8_t *) "HAI PERSO", Blue2, Yellow);
		GUI_Text(25, 160, (uint8_t *) "Premi INT0 per resettare", Blue2, Yellow);
}

void Pong_win(){
		disable_timer(0);
		score=0;
	  score_P2=0;
		x=10;
		NVIC_DisableIRQ(EINT2_IRQn);
		NVIC_EnableIRQ(EINT0_IRQn);
		GUI_TextReverse(150, 120, (uint8_t *) "HAI PERSO", Yellow, Blue2);				//stampato sottosopra!!!
		GUI_Text(80, 200, (uint8_t *) "HAI VINTO", Blue2, Yellow);
		GUI_Text(25, 160, (uint8_t *) "Premi INT0 per resettare", Blue2, Yellow);
}

void Pong_updateBall(){
	if(x<10){ //muro sx
		segnoX=segnoX*(-1);
		//Pong_lowNote();
	}
	if(x>230){ //muro dx
		segnoX=segnoX*(-1);
		//Pong_lowNote();
	}
//	if(y<10){ //muro su
//		segnoY=+1;
//		//Pong_lowNote();
//	}
	
	if(y>267&&y<278){ //paddle player 1
		if(x<xPaddle+20&&x>xPaddle-20&&segnoY==1){
			segnoY=-1;
			if(x==xPaddle&&x>10&&x<230){//90 gradi
				tg1=0;
				tg2=2;
			}
			else if(abs(x-xPaddle)>=7){//30 gradi
				tg1=2;													
				tg2=1;
			}
			else if(abs(x-xPaddle)<7){//60 gradi
				tg1=1;		
				tg2=2;
			}				
		}
	}
	
		if(y>41&&y<51){ //paddle player 2
		if(x<xPaddle_P2+68&&x>xPaddle_P2-68&&segnoY==-1){
			segnoY=1;
			if(x==xPaddle_P2){            //90 gradi
				tg1=0;
				tg2=2;
			}
			else if(abs(x-xPaddle_P2)>34){//30 gradi
				tg1=2;		
				tg2=1;
			}
			else if(abs(x-xPaddle_P2)<=34){//60 gradi
				tg1=1;	
				tg2=2;
			}				
		}
	}
	
	if(y<311&&y>9){
		y=y+4*segnoY*tg2;
		x=x+4*segnoX*tg1;
	}
	else{
		if(y<=9){
			score++;
			Pong_drawScore();
			Pong_eraseBall();
			x=xPaddle+1;
			if(x<10) x=10;
			if(x>230) x=230;
		  y=165;
		  tg1=0;
			tg2=1;
			segnoX=-1;
			segnoY=+1;
			if(score==5)
				Pong_win();
		}
		if(y>=311){
			score_P2++;
			Pong_drawScore_P2();
			Pong_eraseBall();
			x=10;
		  y=160;
		  tg1=1;
			tg2=1;
			segnoX=+1;
			segnoY=-1;
			if(score_P2==5)
				Pong_lose();
		}
	}
		
}
	

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
