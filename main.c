  /*    Author: Wenguang Wang        Email:wangwenguang98@gmail.com
 *      Lab Section: 022 
 *      Assignment: Custom Project
 *      Description: [Snake Game]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "joystick.h"
#include "bean.h"
#include "snake.h"
#include "lcd.c"
#include "timer.h"


typedef struct task{
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFct) (int);
}task;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long period_STICK = 20;
const unsigned long period_SNAKE = 300;
const unsigned long period_LCD = 200;
const unsigned long tasksPeriodGCD = 10;

enum STICK_States{STICK_Init, STICK_Start, STICK_Switch}STICK_State;
int TickFct_STICK(int state);

enum SNACK_States{SNACK_Init, SNAKE_Start, SNAKE_Right, SNAKE_Left, SNAKE_Up, SNAKE_Down, SNAKE_WIN, SNAKE_LOSE}SNAKE_State;
int TickFct_SNAKE(int state);

enum LCD_States{LCD_Init, LCD_Start, LCD_Display, LCD_Wait}LCD_State;
int TickFct_LCD(int state);

int main(void){
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	PORTD =  0x2C;
	PORTB =  0xD6;
	unsigned char i = 0;
	tasks[i].state = STICK_Init;
	tasks[i].period = period_STICK;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = & TickFct_STICK;
	
	++i;
	tasks[i].state = SNACK_Init;
	tasks[i].period = period_SNAKE;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = & TickFct_SNAKE;
	
	++i;
	tasks[i].state = LCD_Init;
	tasks[i].period = period_LCD;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = & TickFct_LCD;

	TimerSet(tasksPeriodGCD);
	TimerOn();
	snake_init();
	while(1){
		snake_draw();
	}
	
}


int TickFct_STICK(int state){
	switch(state){
		case STICK_Init:
			state = STICK_Start;
			break;
		case STICK_Start:
			state = STICK_Switch;
			break;
		case STICK_Switch:
			state = STICK_Switch;
			break;
	}
	switch(state){
		case STICK_Start:
			stick_init();
			break;
		case STICK_Switch:
			stick_switch();
			break;
	}
	return state;
}

int TickFct_SNAKE(int state){
	switch(state){
		case SNACK_Init:
			state = SNAKE_Start;
			break;
		case SNAKE_Start:
			if(stick != '0'){state = SNAKE_Right;}
			break;
		case SNAKE_Right:
			if(stick == up){state = SNAKE_Up;}
			else if(stick == down){state = SNAKE_Down;}
			
			if(score == 6){	state = SNAKE_WIN;}
			else if (score == 100){state = SNAKE_LOSE;}
			break;
		case SNAKE_Left:
			if(stick == up){state = SNAKE_Up;}
			else if(stick == down){state = SNAKE_Down;}
			
			if(score == 6){	state = SNAKE_WIN;}
			else if (score == 100){state = SNAKE_LOSE;}
			break;
		case SNAKE_Up:
			if(stick == right){state = SNAKE_Right;}
			else if(stick == left){state = SNAKE_Left;}
			
			if(score == 6){	state = SNAKE_WIN;}
			else if (score == 100){state = SNAKE_LOSE;}
			break;
		case SNAKE_Down:
			if(stick == right){state = SNAKE_Right;}
			else if(stick == left){state = SNAKE_Left;}
			
			if(score == 6){	state = SNAKE_WIN;}
			else if (score == 100){state = SNAKE_LOSE;}
			break;
		case SNAKE_WIN:
			break;
		case SNAKE_LOSE:
			break;
	}
	switch(state){
			
		case SNAKE_Start:
			snake_init();
			snake_draw();
			break;
		case SNAKE_Right:
			snake_right();
			snake_draw();
			break;
		case SNAKE_Left:
			snake_left();
			snake_draw();
			break;
		case SNAKE_Up:
			snake_up();
			snake_draw();
			break;
		case SNAKE_Down:
			snake_down();
			snake_draw();
			break;
		case SNAKE_WIN:
			snake_win();
			break;
		case SNAKE_LOSE:
			snake_lose();
			break;
	}
	return state;
}


int TickFct_LCD(int state){
	switch(state){
		case LCD_Init:
			state = LCD_Start;
			break;
		case LCD_Start:	
			state = LCD_Display;
			break;
		case LCD_Display:
			state = LCD_Wait;
			break;
		case LCD_Wait:
			if(stick != '0'){state = LCD_Display;}
			break;
	}
	switch(state){
		case LCD_Start:
			LCD_init();
			LCD_ClearScreen();
			break;
		case LCD_Display:
			LCD_Snake();
			break;
		case LCD_Wait:
			break;
	}
	return state;
}

void TimerISR(){
	unsigned char i = 0;
	for(i=0; i<tasksNum; ++i){
		if(tasks[i].elapsedTime >= tasks[i].period){
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
}



