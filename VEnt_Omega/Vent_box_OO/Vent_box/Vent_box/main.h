


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU              16000000UL
//#define ONE_WIRE_PORT      PORTD
//#define ONE_WIRE_DDR       DDRD
//#define ONE_WIRE_PIN       PIND
//#define ONE_WIRE_DQ        7

#define DHT_PORT        PORTD
#define DHT_DDR         DDRD
#define DHT_PIN         PIND
#define DHT_BIT         7

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "Registr.h"
#include "ADConverter.h"
#include "LCD.h"
#include "EepromDATA.h"
#include "Voltmeter.h"
#include "Inputs.h"
#include "Led_driver.h"
#include "ManualSet.h"
#include "Service.h"
#include "AutoSet.h"
#include "Omega.h"
#include "DHT.h"



float hd;
float tm;
unsigned char hum;
uint8_t data[5];
unsigned char buff [16];  //буфер дисплея

int milis;
int interval;
int delta_U;
int delta_F;
int timer_U;
unsigned char arm;       //пуск ручной
int fire;
int pwr;  //Питание НОРМА 
unsigned char preority;
int preasure;
unsigned char technic;
unsigned char working;
unsigned char autorun;
unsigned char flag1;
unsigned char flag2;
unsigned char flag3;
int j;
int d;
unsigned char regim;      //режим работы ручной-авто
unsigned char service;
int stat[8];
unsigned char search;
unsigned char test;
unsigned char regim_fall;
unsigned char faza_fall;
unsigned char faza_fall_1;
unsigned char faza_fall_2;
unsigned char revers;




#endif /* MAIN_H_ */