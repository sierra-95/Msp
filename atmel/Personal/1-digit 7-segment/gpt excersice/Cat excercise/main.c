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

// Array to hold the 7-segment display patterns for numbers 0 to 9
const uint8_t digits[10] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111  // 9
};

void displayDigit(uint8_t digit) {
	LED_Port = digits[digit]; // Display the given digit on the 7-segment display
}

int main(void) {
	LED_Dir = 0xFF; // Set all pins of PORTD as output
	
	// No need to set up the RESET pin as it's a dedicated reset pin and doesn't need configuration

	uint8_t num = 9; // Start with digit 9
	
	while (1) {
		// Display the current digit
		displayDigit(num);
		_delay_ms(1000); // Delay of 1000ms (1 second)
		
		// Decrement the digit, and if it reaches 0, reset to 9
		if (num == 0) {
			num = 9;
			} 
			else {
			num--;
		}
	}

	return 0;
}