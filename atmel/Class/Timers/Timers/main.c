/*
 * Timers.c
 *
 * Created: 7/14/2023 2:05:10 PM
 * Author : admin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*Interrupt Service Routine for INT0*/
ISR(TIMER0_OVF_vect)
{
	PORTC ^= (1<<PC0); /* Toggle PORTC PC0 */
	TCNT0 = 0xB2; /* At the end of each cycle: Reload start value to TCNT0 */
}
int main(void){
	/* Initialization */
	DDRA = 0x07; /* Make PORTA as output PORT i.e. PA0, PA1, PA2*/
	DDRC = 1<<PC0; /* Make PORTC as output PORT i.e. PC0*/
	DDRD = 0; /* PORTD as input */
	PORTD = 1<<PD2; /* Activate pull up resistor high */
	/* Interrupt setup */
	TIMSK=(1<<TOIE0); /* Enable Timer0 overflow interrupts */
	TCNT0 = 0xB2; /* Load TCNT0, count for 10ms*/
	TCCR0 = (1<<CS02) | (1<<CS00); /* Start timer0 with /1024 pre-scaler*/
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
