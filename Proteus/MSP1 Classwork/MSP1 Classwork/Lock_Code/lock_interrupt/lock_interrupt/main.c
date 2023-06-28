/*
 * lock_interrupt.c
 *
 * Created: 15/06/2023 15:01:09
 * Author : OWNER
 */ 

// Preprocessor commands
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LENGTH 3

int no_inputs = 0;
int password[LENGTH] = {1,1,1};
int inputs[LENGTH] = {0,0,0};

ISR(INT0_vect){
	// ISR of button 1
	if(no_inputs < LENGTH){
		inputs[no_inputs] = 1;
		no_inputs++;
	}
}

ISR(INT1_vect){
	// ISR of button 2
	if(no_inputs < LENGTH){
		inputs[no_inputs] = 2;
		no_inputs++;
	}
}

ISR(INT2_vect){
	// ISR of button 3
	if(no_inputs < LENGTH){
		inputs[no_inputs] = 3;
		no_inputs++;
	}
}


void flashGreen(){
	PORTC = 0b00000001;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
	PORTC = 0b00000001;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
	PORTC = 0b00000001;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
}

void flashRed(){
	PORTC = 0b00000010;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
	PORTC = 0b00000010;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
	PORTC = 0b00000010;
	_delay_ms(500);
	PORTC = 0b00000000;
	_delay_ms(500);
}

void systemReset(){
	no_inputs = 0;
	inputs[0] = 0;
	inputs[1] = 0;
	inputs[2] = 0;
}

int main(void)
{
	// Setup inputs and outputs
	DDRB = 0x00;
	PORTB = 0x04; //0b00000100
	DDRD = 0x00;
	PORTD = 0x0C; //0b00001100
	
	DDRC = 0x1F;
	
	//Setup the Interrupts
	/* Interrupt setup */
	GICR = 1<<INT0 | 1<<INT1 | 1<<INT2; /* Enable INT0, INT1, INT2*/
	MCUCR = 1<<ISC01 | 1<<ISC00; /* Trigger INT0 on rising edge */
	MCUCR = 1<<ISC11 | 1<<ISC10; /* Trigger INT1 on rising edge */
	MCUCSR = 1<<ISC2; /* Trigger INT2 on rising edge */
	sei(); /*global interrupt enable*/
	
    /* Replace with your application code */
    while (1) {
		// We need to check the number of inputs
		switch(no_inputs){
		case 1:
		//		   76543210
		 PORTC |= 0b00000100;
		 break;
		case 2: 
		//		   76543210
		PORTC |= 0b00001000;
		break;	 
		case 3:
		//		   76543210
		PORTC |= 0b00010000;
		break;
		default:
		PORTC = 0x00;
		}
		
		if(no_inputs == LENGTH){
			int check = 0;
			for(int i = 0; i < LENGTH; i++){
				if(password[i] == inputs[i]){
					check++;
				}
			}
			
			if(check == 3){
				flashGreen();
			}else{
				flashRed();
			}
			systemReset();
		}
    }
}

