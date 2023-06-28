/*
 * Embedded hello world xor version.c
 *
 * Created: 6/27/2023 5:07:08 PM
 * Author : admin
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
    DDRB=(1<<PB3); //setting PB3 as output only
    while (1) 
    {
		PORTB ^= (1<<PB3);// X^=Y means x=x^y
		/* initially PORTB= ob 0000 0000 and 1<<PB3 = OB 0000 1000
		XOR masking - set 0 if bits are same and 1 if different
		PORTB= ob 0000 0000
		mask=  0b 0000 1000
		result-0b 0000 1000
		-----------loop 2--------------
		PORTB= ob 0000 1000
		mask=  0b 0000 1000
		result-0b 0000 0000
		*/
		_delay_ms(100);
    }
}

