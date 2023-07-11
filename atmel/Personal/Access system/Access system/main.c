/*
 * Access system.c
 *
 * Created: 6/29/2023 3:12:28 PM
 * Author : admin
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>

void green();
void red();


int main(void)
{

    /* ---------LONG FORM----------*
	DDRB=DDRB & ~(1<<PB0); //mask = ob 1111 1110
	                        DDRB=  0b 0000 0000
	                        result=0b 0000 0000
							/
	DDRB=DDRB & ~(1<<PB1); //mask = ob 1111 1101
	DDRB=DDRB & ~(1<<PB2); //mask = ob 1111 1011
	DDRB=DDRB & ~(1<<PB3); //mask = ob 1111 0111
	
	DDRC=DDRC | (1<<PC0); //ob 0000 0001 set PC0 as output
	DDRC=DDRC | (1<<PC1); //ob 0000 0010 set PC1 as output
	DDRC=DDRC | (1<<PC2); //ob 0000 0100 set PC2 as output
	DDRC=DDRC | (1<<PC3); //ob 0000 1000 set PC3 as output
	
	DDRD=DDRD | (1<<PD0); //ob 0000 0001 set PD0 as output
	   DDRD= ob 0000 0000
	   mask= ob 0000 0001
	  result-ob 0000 0001
	
	DDRD=DDRD | (1<<PD1); //ob 0000 0010 set PD1 as output 
	
	PORTB= PORTB | (1<<PB0);
	PORTB= PORTB | (1<<PB1);
	PORTB= PORTB | (1<<PB2);
	PORTB= PORTB | (1<<PB3);
	*/
	
	
	//-------SHORT FORM--------
	
	DDRB= 0x00; //0b 0000 0000
	DDRC= 0x0F; //0b 0000 1111
	DDRD= 0X03; //0b 0000 0011
	
	PORTB= 0x0F; //ob 0000 1111
			
	while(1){
		
		int pin4_status= ~PINB & (1<<PB3);		
		if(pin4_status && PORTC==0X00) 
		{
			green();
			PORTC=PORTC | (1<<PC3);			
		}
		else{
			red();
		}
		
		
		int pin3_status= ~PINB & (1<<PB2);
		if(pin3_status && PORTC==0X08){
			green();
			PORTC=PORTC | (1<<PC2);
		}
		else{
			red();
		}
		
		int pin2_status= ~PINB & (1<<PB1);
		if(pin2_status && PORTC==0x0C ){
			green();
			PORTC=PORTC | (1<<PC1);
		}
		else{
			red();
		}
		
		int pin1_status= ~PINB & (1<<PB0);
		if(pin1_status && PORTC==0x0E){
			green();
			PORTC=PORTC | (1<<PC0);
		}
		else{
			red();
		}
		
				
	}
	
		
	return 0;		
	
}
void green(){
	int i=0;
	
	while(i<4)
	{
		PORTD^= (1<<PD0);
		_delay_ms(50);
		i++;
		
	}
	
}
void red(){
	int i=0;
	while(i<4)
	{
		PORTD^= (1<<PD1);
		_delay_ms(50);
		i++;
		
	}
	
}

