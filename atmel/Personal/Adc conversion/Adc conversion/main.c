/*
 * Adc conversion.c
 *
 * Created: 7/28/2023 4:42:58 PM
 * Author : admin
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>
#define SEG1_Dir DDRB /*define SEG1 Directory*/
#define SEG1_Port PORTB /*define SEG1 PORT*/
#define SEG2_Dir DDRC /*define SEG2 Directory*/
#define SEG2_Port PORTC /*define SEG2 PORT*/
#define SEG3_Dir DDRD /*define SEG3 Directory*/
#define SEG3_Port PORTD /*define SEG3 PORT*/
void DISPLAY_Init(); /*Function declaration*/
void display_1(int digit); /*Function declaration*/
void display_2(int digit); /*Function declaration*/
void display_3(int digit); /*Function declaration*/
char numbers[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
/*Function declaration*/
void ADC_Init(){
	DDRA = 0x0; /* Make ADC port as input */
	ADCSRA = 0x87; /* Enable ADC, fr/128 */
	ADMUX = 0x40; /* Vref: Avcc */
}
int ADC_Read(int channel){
	int Ain,AinLow;
	ADMUX = ADMUX|(channel); /* Set input channel to read */
	ADCSRA |= (1<<ADSC); /* Start conversion */
	while((ADCSRA & (1<<ADIF)) == 0);/* Monitor end of conversion interrupt */
	_delay_us(10);
	AinLow = (int)ADCL; /* Read lower byte*/
	Ain = (int)ADCH*256; /* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;
	return(Ain); /* Return digital value*/
}
int main(){
	int value;
	int hunds, tens, ones;
	ADC_Init();
	DISPLAY_Init();
	while(1)
	{
		value = ADC_Read(0); /* Read ADC channel 0 */
		value = value/10;
		hunds = value/100;
		value %= 100;
		tens = value/10;
		ones = value%10;
		display_1(hunds);
		display_2(tens);
		display_3(ones);
	}
	return 0;
}
/*Function declaration*/
void DISPLAY_Init(){
	/*initialization*/
	SEG1_Dir |= 0xff;
	SEG1_Port = 0xff;
	SEG2_Dir |= 0xff;
	SEG2_Port = 0xff;
	SEG3_Dir |= 0xff;
	SEG3_Port = 0xff;
}
void display_1(int digit){
	SEG1_Port = numbers[digit];
}
void display_2(int digit){
	SEG2_Port = numbers[digit];
}
void display_3(int digit){
	SEG3_Port = numbers[digit];
}


