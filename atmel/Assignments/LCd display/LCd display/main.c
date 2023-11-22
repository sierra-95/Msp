#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_Master_Data_Dir DDRD
#define LCD_Master_Command_Dir DDRD
#define LCD_Master_Data_Port PORTD
#define LCD_Master_Command_Port PORTD
#define RS_Master PD0
#define EN_Master PD1

void LCD_Init() {
	LCD_Master_Command_Dir = 0xFF;
	LCD_Master_Data_Dir = 0xFF;
	_delay_ms(20);
	LCD_Command(0x38);
	LCD_Command(0x0C);
	LCD_Command(0x06);
	LCD_Command(0x01);
	LCD_Command(0x80);
}

void LCD_Command(unsigned char cmnd) {
	LCD_Master_Data_Port = cmnd;
	LCD_Master_Command_Port &= ~(1 << RS_Master);
	LCD_Master_Command_Port |= (1 << EN_Master);
	_delay_us(1);
	LCD_Master_Command_Port &= ~(1 << EN_Master);
	_delay_ms(3);
}

void LCD_Char(unsigned char char_data) {
	LCD_Master_Data_Port = char_data;
	LCD_Master_Command_Port |= (1 << RS_Master);
	LCD_Master_Command_Port |= (1 << EN_Master);
	_delay_us(1);
	LCD_Master_Command_Port &= ~(1 << EN_Master);
	_delay_ms(1);
}

void LCD_String(char *str) {
	int i;
	for(i = 0; str[i] != 0; i++) {
		LCD_Char(str[i]);
	}
}

int main(void) {
	LCD_Init();
	LCD_String("Hey");
	while(1) {}
	return 0;
}
