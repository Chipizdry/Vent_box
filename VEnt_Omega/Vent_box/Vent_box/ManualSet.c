/*
 * ManualSet.c
 *
 * Created: 05.12.2020 20:03:51
 *  Author: Red
 */ 
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"
#include "ManualSet.h"

void ManualSet()
{
 NORMAL0;
 
 if((arm==0) && (PINB & 0b0010000)&&(working==0))// Кнопка отпущена и вентилятор отключен
 
 {
	 regim_fall=0;
	 
	 lcd_gotoxy(0, 0);
	 lcd_puts("PyАЅo№ PEЈҐM    "); //Ручной режим 
	 if((preority==0)&&(technic==0))
	 {  
		
		 pr();
		// volts();
	 }
	 if((preority==1)&&(technic>1))
	 {
		 lcd_gotoxy(0, 0);
		 lcd_puts("PyАЅo№ PEЈҐM    ");// Ручной режим 
		 
		 lcd_gotoxy(0,1);
		 lcd_puts("SIGNAL LINES ERR");
	 }
	 
	 
 }
 
 
 // ОБРАБОТКА КНОПКИ  РУЧНОГО ПУСКА
 //____________________________________________________________
 
 
 if((!(PINB & 0b0010000))&& (arm==0) &&(working==0))//Кнопка нажата
 
 {
	  J1;
	 arm=1;
	 _delay_ms(100);
	 milis=0; 
	 J0;
 }
 if((arm==1)  &&  (PINB & 0b0010000)&&(working==0))// Кнопка отпущена , вентилятор запущен в ручном режиме
 
 {
	 
	 working=1;
	 
	 if((preority==1)&&(technic>1))
	 {
		 lcd_gotoxy(0, 0);
		 
		 lcd_puts("   Manual START    ");
		
		 
	 }
	 
	 
	 RN1;
	 arm=0;
	 
	 
	 _delay_ms(20);
	 
 }
 
 //__________________Выключение вентилятора____________________________
 if((arm==0)  &&  (!(PINB & 0b0010000)) &&(working==1))//
 
 {
	 
	 arm=1;
	 J1;
	 _delay_ms(150);
	 J0;
 }
 
 if((arm==1)  && (PINB & 0b0010000) &&(working==1) )//
 
 {
	 working=0;
	 arm=0;
	 if ( (preority==0) &&(technic==0) )
	 {
		 lcd_gotoxy(0, 0);
		 lcd_puts("PyАЅo№ PEЈҐM    ");  // lcd_puts("  MANUAL  SET   ");
		
		// volts();
		//if((timing-time_loop)>90000) { pr();time_loop=timing;} 
	 }
	 
	 
	 if((preority==1)&&(technic>1))
	 {
		 lcd_gotoxy(0, 0);
		 lcd_puts("PyАЅo№ PEЈҐM    ");
		 //lcd_puts("  MANUAL  SET   ");
		 lcd_gotoxy(0,1);
		 lcd_puts("SIGNAL LINES ERR");
		 
	 }
	 RN0;
	 _delay_ms(20);
	 
 }
 
 if((arm==0)&&(working==1))// Кнопка отпущена , вентилятор запущен в ручном режиме ВЫВОД ИНФОРМАЦИИ НА ДИСПЛЕЙ
 
 {
	 int mcount=interval-milis;
	 if ( (preority==0)&&(technic==0)&&(interval > milis) )
	 
	 {
		  regim_fall=0;
		 lcd_gotoxy(0,0);
		 lcd_puts("PyАЅo№ Ё©CK іeЅї"); //Ручной пуск вентилятора
		 lcd_gotoxy(0,1);
		 lcd_puts("ЎoїoіЅocїД...");
		 
		 lcd_gotoxy(13, 1);
		 lcd_num_to_str(mcount/10, 2); // Выводим данные времени на LCD
		 lcd_gotoxy(15, 1);
		 lcd_num_to_str(mcount%100, 1);
	 }
	 if ( (preority==0)&&(technic==0)&&(interval <= milis) )
	 {
		 lcd_gotoxy(0,1);
		 lcd_puts("HeіГxoг Ѕa pe¶ёј"); //Невыход на режим 
		 regim_fall=1;
	 }
	 if ((preority==0) && (technic==1))
	 {
		 lcd_gotoxy(0,1);
		 lcd_puts("PaІoїa іeЅї-pa  ");
		  regim_fall=0;
	 }
	 
	 if((preority==0)&&(technic>1))
	 {
		 lcd_gotoxy(0,1); 
		 lcd_puts("AіapёЗ »ёЅёё PS!");  // Авария линии PS
	 }
	 
	 
	 
 }
 
}