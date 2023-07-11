/* Exercise3.c
 *
 * Created: 13/06/2023 18:07:50
 * Author : Michael Machohi
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

char display[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
int SEG1 = 4;
int SEG2 = 5;
int delayvalue = 5000;
int i = 0;
int j = 0;

/* A function to act as a persistence of vision delay */
void vision_persist() {
	int delay = delayvalue;
	while (0 < delay) {
		_delay_us(1);
		--delay;
	}
}

/* A function to reload the timer initial value after the timer overflows */
void sevseg_refreshDisplay() {
	TCNT1 = 34286; // Set TCNT1 to count for 30ms
	TCCR1B |= (1 << CS11); // Start timer1 with 8 prescaler
}

void displayLED(int input) { /* Function to display a number on the LED */
	char BH = (~PORTB & 0xF0);
	char BL = (display[input] & 0x0F);
	PORTB = ~(BH | BL);

	char DL = (~PORTD & 0x0F);
	char DH = (display[input] & 0xF0);
	PORTD = ~(DH | DL);
}

ISR(TIMER1_OVF_vect) { /* Interrupt Service Routine for Timer1 */
	PORTB ^= (1 << SEG1); // Toggle SEG1
	PORTB ^= (1 << SEG2); // Toggle SEG2
	displayLED(i);
	vision_persist();

	PORTB ^= (1 << SEG1); // Toggle SEG1
	PORTB ^= (1 << SEG2); // Toggle SEG2
	displayLED(j);
	vision_persist();

	sevseg_refreshDisplay();
}

void InitADC() {
	// Select AVcc as the reference voltage
	ADMUX |= (1 << REFS0);
	// Set prescaler to 128 and enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

uint16_t ReadADC(uint8_t ADCchannel) {
	// Select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	// Start single conversion
	ADCSRA |= (1 << ADSC);
	// Wait until ADC conversion is complete
	while (ADCSRA & (1 << ADSC))
		;
	return ADC;
}

int main(void) {
	// Initialize ADC
	InitADC();
	DDRB |= 0xFF;
	DDRD |= 0xFF;
	DDRC = 0x00;
	PORTB |= (1 << SEG1);
	

	/* Interrupt Setup */
	sevseg_refreshDisplay();
	TIMSK1 |= (1 << TOIE1); // Enable Timer1 overflow interrupts
	sei(); // Enable global interrupt

	while (1) {
		// Read analog value from potentiometer connected to ADC channel 0
		uint16_t rawValue = ReadADC(0);
		// Define the minimum and maximum values of the potentiometer
		uint16_t minVal = 0;
		uint16_t maxVal = 653;//Potentiometer resistance = 9.35k : 2^9.35=652.57

		// Adjust the raw value relative to the minimum
		uint16_t adjustedValue = rawValue - minVal;

		// Calculate the range of the potentiometer
		uint16_t valRange = maxVal - minVal;

		// Map the adjusted value to the range of 0 to 99
		uint8_t mappedValue = (adjustedValue * 99) / valRange;
		uint8_t digit1 = mappedValue / 10;
		uint8_t digit2 = mappedValue % 10;
		i = digit1;
		j = digit2;

		_delay_ms(10); // Delay for smoother potentiometer reading
	}
}