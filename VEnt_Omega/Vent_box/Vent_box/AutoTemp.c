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
		RN1;
		lcd_gotoxy(0, 0);
		lcd_puts("Pa²o¿a ³e½¿-pa  ");	
	}
	
	if((temp_alarm==0)&&(hum_alarm==0)){
		RN0;
		lcd_gotoxy(0, 0);
		lcd_puts("ABTO   PE£¥M    ");	
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
	}
	RN0;	
}


_delay_ms(10);	
	
	
}
	