#include <avr/io.h>
#include <util/delay.h>
#define LCD_Data_Port PORTD
#define LCD_Cmd_Port PORTC
#define LCD_Data_Dir DDRD
#define LCD_Cmd_Dir DDRC
#define RS PC0
#define RW PC1
#define EN PC2

void LCD_Cmd(unsigned char cmd){
	LCD_Data_Port = cmd;
	LCD_Cmd_Port &= ~(1<<RS); /* RS=0 command reg. */
	LCD_Cmd_Port &= ~(1<<RW); /* RW=0 Write operation */
	_delay_us(1);
	LCD_Cmd_Port |= (1<<EN); /* Enable pulse ON */
	_delay_us(1);
	LCD_Cmd_Port &= ~(1<<EN); /* Enable pulse OFF */
	_delay_ms(2);
}
void LCD_Char (unsigned char char_data){
	LCD_Data_Port = char_data;
	LCD_Cmd_Port |= (1<<RS); /* RS=1 Data reg. */
	LCD_Cmd_Port &= ~(1<<RW); /* RW=0 write operation */
	_delay_us(1);
	LCD_Cmd_Port |= (1<<EN); /* Enable Pulse ON */
	_delay_us(1);
	LCD_Cmd_Port &= ~(1<<EN); /* Enable Pulse ON */
	_delay_ms(2);
}
void LCD_Init (void){
	LCD_Cmd_Dir = 0xFF; /* Make LCD command port direction as output pins*/
	LCD_Data_Dir = 0xFF; /* Make LCD data port direction as output pins*/
	_delay_ms(50); /* LCD Power ON delay always >15ms */
	LCD_Cmd(0x02); /* Return display to its home position */
	LCD_Cmd(0x38); /* Initialization of 16X2 LCD in 8bit mode */
	LCD_Cmd(0x0F); /* Display ON Cursor Blinking */
	LCD_Cmd(0x06); /* Auto Increment cursor */
	LCD_Cmd(0x01); /* Clear display */
}
void LCD_Clear(void){
	LCD_Cmd(0x01); /* clear display */
	LCD_Cmd(0x02); /* Return display to its home position */
}
/*Send string to LCD function */
void LCD_String (char *str){
	int i;
	/* Send each char of string till the NULL */
	for(i=0;str[i]!=0;i++){
		LCD_Char(str[i]);
	}
}
const short Custorm_Chars5X8[8][7] = {
	{0x0E,0x1B,0x11,0x11,0x1F,0x1F,0x1F,0x00},
	{0xa,0xa,0x1f,0x1f,0xe,0xe,0x4,0x4,0x00},
	{0x1f,0x15,0xe,0x4,0x4,0x4,0x4,0x4,0x00},
	{0x1,0x1,0x5,0x15,0x15,0x15,0x15,0x15},
	{0xa,0xa,0x1f,0x11,0x11,0xe,0x4},
	{0x4,0x16,0xf,0x4,0xf,0x16,0x4,0x0},
	{0x4,0xe,0xe,0xe,0x1f,0x0,0xe,0x0},
	{0x3,0x7,0xd,0x9,0xb,0x1b,0x18,0x00},
};

void Load_Custom_Char(){
	/*Load custom char into the CGROM*/
	LCD_Cmd(0x40); // Set CGRAM Address
	for (int i = 0; i <= 7; i++){
		for (int j = 0; j <= 7; j++){
			LCD_Char(Custorm_Chars5X8[i][j]);
		}
	}
	//LCD_Char(Custorm_Chars5X8[2][i]);
	LCD_Cmd(0x80); // Return to Home
	/*Load custom char into the CGROM*/
}

void LCD_String_xy (char row, char pos)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Cmd((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Cmd((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
}

int main(void)
{
	LCD_Init(); /* Initialize LCD */
	Load_Custom_Char(); /* Load custom characters into CGRAM */
	LCD_Clear(); /* Clear LCD */
	LCD_String("Custom Chars");/* Display string on screen */
	_delay_ms(1000);
	LCD_String_xy(1,0); /* Place cursor on the second row */
	LCD_Char(0x00); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,2); /* Place cursor on the second row */
	LCD_Char(0x01); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,4); /* Place cursor on the second row */
	LCD_Char(0x02); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,5); /* Place cursor on the second row */
	LCD_Char(0x03); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,7); /* Place cursor on the second row */
	LCD_Char(0x04); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,9); /* Place cursor on the second row */
	LCD_Char(0x05); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,11); /* Place cursor on the second row */
	LCD_Char(0x06); /* Display the character in address 0x00 of CGRAM*/
	LCD_String_xy(1,13); /* Place cursor on the second row */
	LCD_Char(0x07); /* Display the character in address 0x00 of CGRAM*/
	_delay_ms(3000);
	int shift,i;
	shift = 15;	/* Number of time shifts count=15 */
	for(i=0;i<shift;i++)
	{
		LCD_Cmd(0x18);/* shift entire display left */
		_delay_ms(300);
		
	}
	shift=30;/* number of time shifts 30 */
	
	for(i=0;i<30;i++)
	{
		LCD_Cmd(0x1c);/* shift entire display right */
		_delay_ms(300);
	}
	
	
	while (1)
	{
	}
}