/*Typical Header file inclusion and CPU frequency definition*/
#define F_CPU 8000000UL#include <avr/io.h>#include <util/delay.h>
#include <string.h>
#define KEY_PIN PIND // Keypad input pin
#define MAX_DISPLAY_LENGTH 15 // Maximum characters to display on the LCD

/* Function Declarations */
void LCD_Cmd(unsigned char cmd);
void LCD_Char(unsigned char char_data);
void LCD_Init(void);
void LCD_Clear(void);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char *str);


/* Keypad array holding the keys in a grid arrangement*/
unsigned char keypad[4][4] = { {'7','8','9','/'},
{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};
/* Function that checks the key that has been pressed on the keypad */
char check_Keypad()
{
	unsigned char rowNum, colNum, input;
	while(1)
	{
		DDRD = 0xF0; // Set the rows as outputs and the columns as inputs
		PORTD = 0x0F; // Set the columns HIGH and the rows LOW.
		/*With the columns HIGH and the rows LOW, thus the KEY_PIN == 0x0F(0b0000 1111).		If a button is pressed, the value of the column pin will be grounded and		KEY_PIN will change from 0x0F to some other number 0x0E i.e.
		0x0E(0b0000 1110) i.e. a button in the 4th column was pressed.		*/
		do
		{
			do
			{
				_delay_ms(20); // 20ms key de_bounce time
				colNum = (KEY_PIN & 0x0F); // read status of column
			}while(colNum == 0x0F); // check for any key press
			_delay_ms (40); // 20 ms key de_bounce time
			colNum = (KEY_PIN & 0x0F);
		}while(colNum == 0x0F);
		/*Once we have established which column the button is, we need to know the row
		To this we set the rows HIGH and ground them 1 pin at a time while reading the result		on the column pins.
		*/
		PORTD = 0xEF; // Check for pressed key in 4th row
		asm("NOP");
		input = (KEY_PIN & 0x0F);
		if(input != 0x0F)
		{
			rowNum = 3;
			break;		}
		PORTD = 0xDF; // Check for pressed key in 3rd row
		asm("NOP");
		input = (KEY_PIN & 0x0F);
		if(input != 0x0F)
		{
			rowNum = 2;
			break;		}
		PORTD = 0xBF; // Check for pressed key in 2nd row
		asm("NOP");
		input = (KEY_PIN & 0x0F);
		if(input != 0x0F)
		{
			rowNum = 1;
			break;
		}
		PORTD = 0x7F; // Check for pressed key in 1st row
		asm("NOP");
		input = (KEY_PIN & 0x0F);
		if(input != 0x0F)
		{
			rowNum = 0;
			break;		}
	}
	/*After obtaining the column and row values, the final keypad key can be output by cross	referencing
	the rows and columns in our keypad character array	*/
	if(colNum == 0x0E)	return(keypad[rowNum][3]);	else if(colNum == 0x0D)	return(keypad[rowNum][2]);	else if(colNum == 0x0B)	return(keypad[rowNum][1]);	else	return(keypad[rowNum][0]);
}
int main(){
	DDRC = 0xFF;  /* Make LCD command port direction as output pins */
	LCD_Init(); /* Initialize LCD */
	LCD_Cmd(0x80); // Move cursor to the beginning of the first line
	LCD_String("Hello, LCD!"); // Display string on LCD
	
	char key ;
	char displayStr[MAX_DISPLAY_LENGTH + 1]; // Buffer to hold displayed characters (+1 for null terminator)
	displayStr[0] = '\0'; // Initialize buffer as an empty string
	
	while(1) {
		key = check_Keypad(); // Get the pressed key from the keypad
		
		if (key != ' ' && key != '\0') {
			if (key == 'C') { // Check if the 'C' key is pressed
				// Clear the display
				displayStr[0] = '\0'; // Clear the display string
				LCD_Cmd(0x01); // Clear the LCD display
			} else{
			// Concatenate the new key to the existing display string if there is space
			if (strlen(displayStr) < MAX_DISPLAY_LENGTH) {
				strncat(displayStr, &key, 1); // Concatenate the key character to displayStr
				LCD_String_xy(1, 0, displayStr); // Display the updated string on LCD
			}
			}
			// Wait a bit to avoid continuous key detection
			_delay_ms(50);
		}
		}
	}
