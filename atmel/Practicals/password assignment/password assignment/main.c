/*
 * password assignment.c
 *
 * Created: 7/19/2023 8:45:57 AM
 * Author : admin
 */ 

#include <avr/io.h>


#include <avr/io.h>
#include <util/delay.h>

#define PASSWORD_LENGTH 4
#define PASSWORD {1, 2, 3, 4}

// Function to initialize ports and pins
void initialize() {
	// Set PC0, PC1, PC2, and PC3 as output pins for LEDs
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
	
	// Set PD0 and PD1 as output pins for status LEDs
	DDRD |= (1 << PD0) | (1 << PD1);
	
	// Set PB0, PB1, PB2, and PB3 as input pins for push buttons
	DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3));
	
	// Enable internal pull-up resistors for push buttons
	PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
}

// Function to check if the entered password is correct
int checkPassword(int password[]) {
	int storedPassword[PASSWORD_LENGTH] = PASSWORD;
	int i;
	
	for (i = 0; i < PASSWORD_LENGTH; i++) {
		if (password[i] != storedPassword[i]) {
			return 0;  // Password is incorrect
		}
	}
	
	return 1;  // Password is correct
}

int main() {
	int enteredPassword[PASSWORD_LENGTH] = {0};
	int enteredCount = 0;
	int passwordCorrect = 0;
	int i;
	
	initialize();
	
	while (1) {
		// Check if any push button is pressed
		if (!(PINB & (1 << PB0))) {
			enteredPassword[enteredCount] = 1;
			enteredCount++;
			PORTC |= (1 << enteredCount-1);  // Light up the corresponding input status LED
			_delay_ms(500);  // Delay to debounce the button press
			} else if (!(PINB & (1 << PB1))) {
			enteredPassword[enteredCount] = 2;
			enteredCount++;
			PORTC |= (1 << enteredCount-1);  // Light up the corresponding input status LED
			_delay_ms(500);  // Delay to debounce the button press
			} else if (!(PINB & (1 << PB2))) {
			enteredPassword[enteredCount] = 3;
			enteredCount++;
			PORTC |= (1 << enteredCount-1);  // Light up the corresponding input status LED
			_delay_ms(500);  // Delay to debounce the button press
			} else if (!(PINB & (1 << PB3))) {
			enteredPassword[enteredCount] = 4;
			enteredCount++;
			PORTC |= (1 << enteredCount-1);  // Light up the corresponding input status LED
			_delay_ms(500);  // Delay to debounce the button press
		}
		
		// Check if all digits of the password have been entered
		if (enteredCount == PASSWORD_LENGTH) {
			// Check if the entered password is correct
			passwordCorrect = checkPassword(enteredPassword);
			
			// Reset entered password
			enteredCount = 0;
			for (i = 0; i < PASSWORD_LENGTH; i++) {
				enteredPassword[i] = 0;
			}
			
			// Light up the appropriate LED(s) based on password correctness
			if (passwordCorrect) {
				PORTD |= (1 << PD0);  // Green LED on
				PORTD &= ~(1 << PD1);  // Red LED off
				} else {
				PORTD |= (1 << PD1);  // Red LED on
				PORTD &= ~(1 << PD0);  // Green LED off
			}
			
			// Delay for a while to display the LED status
			_delay_ms(2000);
			
			// Turn off both LEDs
			PORTD &= ~((1 << PD0) | (1 << PD1));
			
			// Turn off all input status LEDs
			PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));
		}
	}
	
	return 0;
}