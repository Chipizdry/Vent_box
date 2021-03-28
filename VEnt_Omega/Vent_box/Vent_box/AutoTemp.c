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
if( (preority==0)&&(external==0) )
{
	technic=0;
	lcd_gotoxy(0, 0);
	lcd_puts("ABTO   PE£¥M    ");
	 regim_fall=0;
	RN0;
	milis=0;
	autorun=0;
}

if((preority==2)||(external==2))
{
	autorun=1;
	RN1;
	
	
	
}


_delay_ms(10);	
	
	
}
	