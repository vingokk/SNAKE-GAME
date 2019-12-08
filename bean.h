#ifndef BEAN_H
#define BEAN_H


volatile unsigned int flag = 1;
int bean_x = 0; int bean_y = 0; // bean

void bean();

void bean(){
	//srand((unsigned int) time(0));
	if(flag){
		bean_x = rand()%8 + 1;
		bean_y = rand()%8 + 1;
		flag = 0;
	}
	
	switch(bean_x){
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

	
		switch(bean_y){
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
}



#endif
