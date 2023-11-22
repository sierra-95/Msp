#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
char display[] = {0x3F ,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
int SEG1 = 4;
int SEG2 = 5;
int delayvalue = 5000;
int i = 0;
int j = 0;
/*A function to act as a persistence of vision delay*/
void vision_persist(){
	int delay = delayvalue;
	while (0 < delay){
		_delay_us(1);
		--delay;
	}
}
/* A function to reload the timer initial value after the timer overflows */
void sevseg_refreshDisplay(){
	TCNT1L = 0x15; /* Load TCNT1, count for 30ms*/
	TCNT1H = 0x9F;
	TCCR1B |= (1<<CS11); /* Start timer1 with 8 pre-scaler*/
	TIMSK1 |= (1<<TOIE1); /* Enable Timer1 overflow interrupts */
}
void displayLED(int input){ /*Function to display a number in the LED*/
	char BH = (~PORTB & 0xF0);
	char BL = (display[input] & 0x0F);
	PORTB = ~(BH|BL);
	char DL = (~PORTD & 0x0F);
	char DH = (display[input] & 0xF0);
	PORTD = ~(DH|DL);
}
ISR(TIMER1_OVF_vect){ /*Interrupt Service Routine for Timer1*/
	PORTB ^= (1<<SEG1); /* Toggle SEG1 */
	PORTB ^= (1<<SEG2); /* Toggle SEG2 */
	displayLED(i);
	vision_persist();
	PORTB ^= (1<<SEG1); /* Toggle SEG1 */
	PORTB ^= (1<<SEG2); /* Toggle SEG2 */
	displayLED(j);
	vision_persist();
	sevseg_refreshDisplay();
}
void InitADC(){
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
uint16_t ReadADC(uint8_t ADCchannel){
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	return ADC;
}
int main(void){
	int count = 0;
	int potentiometervalue;
	//int ADCchannel=PC0;
	DDRB |= 0xFF;
	DDRD |= 0xFF;
	PORTB |= (1<<SEG1);
	/***********************************************************************/
	/*Interrupt Setup*/
	sevseg_refreshDisplay();
	sei(); /* Enable Global Interrupt */
	/***********************************************************************/
	while (1) { /*Change this code segment to achieve a 10s countdown*/
		
		potentiometervalue=(ReadADC(0)*99/1023);
		count=potentiometervalue;
		i=count/10;
		j=count%10;		
		
		
		_delay_ms(300);
	}
}