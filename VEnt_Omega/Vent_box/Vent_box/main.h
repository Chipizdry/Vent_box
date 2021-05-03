


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU              16000000UL

#define DHT_PORT        PORTD
#define DHT_DDR         DDRD
#define DHT_PIN         PIND
#define DHT_BIT         7

#define VENT_SYSTEM     2 //2

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
#include "Omega.h"
#include "DHT.h"
#include "MenuStatus.h"
#if(VENT_SYSTEM==1) 
#include "ManualSet.h"
#include "AutoSet.h"
#include "Service.h"
#endif

#if(VENT_SYSTEM==2)
#include "Manual.h"
#include "AutoTemp.h"
#include "ServiceMenu.h"
#include "AirCond.h"

#endif

float hd;
float tm;
float dh;
float dt;
int dh1;
int dt1;
int dh2;
int dt2;
unsigned char hum;
uint8_t data[5];
char buff [16];  //буфер дисплея
int mn_time;
int milis;
int millis;
int interval;
int delta_U;
int delta_F;
float delta_T;
float delta_H;
int timer_M;
int timer_U;
int timer_FLV;//Таймер положения клапана 
unsigned char flv_alarm;// ОЗК закрыт 
unsigned char temp_alarm;
unsigned char hum_alarm;
unsigned char arm;       //пуск ручной
int fire; //АЦП входа ПОЖАР
int run_status; //флаг подачи питания 
int peak; //Пиковое напряжение пуска
int tk; //коэффициент подачи питания
int blink; // переменная состояния задержки пуска
unsigned char soft_start; //Активация плавного пуска 
int pwr;  //Питание НОРМА 
unsigned char preority;
int preasure;//состояние входа PS
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
int stat[10];//Массив статуса аварий
int norm[10];// Массив статуса НОРМА
int test;//авария датчика DHT
unsigned char search;
unsigned char al;
unsigned char regim_fall;//невыход на режим 
unsigned char faza_fall;
unsigned char faza_fall_1;
unsigned char faza_fall_2;
unsigned char revers;
unsigned char time_loop;
unsigned char receivemode;// состояние аварии DHT датчика
unsigned char mode;
unsigned int tt; //вспомогательная переменная для динамического меню
unsigned char external;//внешняя тревога
int tmp; //температура в INT 
int relay;

#endif /* MAIN_H_ */