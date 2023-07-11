#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
char display[] = {0x3F ,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
int SEG1 = 4;
int SEG2 = 5;
void displayLED(int input){
	char BH = (~PORTB & 0xF0);
	char BL = (display[input] & 0x0F);
	PORTB = ~(BH|BL);
	char DL = (~PORTD & 0x0F);
	char DH = (display[input] & 0xF0);
	PORTD = ~(DH|DL);
}
int main(void){
	DDRB |= 0xFF;
	DDRD |= 0xFF;
	int count = 0;

	while (1) {
		PORTB |= (1<<SEG1);
		PORTB |= (1<<SEG2);
		if(count < 10){
			displayLED(count);
			count++;
			_delay_ms(100);
		}
		if(count == 10){
			count = 0;
		}
	}
}