#include <avr/io.h>
#include <util/delay.h>

#define RED_LED_PIN PC0
#define YELLOW_LED_PIN PC1
#define GREEN_LED_PIN PC2

void initialize()
{
	// Set the three LED pins as output
	DDRC |= (1 << RED_LED_PIN) | (1 << YELLOW_LED_PIN) | (1 << GREEN_LED_PIN);
}

void setLED(uint8_t pin)
{
	PORTC |= (1 << pin);
}

void clearLED(uint8_t pin)
{
	PORTC &= ~(1 << pin);
}

int main(void)
{
	initialize();

	while (1)
	{
		// Turn on the red LED
		setLED(RED_LED_PIN);
		_delay_ms(3000); // Delay for 3 seconds

		// Turn off the red LED and turn on the amber LED
		clearLED(RED_LED_PIN);
		setLED(YELLOW_LED_PIN);
		_delay_ms(3000); // Delay for 3 seconds

		// Turn off the amber LED and turn on the green LED
		clearLED(YELLOW_LED_PIN);
		setLED(GREEN_LED_PIN);
		_delay_ms(3000); // Delay for 3 seconds

		// Turn off the green LED and repeat the sequence
		clearLED(GREEN_LED_PIN);
	}

	return 0;
}