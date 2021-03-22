

#include "Registr.h"


// Функция передачи данных в регистр
void registr(unsigned long data, unsigned char WriteOrErase)
{
	if(WriteOrErase == 1)
	tempdata = (tempdata|data);
	else
	tempdata &= ~(data);
	PORTD &= ~(1 << PD3); // ST_CP 0
	PORTD &= ~(1 << PD4); // SH_CP 0
	
	if(tempdata & 0x8000)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x4000)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x2000)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x1000)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x800)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x400)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x200)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x100)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x80)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x40)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x20)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x10)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x08)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x04)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x02)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD &= ~(1 << PD4); // SH_CP 0
	if(tempdata & 0x01)PORTD |= (1 << PD2);
	else PORTD &= ~(1 << PD2);
	PORTD |= (1 << PD4); // SH_CP 1
	PORTD |= (1 << PD3); // ST_CP 1
}

//Функция вывода тех.информации
void write_to_74HC595 (long l, unsigned char sl)
{
	if(l&0x40)   RUN1; else RUN0;         // Индикатор ПИТАНИЕ НОРМА  (LED 3)
	if(l&0x80)   RN1; else RN0;           // Индикатор ПУСК ДВИГАТЕЛЯ  (LED 4)
	if(l&0x100)  NORMAL1; else NORMAL0;   // Индикатор АВТО РЕЖИМ      (LED 5)
	if(l&0x200)  FL1; else FL0;           // Индикатор ПОЖАР  (LED 6)
	if(l&0x400)  C1; else C0;             // Индикатор ВЫХОД НА РЕЖИМ (LED 10)
	if(l&0x800)  D1; else D0;             // Индикатор Авария (LED 11)
	if(l&0x1000) F1; else F0;             // Индикатор L1(LED 8)
	if(l&0x2000) G1; else G0;             // Индикатор L2(LED 12)
	if(l&0x4000) H1; else H0;             // Индикатор L3(LED 9)
	if(l&0x8000) J1; else J0;             // Индикатор ТЕСТ(LED 7)

}
