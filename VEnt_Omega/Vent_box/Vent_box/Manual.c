/*
 * Manual.c
 *
 * Created: 22.02.2021 20:23:06
 *  Author: Red
 */ 

#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"
#include "Manual.h"
int mcount;
int mn_tm;


void Manual()
{
	
	NORMAL0;
	
	if((arm==0)&&(PINB & 0b0010000)&&(working==0))// Кнопка отпущена и вентилятор отключен
	
	{
		
		lcd_gotoxy(0, 0);
		lcd_puts("PyАЅo№ PEЈҐM    "); //Ручной режим	
		StatusBarTemp();
	}
	
	
	// ОБРАБОТКА КНОПКИ  РУЧНОГО ПУСКА
	//____________________________________________________________
	
	
	if((!(PINB & 0b0010000))&& (arm==0) &&(working==0))//Кнопка нажата
	
	   {
		J1;
		arm=1;
		_delay_ms(70);
		milis=0;
		J0;
	   }
	   
	   
	if((arm==1)&&(PINB & 0b0010000)&&(working==0))// Кнопка отпущена , вентилятор запущен в ручном режиме
	
     	{   
			 		 
	 if((preority==0)&&(external==0))
		{
		   working=1;
		   soft_start=1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		   //RN1;
		   arm=0;
		    _delay_ms(20);	
			autorun=1;
		}
		
		if((preority==2)||(external==1))
		{
			working=1;
			RN0;
			soft_start=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			 arm=0;
			lcd_gotoxy(0, 0);
			lcd_puts("Ёycє ¤AЁPEвўH   ");
			 _delay_ms(20);
			 autorun=0;
		}
		
		
		
		
		
     }
	
	//__________________Выключение вентилятора____________________________
	if((arm==0)  &&  (!(PINB & 0b0010000)) &&(working==1))//
	
	{	
		arm=1;
		J1;
		_delay_ms(150);
		J0;
	}
	
	if((arm==1)&&(PINB & 0b0010000)&&(working==1) )//
	
	  {
		working=0;
		arm=0;
		lcd_gotoxy(0, 0);
		lcd_puts("PyАЅo№ PEЈҐM    "); 
		StatusBarTemp();
		soft_start=0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    RN0;
    	_delay_ms(20);
		autorun=0;
	  }
	
	if((arm==0)&&(working==1))// Кнопка отпущена , вентилятор запущен в ручном режиме ВЫВОД ИНФОРМАЦИИ НА ДИСПЛЕЙ
	
	{	
		
		if((preority==0)&&(external==0))
		{
			regim_fall=0;
			lcd_gotoxy(0,0);
			lcd_puts("PyАЅo№ Ё©CK іeЅї"); //Ручной пуск вентилятора	
			StatusBarTemp();
		}
		
		if((preority==2)||(external==1))
		{
			
			RN0;
			soft_start=0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			lcd_gotoxy(0, 0);
			lcd_puts("Ёycє ¤AЁPEвўH   ");
			autorun=0;
			StatusBarTemp();
		}
					
	}
	
}