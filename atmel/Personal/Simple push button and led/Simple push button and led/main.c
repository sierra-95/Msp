#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB = DDRB | (1<<PB3); /* Make PB3 as output pin */
	/*DDRB=ob 0000 0000 . 1<<PB3 of mask value=0b 0000 1000
	DDRB = ob 0000 0000  or mask 0-> 1 and 1 remains 1
	mask = 0b 0000 1000
	result-ob 0000 1000 */ 
	DDRB = DDRB & (~(1<<PB2)); /* Make PB2 as input pin */
	/* DDRB=ob 0000 1000 and 1<<PB2 is 0b 0000 0001 -> 0b 0000 0100
	then ~1<<PB2 is 0b 1111 1011 ->mask value
	DDRB = ob 0000 1000
	mask = ob 1111 1011   and mask ->if both bits have 1, put 1 otherwise put 0
	result-ob 0000 1000  --hence PB2 is input */
	PORTB = PORTB | (1<<PB2); /* Enable pull-up on PB2 by writing 1 to it */
	/* PORTB= ob 0000 0000 logic 0(low)
	1<<PB2  shifts 0b 0000 0000 -> 0b 0000 0100
	result is 0b 0000 0100 making PB2 high */
	int pin_status;
	while(1)
	{
		pin_status = ~PINB & (1<<PB2); /*Read status of pin PB2 */
		if(pin_status) /* Transmit status of pin PB2 on to pin PB3 to drive LED.*/
		{
			PORTB = PORTB | (1<<PB3); /*Switch is open, pin_status = 1, LED is ON */
		}
		else
		{
			PORTB = PORTB & (~(1<<PB3));/*Switch is closed, pin_status = 0, LED is OFF */
		}
	}
	return 0;
}