#define F_CPU 8000000UL 
#include <avr/io.h> 
#include <util/delay.h> 
#define LED_Dir DDRD /*define LED Directory*/ 
#define LED_Port PORTD /*define LED PORT*/

void display(int digit);
 int main(void) 
 { 
	 /*initialization*/ 
	 LED_Dir |= 0xff; 
	 LED_Port = 0xff; 
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
	 char numbers[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
		  // 0b 1111 1001
	 if(digit < 10 ){
		  LED_Port = numbers[digit]; 
		  } 
}

