/*
 * Embedded hello world.c
 *
 * Created: 6/27/2023 4:17:48 PM
 * Author : admin
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


int main(void)
{
	//set all pins in PORTB as output
	DDRB=0XFF; //OB 1111 1111 logic 1
	/*set -pb3 as output and leave other pins unchanged
	DDRB=DDRB | (1<<PB3) PB3=3 
	SYNTAX operand(1 which is 0b 0000 0001)<<n n=number of bits to be shifted
	Initially DDRB= 0B 0000 0000 . shifting 1-3 times to the left produces ob 0000 1000
	hence DDRB=ob 0000 1000
	setting only PB3 output
	*/
	while(1) //infinite loop
	{
		PORTB = PORTB | (1<<PB3); //LOGIC 1 on PB3 HIGH
		/* or masking happened where a 0 is made 1 and 1 remains 1
		initially, in terms of high/low, PORTB  was ob 0000 0000
		1<<PB3 left shifts 1 (ob 0000 0001) three spaces to ob 0000 1000 hence our mask is
		PORTB = 0000 0000
		mask =  0000 1000
		PORTB | MASK results to ob 0000 1000
		*/
		_delay_ms(100);
		PORTB = PORTB & (~(1<<PB3)); 
		/*NOR operator used changes all logic 1 to logic 0 and vice versa
		PORTB was ='0b 0000 1000' 
		1<<PB3 converted ob 0000 0000 to 0b 0000 1000.
		~(1<<PB3) converts ob 0000 0000 to 0b 0000 1000 then performs nor operation
		giving ob 1111 0111
		hence mask = 1111 0111
		and mask: if both bits have 1, put 1 otherwise put 0
		PORTB= ob 0000 1000
		mask=  ob 1111 0111
		result-ob 0000 0000 //off
		*/
		_delay_ms(100);
			
		
	}
	return 0;
}