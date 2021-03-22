/*
 * Omega_slave_.h
 *
 * Created: 11.01.2021 18:09:47
 *  Author: Red
 */ 


#ifndef OMEGA_H_
#define OMEGA_H_

#include "main.h"

int stats;
int active;
int low;
unsigned char bit_flag;
unsigned char hi_flag;
int tct;
int input_bit;
int adres_call;
long rd;


int adress_t;
int adress;
int directive;
int device_ID;// 157-блок коммутации ,89-СПРА ,108-БСА
int temp_ID;

int frame;
int answer;


int detect[145];




void Omega_slave();
void protocol();


#endif /* OMEGA(SLAVE)_H_ */