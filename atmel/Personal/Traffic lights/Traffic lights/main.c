/*
 * Traffic lights.c
 *
 * Created: 6/27/2023 5:26:19 PM
 * Author : admin
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
    DDRB=0x49;
    while (1) 
    {
		PORTB^=(1<<PB0); // x^=y means x= x^y
		//PB1 IS ob 0000 0000 initially
		/* 1<<PB0 shifts 0000 0001 zero times hence this is the mask
		PORTB= ob 0000 0000
		mask=  ob 0000 0001  XOR sets 0 if both bits are same and 1 if different
		result-ob 0000 0001
		*/
		_delay_ms(1000);
		//turn red light off
		//PORTB= 0b 0000 0000
		PORTB^=(1<<PB0);
		//turn orange on
		PORTB^=(1<<PB3); // mask value= 0b 0000 1000
		//PORTB= 0b 0000 1000
		_delay_ms(500);
		//turn orange off
		PORTB^=(1<<PB3);
		/* to turn off PORTB= ob 0000 1000
		also 1<<PB3 IS 0b 0000 1000 which is the mask
		XOR sets 0 if both bits are same and 1 if different
		result= ob 0000 0000
		*/
		PORTB^=(1<<PB6);
		//green on
		/* PORTB= ob 0000 0000 and mask value:
		1<<PB6 is 0100 0000 
		result is 0b 0100 0000 hence PB6 sets high
		*/
		_delay_ms(1000);
		//green off
		PORTB^=(1<<PB6);	
		
		
		
		
    }
	return 0;
}

