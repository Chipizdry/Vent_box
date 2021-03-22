/*
 * LCD.h
 *
 * Created: 30.11.2020 17:24:32
 *  Author: Red
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "main.h"
#include "registr.h"
// Функция установки курсора в указанную точку
#define lcd_gotoxy(x, y) write_to_lcd(0x80|((x)+((y)*0x40)), 0)


void lcd_init(void); // Функция инициализации LCD

void write_to_lcd(char p, unsigned char rs); // Функция передачи данных или команды в LCD

void lcd_puts(const char *str); // Функция вывода строки

void lcd_num_to_str(unsigned int value, unsigned char nDigit); // Функция вывода переменной

#define RS1 registr(0x01,1)
#define RS0 registr(0x01,0)

/* E */
#define E1 registr(0x02, 1)
#define E0 registr(0x02, 0)

/* D4 */
#define D41 registr(0x04, 1)
#define D40 registr(0x04, 0)

/* D5 */
#define D51 registr(0x08, 1)
#define D50 registr(0x08, 0)

/* D6 */
#define D61 registr(0x10, 1)
#define D60 registr(0x10, 0)

/* D7 */
#define D71 registr(0x20, 1)
#define D70 registr(0x20, 0)

#endif /* LCD_H_ */