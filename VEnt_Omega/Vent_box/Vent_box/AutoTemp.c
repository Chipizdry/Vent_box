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
if( (preority==0)&&(external==0)&&((technic==0)||(technic==1)) )
{
	technic=0;
	lcd_gotoxy(0, 0);
	lcd_puts("ABTO   PEЈҐM    ");
	 regim_fall=0;
//	volts();
	
/*	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	 if((PINB & 0b0010000)&& (j==1))
	 {  J1;
		 j=0;
		 _delay_ms(30);
		 
		 J0;
	 }
	 
	 if((!(PINB & 0b0010000))&& (j==0))
	 {
		 J1;
		 
		 volt_1=0;
		 volt_2=0;
		 volt_3=0;
		 

		 volt_1=(int) read_adc(7);//6612
		 _delay_us(6152);
		 volt_2=(int) read_adc(3);//6612
		 _delay_us(6152);
		 volt_3=(int) read_adc(6);
		 
		 lcd_gotoxy(0, 1);
		 lcd_puts("U");
		 
		 lcd_gotoxy(1, 1);
		 lcd_num_to_str(volt_1/10, 2); // Выводим данные АЦП1 на LCD
		 lcd_gotoxy(3, 1);
		 lcd_num_to_str(volt_1%100, 1);
		 
		 lcd_gotoxy(4, 1);
		 lcd_puts("__V");
		 
		 lcd_gotoxy(7, 1);
		 lcd_num_to_str(volt_2/10, 2); // Выводим данные АЦП2 на LCD
		 lcd_gotoxy(9, 1);
		 lcd_num_to_str(volt_2%100, 1);
		 
		 lcd_gotoxy(10, 1);
		 lcd_puts("__W");
		 
		 lcd_gotoxy(13, 1);
		 lcd_num_to_str(volt_3/10, 2); // Выводим данные АЦП3 на LCD
		 lcd_gotoxy(15, 1);
		 lcd_num_to_str(volt_3%100, 1);
		 j=1;
		 _delay_ms(10);
		 J0;
	 }
*/	///////////////////////////////////////////////////////////////////////////////////////
	RN0;
	milis=0;
	//working=0;
	autorun=0;
}
/*
if((preority==0)&&(technic>1)&&(external==0))
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
*/
if((preority==2)||(external==2))
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
		 regim_fall=0;
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
		regim_fall=1;
	}
	if((milis>=interval)&&(technic>1))
	{
		lcd_gotoxy(0,0);
		lcd_puts("PS LINE ERROR   ");	
		 regim_fall=0;	
	}
	
}
if((preority==1)&&(technic>1))
{
	lcd_gotoxy(0, 0);
	
	lcd_puts("ABTO   PEЈҐM    ");
	
	RN0;
	milis=0;
	autorun=0;
}

_delay_ms(10);	
	
	
}
	