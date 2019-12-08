#ifndef SNAKE_H
#define SNAKE_H

#define up '2'
#define left '4'
#define down '8'
#define right '6'

unsigned int len = 3;
unsigned int tail = 2;
unsigned int pos = 0;

#define score (len-3)


typedef struct Coord{int x; int y;}Coord;


Coord head[1000];

void snake_init();
void snake_right();
void snake_up();
void snake_left();
void snake_down();
void snake_grow();
void snake_win();
void snake_lose();
void snake_dead();
void snake_draw();


void snake_init(){
	
	Coord a; a.x = 1; a.y = 4;
	Coord b; b.x = 2; b.y = 4;
	Coord c; c.x = 3; c.y = 4;
	
	head[0] = a;
	head[1] = b;
	head[2] = c;
	
}

void snake_right(){
	Coord d; 
	if(head[tail].x == 8){
		d.x = 1; d.y = head[tail].y;
	}
	else{
		d.x = head[tail].x +1; d.y = head[tail].y;
	}
	++ tail;
	head[tail] = d;
	++ pos;
	snake_grow();
	snake_dead();
}
void snake_up(){
	Coord d; 
	if(head[tail].y == 8){
		d.y = 1; d.x = head[tail].x;
	}
	else{
		d.x = head[tail].x; d.y = head[tail].y+1;
	}
	++ tail;
	head[tail] = d;
	++ pos;
	snake_grow();
	snake_dead();
}

void snake_left(){
	Coord d; 
	if(head[tail].x == 1){
		d.x = 8; d.y = head[tail].y;
	}
	else{
		d.x = head[tail].x -1; d.y = head[tail].y;
	}
	++ tail;
	head[tail] = d;
	++ pos;
	snake_grow();
	snake_dead();
}

void snake_down(){
	Coord d; 
	if(head[tail].y == 1){
		d.y = 8; d.x = head[tail].x;
	}
	else{
		d.y = head[tail].y -1; d.x = head[tail].x;
	}
	++ tail;
	head[tail] = d;
	++ pos;
	snake_grow();
	snake_dead();
}

void snake_grow(){
	if(head[tail].x == bean_x && head[tail].y == bean_y){
		++len;
		--pos;
		flag = 1;
	}
}

void snake_dead(){
	for(unsigned i = pos; i < (pos + len - 1); ++i){
		if(head[tail].x == head[i].x && head[tail].y == head[i].y){
			len = 103;
		}
	}
}


void snake_win(){
	PORTD =  ~(0x2C); 
	PORTB =  ~(0xD6);
}
void snake_lose(){
	PORTD =  (0x2C); 
	PORTB =  (0xD6);
}
void snake_draw(){
	for(unsigned i = pos; i < (pos + len); ++i){
	switch(head[i].x){
			case 1:
				PORTB &= 0xEF;
				break;
			case 2:
				PORTD &= 0xFB;
				break;
			case 3:
				PORTD &= 0xF7;
				break;
			case 4:
				PORTB &= 0xFD;
				break;
			case 5:
				PORTD &= 0xDF;
				break;
			case 6:
				PORTB &= 0xFB;
				break;
			case 7:
				PORTB &= 0xBF;
				break;
			case 8:
				PORTB &= 0x7F;
				break;
			default:
				break;
		}

	
		switch(head[i].y){
			case 8:
				PORTB |= 1;
				break;
			case 7:
				PORTB |= (1 << 5);
				break;
			case 6:
				PORTD |= (1 << 7);
				break;
			case 5:
				PORTB |= (1 << 3);
				break;
			case 4:
				PORTD |= 1;
				break;
			case 3:
				PORTD |= (1 << 6);
				break;
			case 2:
				PORTD |= (1 << 1);
				break;
			case 1:
				PORTD |= (1 << 4);
				break;
			default:
				break;
		}
		PORTD =  0x2C;
		PORTB =  0xD6;
		bean();
	}
	

}
#endif
