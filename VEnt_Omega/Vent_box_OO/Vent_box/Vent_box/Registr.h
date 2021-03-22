/*
 * Register.h
 *
 * Created: 30.11.2020 17:17:39
 *  Author: Red
 */ 


#ifndef REGISTER_H_
#define REGISTER_H_
#include "main.h"

void registr(unsigned long data, unsigned char WriteOrErase); // Функция передачи данных в регистр
void write_to_74HC595 (long l, unsigned char sl); //Функция вывода тех.информации

volatile static unsigned long tempdata = 0;


/* FIRE ALARM*/
#define RUN1 registr(0x40, 1)
#define RUN0 registr(0x40, 0)

/* RUNING detector*/
#define RN1 registr(0x80, 1)
#define RN0 registr(0x80, 0)

/* START detector*/
#define NORMAL1 registr(0x100, 1)
#define NORMAL0 registr(0x100, 0)

/* RUN detector*/
#define FL1 registr(0x200, 1)
#define FL0 registr(0x200, 0)

/* PS-500*/
#define C1 registr(0x400, 1)
#define C0 registr(0x400, 0)

/* DDDDD*/
#define D1 registr(0x800, 1)
#define D0 registr(0x800, 0)

/* FFF*/
#define F1 registr(0x1000, 1)
#define F0 registr(0x1000, 0)

/* GGGG*/
#define G1 registr(0x2000, 1)
#define G0 registr(0x2000, 0)

/* HHHH*/
#define H1 registr(0x4000, 1)
#define H0 registr(0x4000, 0)

/* JJJJ*/
#define J1 registr(0x8000, 1)
#define J0 registr(0x8000, 0)

#endif /* REGISTER_H_ */