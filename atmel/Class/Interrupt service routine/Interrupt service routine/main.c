/*
 * Interrupt service routine.c
 *
 * Created: 7/19/2023 7:13:37 AM
 * Author : admin
 */ 

#include <avr/io.h>

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*Interrupt Service Routine for INT0*/
ISR(INT0_vect){
	PORTC ^= (1<<PC0); /* Toggle PORTC PC0 */
	_delay_ms(50); /* Software debouncing control delay */
}
int main(void){
	/* Initialization */
	DDRA = 0x07; /* Make PORTA as output PORT i.e. PA0, PA1, PA2*/
	DDRC = 1<<PC0; /* Make PORTC as output PORT i.e. PC0*/
	DDRD = 0; /* PORTD as input */
	PORTD = 1<<PD2; /* Activate pull up resistor high */
	/* Interrupt setup */
	GICR = 1<<INT0; /* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00; /* Trigger INT0 on rising edge */
	sei(); /* Enable Global Interrupt */
	while(1){
		/* flashing LED code*/
		PORTA = 1<<PA0;
		_delay_ms(200);
		PORTA = 1<<PA1;
		_delay_ms(200);
		PORTA = 1<<PA2;
		_delay_ms(200);
	}
}

