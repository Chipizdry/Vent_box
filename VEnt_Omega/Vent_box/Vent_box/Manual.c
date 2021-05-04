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
#include "Omega.h"
int mcount;
int mn_tm;


void Manual()
{
	
	
	
	
	if((arm==0)&&(PINB & 0b0010000)&&(working==0))// Кнопка отпущена и вентилятор отключен
	 
	{  
		if(soft_start==0){blink=0;tk=0;run_status=0;run_relay=0;}
		NORMAL0;
		lcd_gotoxy(0, 0);
		lcd_puts("PyАЅo№ PEЈҐM    "); //Ручной режим	
		StatusBarTemp();
		soft_start=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		pwm_finish=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		_delay_ms(10);
	}
	
	
	// ОБРАБОТКА КНОПКИ  РУЧНОГО ПУСКА
	//____________________________________________________________
	
	
	if((!(PINB & 0b0010000))&& (arm==0) &&(working==0))//Кнопка нажата
	
	   {
		J1;
		arm=1;
		_delay_ms(70);
		J0;
	   }
	   	   
	if((arm==1)&&(PINB & 0b0010000)&&(working==0))// Кнопка отпущена , вентилятор запущен в ручном режиме
	
     	{   
			 		 
	 if((preority==0)&&(external==0))
		{ 
		   arm=0;
		   working=1;
		   autorun=1;
		   soft_start=1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		   pwm_finish=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		  // RN1;
		    _delay_ms(20);	
			
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
	if((arm==0)&&(!(PINB & 0b0010000)) &&(working==1))//Кнопка нажата 
	
	{	
		RN0;
		soft_start=0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		J1;
		arm=1;
		_delay_ms(150);
		J0;
	}
	
	if((arm==1)&&(PINB & 0b0010000)&&(working==1) )//Кнопка отпущена , вентилятор отключен
	
	  {
		  run_relay=0;
		  RN0;
		working=0;
		arm=0;
		lcd_gotoxy(0, 0);
		lcd_puts("PyАЅo№ PEЈҐM    "); 
		StatusBarTemp();
		
    	_delay_ms(20);
		autorun=0;
	  }
	
	if((arm==0)&&(working==1))// Кнопка отпущена , вентилятор запущен в ручном режиме ВЫВОД ИНФОРМАЦИИ НА ДИСПЛЕЙ
	
	{	
		if((pwm_finish==1)&&(run_relay==0)){soft_start=0;blink=0;run_relay=1;RN1;}//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		if((preority==0)&&(external==0))
		{
			//regim_fall=0;
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