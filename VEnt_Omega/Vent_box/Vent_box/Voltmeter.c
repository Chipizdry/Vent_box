/*
 * Voltmeter.c
 *
 * Created: 30.11.2020 17:49:07
 *  Author: Red
 */ 

#include "Voltmeter.h"
#include "LCD.h"
#include "ADConverter.h"
//Вывод текущего значения напряжения

void volts()
{
	//int current_adc ();
	lcd_gotoxy(0, 1);
	lcd_puts("U");
	u =(u_curr -512)/1.414213*1.16;
	lcd_gotoxy(1, 1);
	lcd_num_to_str(u/10, 2); // Выводим данные АЦП1 на LCD
	lcd_gotoxy(3, 1);
	lcd_num_to_str(u%100, 1);
	current_adc ();
	lcd_gotoxy(4, 1);
	lcd_puts("__V");
	v =(v_curr -512)/1.414213*1.16;
	lcd_gotoxy(7, 1);
	lcd_num_to_str(v/10, 2); // Выводим данные АЦП2 на LCD
	lcd_gotoxy(9, 1);
	lcd_num_to_str(v%100, 1);
	current_adc ();
	lcd_gotoxy(10, 1);
	lcd_puts("__W");
	w =(w_curr -512)/1.414213*1.16;
	lcd_gotoxy(13, 1);
	lcd_num_to_str(w/10, 2); // Выводим данные АЦП3 на LCD
	lcd_gotoxy(15, 1);
	lcd_num_to_str(w%100, 1);
	
}