#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED_Dir DDRD /*define LED Directory*/
#define LED_Port PORTD /*define LED PORT*/

void display(int digit);
int main(void)
{
	/*initialization*/
	LED_Dir |= 0xff; //0b 1111 1111
	LED_Port = 0xff; //0b 1111 1111
	while (1){
		for(int i=0;i<10;i++){
			display(i); /* Function to display a digit */
			_delay_ms(100); /* wait for 1 second */
		}
	}
}
void display(int digit){
	/*We light each LED one at a time*/
	/* write hex value for Common Cathode display from 0 to 9 */
	char numbers[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	//0b 00 0011 1111 // ob 0000 0110 //
		LED_Port = numbers[digit];
	}
}

