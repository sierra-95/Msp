/*
 * test.c
 *
 * Created: 6/13/2023 4:56:19 PM
 * Author: admin
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB=0xff;
	for(;;) //repeat forever
	{
		
		PORTB=0X55;
		PORTB=0XAA;
	}
	return 0;
}

