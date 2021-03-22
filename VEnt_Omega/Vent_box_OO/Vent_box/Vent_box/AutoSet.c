
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"

void AutoSet()
{
NORMAL1;	


if( (preority==0)&&((technic==0)||(technic==1)) )
{
	technic=0;
	lcd_gotoxy(0, 0);
	//lcd_puts("AUTOMATIC SET   ");
	lcd_puts("ABTO   PEЈҐM    ");
	volts();
	
	RN0;
	milis=0;
	//working=0;
	autorun=0;
}
if((preority==0)&&(technic>1))
{
	lcd_gotoxy(0, 0);
	//lcd_puts("AUTOMATIC SET   ");
	lcd_puts("ABTO   PEЈҐM    ");
	
	lcd_gotoxy(0,1);
	//lcd_puts("PS LINE ERROR   ");
	lcd_puts("AіapёЗ »ёЅёё PS!");  // Авария линии PS
	
	RN0;
	milis=0;
	autorun=0;
}

if(preority==2)
{
	autorun=1;
	RN1;
	int tcount=interval-milis;
	
	if(technic==1)
	{
		C1;//Выход на режим 
		
		lcd_gotoxy(0,0);
		//lcd_puts("ENGINE START   ");
		lcd_puts("BГxoг Ѕa pe¶ёј  ");
		
	}
	
	if((milis<interval)&&(technic==0))
	{
		
		lcd_gotoxy(0,0);
		//lcd_puts("Waiting...   ");
		lcd_puts("ЎoїoіЅocїД..."); //Ожидание 
		
		lcd_gotoxy(13, 0);
		lcd_num_to_str(tcount/10, 2); // Выводим данные времени на LCD
		lcd_gotoxy(15, 0);
		lcd_num_to_str(tcount%100, 1);
		
	}
	
	if((milis>=interval)&&(technic==0))
	{	
		lcd_gotoxy(0,0);
		//	lcd_puts("ENGINE BREAK");
		lcd_puts("HeіГxoг Ѕa pe¶ёј");   //Невыход на режим 
		regim_fall=2;
	}
	if((milis>=interval)&&(technic>1))
	{
		lcd_gotoxy(0,0);
		lcd_puts("PS LINE ERROR   ");		
	}
	
}
if((preority==1)&&(technic>1))
{
	lcd_gotoxy(0, 0);
	lcd_puts("AUTOMATIC SET   ");
	//lcd_puts("ABTO   PEЈҐM  ");
	
	lcd_gotoxy(0,1);
	lcd_puts("SIGNAL LINES ERR");
	//	lcd_puts("AіapёЗ »ёЅёё PS!");  // Авария линии PS
	
	RN0;
	milis=0;
	autorun=0;
}

_delay_ms(10);

}