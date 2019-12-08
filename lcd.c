#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))
          
/*-------------------------------------------------------------------------*/

#define DATA_BUS PORTC		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTA	// port connected to pins 4 and 6 of LCD disp.
#define RS 6			// pin number of uC connected to pin 4 of LCD disp.
#define E 7			// pin number of uC connected to pin 6 of LCD disp.

/*-------------------------------------------------------------------------*/

void LCD_ClearScreen(void) {
   LCD_WriteCommand(0x01);
}

void LCD_init(void) {

    //wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);//0x38 16x2 5x7 8bit ; 0x30 16x1
	LCD_WriteCommand(0x06);//after writing address+1
	LCD_WriteCommand(0x0f);//present + blink
	LCD_WriteCommand(0x01);//clear
						   // LCD_WriteCommand(0x18);  move the screen; 
	delay_ms(10);						 
}

void LCD_WriteCommand (unsigned char Command) {
   CLR_BIT(CONTROL_BUS,RS);
   DATA_BUS = Command;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
   SET_BIT(CONTROL_BUS,RS);
   DATA_BUS = Data;
   SET_BIT(CONTROL_BUS,E);
   asm("nop");
   CLR_BIT(CONTROL_BUS,E);
   delay_ms(1);
}

void LCD_DisplayString( unsigned char column,  const unsigned char* string) {
   unsigned char c = column;
   while(*string) {
    	LCD_Cursor(c++);
    	LCD_WriteData(*string++);
 	 
   }
}

void LCD_Cursor(unsigned char column) {
   if ( column < 17 ) { // 16x1 LCD: column < 9
						// 16x2 LCD: column < 17
      LCD_WriteCommand(0x80 + column - 1);
   } else {
      LCD_WriteCommand(0xB8 + column - 9);	// LCD_WriteCommand(0xB8 + column - 9);
	  										// 16x1 LCD: column - 1
											// 16x2 LCD: column - 9
   }
}

void delay_ms(int miliSec) //for 8 Mhz crystal

{
    int i,j;
    for(i=0;i<miliSec;i++)
    for(j=0;j<775;j++)
  {
   asm("nop");
  }
}

void LCD_Snake(){
	if(stick == '0'){LCD_DisplayString(1,"Move the stick to start");}
	else{
		LCD_ClearScreen();
		LCD_Cursor(1);
		if(score < 6){
			LCD_WriteData( score + '0');
		}
		else if(score == 6){
			LCD_DisplayString(1,"Got it");
		}
		else{
			LCD_DisplayString(1,"DIE");
		}
		
	}
}
