/*
 * Led_driver.h
 *
 * Created: 30.11.2020 21:23:20
 *  Author: Red
 */ 


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_
#include "ADConverter.h"

int counter;
int faza_counter;
int faza;
int measure;
int past;
int past2;
int u_1;
int v_1;
int w_1;
unsigned char lvl_1;
unsigned char lvl_2;
unsigned char lvl_3;
unsigned char volts_level;
unsigned char al;
void meter(void);
void status(void);

#endif /* LED_DRIVER_H_ */