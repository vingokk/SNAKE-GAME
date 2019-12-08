#ifndef JOYSTICK_H
#define JOYSTICK_H

unsigned char stick = '0';
const int HORIZONTAL=141;//neutral value on x-axis
const int VERTICAl = 151;// neutral value on y-axis
int HORIZONTALMOV;
int VERTICAlMOV;
void stick_init();
void stick_switchx();
void stick_switchy();

void stick_init(){
	HORIZONTALMOV = 0;
	VERTICAlMOV = 200;
	ADMUX |=(1<<REFS0);
	ADCSRA |=(1<<ADEN) |(1<ADPS2)|(1<ADPS1) |(1<<ADPS0);
}
void stick_switch(){
	switch (ADMUX){ //changing between channels by switch statement
		case 0x40://When ADMUX==0x40
			ADCSRA |=(1<<ADSC);//start ADC conversion
			while ( !(ADCSRA & (1<<ADIF)));//wait till ADC conversion
			HORIZONTALMOV = ADC;//moving value
			ADC=0;//reset ADC register
			ADMUX=0x41;//changing channel
			if (HORIZONTALMOV < HORIZONTAL-50){stick = '8';}					//left
			else if (HORIZONTALMOV> HORIZONTAL + 400){stick = '2';}			//right
			else{stick = '0';}
		break;

		case 0x41:
			ADCSRA |=(1<<ADSC);// start ADC conversion
			while ( !(ADCSRA & (1<<ADIF)));// wait till ADC conversion
			VERTICAlMOV = ADC;// moving value
			ADC=0;// reset ADC register
			ADMUX=0x40;// changing channel
			if (VERTICAlMOV < VERTICAl-50){stick = '4';}					//left
			else if (VERTICAlMOV > VERTICAl+410){stick = '6';}			//right
			else{stick = '0';}
		break;
	}
}
void stick_switchy(){
	ADCSRA |=(1<<ADSC);											// start ADC conversion
	while ( !(ADCSRA & (1<<ADIF)));								// wait till ADC conversion
	VERTICAlMOV = ADC;											// moving value
	ADC=0;														// reset ADC register
	
}

#endif
