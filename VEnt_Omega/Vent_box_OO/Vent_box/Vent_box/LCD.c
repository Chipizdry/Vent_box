/*
 * LCD.c
 *
 * Created: 30.11.2020 17:26:08
 *  Author: Red
 */ 
#include "LCD.h"



// Функция передачи данных или команды в LCD
void write_to_lcd(char p, unsigned char rs)
{
	if(rs == 1) RS1;
	else RS0;
	
	E1;
	if(p&0x10) D41; else D40;
	if(p&0x20) D51; else D50;
	if(p&0x40) D61; else D60;
	if(p&0x80) D71; else D70;
	E0;
	
	_delay_ms(2);
	
	E1;
	if(p&0x01) D41; else D40;
	if(p&0x02) D51; else D50;
	if(p&0x04) D61; else D60;
	if(p&0x08) D71; else D70;
	E0;
	
	_delay_ms(2);
}



// Функция инициализации LCD
void lcd_init(void)
{
	write_to_lcd(0x02, 0); // Курсор в верхней левой позиции
	write_to_lcd(0x28, 0); // Шина 4 бит, LCD - 2 строки
	write_to_lcd(0x0C, 0); // Разрешаем вывод изображения, курсор не виден
	write_to_lcd(0x01, 0); // Очищаем дисплей
}


// Функция вывода строки
void lcd_puts(const char *str)
{
	unsigned char i = 0;
	
	while(str[i])
	write_to_lcd(str[i++], 1);
}


// Функция вывода переменной
void lcd_num_to_str(unsigned int value, unsigned char nDigit)
{
	switch(nDigit)
	{
		case 4: write_to_lcd((value/1000)+'0', 1);
		case 3: write_to_lcd(((value/100)%10)+'0', 1);
		case 2: write_to_lcd(((value/10)%10)+'0', 1);
		case 1: write_to_lcd((value%10)+'0', 1);
	}
}