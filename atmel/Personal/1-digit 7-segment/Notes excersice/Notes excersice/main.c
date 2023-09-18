/*
 * Cat excercise.c
 *
 * Created: 7/19/2023 10:07:50 PM
 * Author : admin
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LED_Dir DDRD      // Macro to define the LED direction register
#define LED_Port PORTD    // Macro to define the LED port register


void display(int digit);/*function declaration*/
int main(void)
{
	/*initialization*/
	LED_Dir |= 0xff;
	LED_Port = 0xff;
	while (1){
		for(int i=0;i<10;i++){
			display(i); /* Function call */
			_delay_ms(1000);/* wait for 1 second */
		}
	}
}
/*Function definition*/
void display(int digit){
	/*We light each LED one at a time*/
	/* write hex value for Common Cathode display from 0 to 9 */
	char numbers[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	if(digit < 10 ){
		LED_Port = numbers[digit];
	}
}

