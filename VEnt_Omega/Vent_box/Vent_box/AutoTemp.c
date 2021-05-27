/*
 * AutoTemp.c
 *
 * Created: 22.02.2021 20:39:46
 *  Author: Red
 */ 
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"

void AutoTemp()
{
	NORMAL1;
	
 StatusBarTemp();
if((preority==0)&&(external==0))
{
		
	if((temp_alarm==1)||(hum_alarm==1)){
	 if(run_auto_relay==0)	{soft_start=1;}
		if((pwm_finish==1)&&(run_relay==0)){soft_start=0;blink=0;run_relay=1;RN1;}//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//RN1;
		lcd_gotoxy(0, 0);
		lcd_puts("Pa²o¿a ³e½¿-pa  ");	
		autorun=1;
	}
	
	
	if((temp_alarm==0)&&(hum_alarm==0)){
	   soft_start=0;      //////////////////////////////////////////////////////
	   run_auto_relay=0;  //////////////////////////////////////////////////////
	   blink=0;           //////////////////////////////////////////////////////
	   blink_detect=0;    //////////////////////////////////////////////////////
	   pwr_flag=0;        //////////////////////////////////////////////////////
	   pwm_finish=0;      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		RN0;
		lcd_gotoxy(0, 0);
		lcd_puts("ABTO   PE£¥M    ");
		autorun=0;	
	}
	
}

if((preority==2)||(external==1))
{	
	if((temp_alarm==1)||(hum_alarm==1)){
		lcd_gotoxy(0, 0);
		lcd_puts("¨ycº ¤A¨PEâ¢H   ");
	}
	if((temp_alarm==0)&&(hum_alarm==0)){
		RN0;
		lcd_gotoxy(0, 0);
		lcd_puts("ABTO   PE£¥M    ");
		autorun=0;
	}
	RN0;	
	
	 soft_start=0;      //////////////////////////////////////////////////////
	 run_auto_relay=0;  //////////////////////////////////////////////////////
	 blink=0;           //////////////////////////////////////////////////////
	 blink_detect=0;    //////////////////////////////////////////////////////
	 pwm_finish=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
}



if(preority==1)
{
	
	if((temp_alarm==1)||(hum_alarm==1)){
		 if(run_auto_relay==0)	{soft_start=1;}
		 if((pwm_finish==1)&&(run_relay==0)){soft_start=0;blink=0;run_relay=1;RN1;}//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//RN1;
		lcd_gotoxy(0, 0);
		lcd_puts("Pa²o¿a ³e½¿-pa  ");
		autorun=1;
	}
	
	if((temp_alarm==0)&&(hum_alarm==0)){
		soft_start=0;////////////////////////////////////////////////////
		run_auto_relay=0;//////////////////////////////////////////////////
		run_relay=0;////////////////////////////////////////////////////
		RN0;
		lcd_gotoxy(0, 0);
		lcd_puts("ABTO   PE£¥M    ");
		autorun=0;
	}
	
}

_delay_ms(10);	
	
	
}
	