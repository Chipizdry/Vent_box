/*
 * ADConverter.h
 *
 * Created: 30.11.2020 17:34:57
 *  Author: Red
 */ 



#ifndef ADCONVERTER_H_
#define ADCONVERTER_H_

#include "main.h"

int  volt_1, volt_2 ,volt_3;
int u;
int v;
int w;
int u_curr,v_curr,w_curr;


int read_adc (unsigned char ch); // Функция чтения АЦП

int current_adc (); // Действующее значение АЦП

#endif /* ADCONVERTER_H_ */
