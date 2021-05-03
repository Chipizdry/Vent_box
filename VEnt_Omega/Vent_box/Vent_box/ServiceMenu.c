/*
 * ServiceMenu.c
 *
 * Created: 22.02.2021 21:11:14
 *  Author: Red
 */ 
#include <stdint.h>
#include <stdio.h>
#include "ServiceMenu.h"
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"
int menu_t=0;
void ServiceMenu () {
    
	// Сервисный режим
	if ((PINB & 0b0100000)  && flag1==0 && regim==3) //Кнопка нажата
	{
		J1;
	    timer_M=timing;
		service++;
		flag1 =1;
		_delay_ms(50);
		lcd_gotoxy(0, 1); // Выводим строки на LCD
		lcd_puts("                ");
		if(service>10)
		{
			regim=3;
			service=0;
		}
		EEPROM_write(0x00, service);
		J0;
	}
	
	if ((PINB & 0b0100000)  && flag1==1){
		menu_t=timing-timer_M;
		
		if(menu_t>4000){
			J1;
			timer_M=timing;
			regim=3;
			service=0;
			EEPROM_write(0x00, service);
			J0;
		}
	}
	
	
	if (!(PINB & 0b0100000) && flag1==1  && regim==3  ) //Кнопка отпущена
	{
		flag1=0;
		_delay_ms(20);
	}
	
	if(service==1)
	
	{
		lcd_gotoxy(0, 0); // Выводим строки на LCD
		lcd_puts("Oїє»oЅeЅёe(   V)");//Отклонение амплитуд
		
		w =(w_curr -512)/1.414213*1.16;
		lcd_gotoxy(11, 0);
		lcd_num_to_str(w, 3); // Выводим данные АЦП3 на LCD
		lcd_gotoxy(0, 1);
		lcd_puts("aјѕ»ёїyг,B+/-");
		lcd_gotoxy(14, 1);
		lcd_num_to_str(k/10, 1);
		lcd_gotoxy(15, 1);
		lcd_num_to_str(k%100, 1);
		
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{    J1;
			k=k+2;
			if(k>40)
			{
				k=0;
			}
			flag2=1;
			EEPROM_write(0x03,k);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{ 
			J1;
			flag2=0;
			_delay_ms(10);
			J0;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
      if ((!(PINB & 0b0010000))&&(flag2==0) )//кнопка выбора значения нажата
		  { 
			J1;
			k=k-2;
			if(k<0)
			{
				k=40;
			}
			flag2=1;
			EEPROM_write(0x03,k);
			_delay_ms(20);
			J0;
		  }
		
		
		if ((PINB & 0b001000)&&(flag2==1) )
		{  
			J1;
			flag2=0;
			_delay_ms(10);
			J0;
		}		
		
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(service==2)
	
	{
		
		lcd_gotoxy(0, 0); // Выводим строки на LCD
		lcd_puts("BpeјЗ іГxoгa    ");//Время выхода на режим
		lcd_gotoxy(0, 1);
		lcd_puts("Ѕa pe¶ёј,");
		lcd_gotoxy(12,1);
		lcd_puts("ceє.");
		
		
		interval=EEPROM_read(0x02);
		lcd_gotoxy(10, 1);
		lcd_num_to_str(interval/10, 1); // Выводим данные времени на LCD
		lcd_gotoxy(11, 1);
		lcd_num_to_str(interval%100, 1);
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			interval=interval+1;
			if(interval>20)
			{
				interval=0;
			}
			flag2=1;
			EEPROM_write(0x02,interval);
			
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if ((!(PINB & 0b0010000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			interval=interval-1;
			if(interval<0)
			{
				interval=20;
				
			}
			flag2=1;
			EEPROM_write(0x02,interval);
			
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b0010000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
		
		
		
		
		
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(service==3)
	
	{
		lcd_gotoxy(0, 0); // Выводим строки на LCD
		lcd_puts("Tёѕ гaїАёєa -PS");
		preasure=read_adc(1); //Чтение состояния входа датчик PS

		lcd_gotoxy(13, 1);
		lcd_num_to_str(preasure/10, 2); // Выводим данные АЦП1 на LCD
		lcd_gotoxy(15, 1);
		lcd_num_to_str(preasure%100, 1);
		
		if(TypePS==0)
		{
			lcd_gotoxy(0,1);
			lcd_puts("-NO-oїєpГї-");
		}
		if(TypePS==1)
		{
			lcd_gotoxy(0,1);
			lcd_puts("-NC-·aјєЅyї-");
		}
		
		if ((!(PINB & 0b001000)) &&(flag3==0) )//кнопка выбора значения нажата
		{
			
			J1;
			
			if((TypePS==0)&&(flag3==0))
			{   flag3=1;
				TypePS=1;
				lcd_gotoxy(0, 1);
				lcd_puts("-NC-·aјєЅyї-");
				EEPROM_write(0x06,TypePS);
				_delay_ms(50);
			}
			
			if((TypePS==1)&&(flag3==0))
			{   flag3=1;
				TypePS=0;
				lcd_gotoxy(0, 1);
				lcd_puts("-NO-oїєpГї-");
				EEPROM_write(0x06,TypePS);
				_delay_ms(50);
			}
			
			J0;
		}
		if ((PINB & 0b001000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(50);
			J0;
			
		}
		
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(service==4)
	
	{
		lcd_gotoxy(0, 0); // Выводим строки на LCD
		lcd_puts("Tёѕ гaїАёєa -AL");
		fire=read_adc(2); //Чтение состояния входа датчик AL

		lcd_gotoxy(13, 1);
		lcd_num_to_str(fire/10, 2); // Выводим данные АЦП1 на LCD
		lcd_gotoxy(15, 1);
		lcd_num_to_str(fire%100, 1);
		
		if(TypeAL==0)
		{
			lcd_gotoxy(0,1);
			lcd_puts("-NO-oїєpГї-");
		}
		if(TypeAL==1)
		{
			lcd_gotoxy(0,1);
			lcd_puts("-NC-·aјєЅyї-");
		}
		
		if ((!(PINB & 0b001000)) &&(flag3==0) )//кнопка выбора значения нажата
		{
			
			J1;
			
			if((TypeAL==0)&&(flag3==0))
			{   flag3=1;
				TypeAL=1;
				lcd_gotoxy(0, 1);
				lcd_puts("-NC-·aјєЅyї-");
				EEPROM_write(0x07,TypeAL);
				_delay_ms(50);
			}
			
			if((TypeAL==1)&&(flag3==0))
			{   flag3=1;
				TypeAL=0;
				lcd_gotoxy(0, 1);
				lcd_puts("-NO-oїєpГї-");
				EEPROM_write(0x07,TypeAL);
				_delay_ms(50);
			}
			
			J0;
		}
		if ((PINB & 0b001000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(50);
			J0;
			
		}
		
		
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(service==5)
	
	{
		delta_T=EEPROM_read(0x11);
		if((delta_T<=60)&&(delta_T>=-10))
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("Maєcёјa»ДЅaЗ    ");//Порог сработки 
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("їeј-pa,C      ");//датчика температуры
			
			lcd_gotoxy(14, 1);
			lcd_num_to_str(delta_T/10, 1); // Выводим данные времени на LCD
			lcd_gotoxy(15, 1);
			lcd_num_to_str((int)delta_T%100, 1);
			
		}
		
		if((delta_T>60)||(delta_T<-10))
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("KoЅїpo»Д        ");//Контроль
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("їeјѕ-pГ     OTK§");//температурного режима отключён 
			
		}
		
	/////////////////////////////////////////////////////////////////////////////////////////	
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
	        timer_M=timing;
			flag2=1;	
			delta_T=delta_T+2;
			if(delta_T>62)
			{
				delta_T=0;
			}

			EEPROM_write(0x11,delta_T);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			J1;
			
			flag2=0;
			_delay_ms(10);
			J0;
		}
/////////////////////.....////////////////////////
         if ((!(PINB & 0b001000))&&(flag2==1))//кнопка выбора значения нажата
         {
			 menu_t=timing-timer_M;
             
			 		 
			 if(menu_t>2000){
				 delta_T=delta_T+1;
				 timer_M=timing;
				 if(delta_T>62)
				 {
					 delta_T=0;
				 }

				 EEPROM_write(0x11,delta_T);	
			    }
			  
		 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if ((!(PINB & 0b010000))&&(flag3==0) )//кнопка выбора значения нажата
		{
			J1;
			delta_T=delta_T-1;
			if(delta_T<-10)
			{
				delta_T=0;
			}

			flag3=1;
			EEPROM_write(0x11,delta_T);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b010000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(10);
			J0;
		}
				
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	if(service==6)
	
	{
		
		delta_F=EEPROM_read(0x09);
		if(delta_H<=99)
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("Maєcёјa»ДЅaЗ    ");//Допустимая
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("і»a¶ЅocїД    %");//влажность 
			
			lcd_gotoxy(14, 1);
			lcd_num_to_str(delta_H/10, 1); // Выводим данные времени на LCD
			lcd_gotoxy(15, 1);
			lcd_num_to_str((int)delta_H%100, 1);
		}
		if(delta_H>99)
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("KoЅїpo»Д        ");//Контроль
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("і»a¶Ѕocїё   OTK§");//влажности ОТКЛ
			
		}
		
		
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			delta_H=delta_H+2;
			if(delta_H>100)
			{
				delta_H=0;
			}

			flag2=1;
			EEPROM_write(0x12,delta_H);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
		
		if ((!(PINB & 0b010000))&&(flag3==0) )//кнопка выбора значения нажата
		{
			J1;
			delta_H=delta_H-1;
			if(delta_H<0)
			{
				delta_H=100;
			}

			flag3=1;
			EEPROM_write(0x12,delta_H);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b010000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(10);
			J0;
		}
		
		
	}
	////////////////////////////////////////////////////////////////////////////////////////
	if(service==7)
	
	{
		if(delta_T>=61){service=service+1;}
			
		if((dt<=5.5)&&(delta_T<61))
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("Ўёcїepe·ёc      ");//Допустимая
			
			
			lcd_gotoxy(0,1);              //перешли
			sprintf(buff,"Tmp+/-   %.1fC      ",dt);
			lcd_puts(buff);
		}
		if(dt>5.5)
		{
			dt=0;		
		}
		
		
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			dt=dt+0.1;
			if(dt>5.5)
			{
				dt=0;
			}

			flag2=1;
			dt1=dt/1;
			dt2=((int)dt*10)%10;
			EEPROM_write(0x13,dt1);
			EEPROM_write(0x14,dt2);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
		
		if ((!(PINB & 0b010000))&&(flag3==0) )//кнопка выбора значения нажата
		{
			J1;
			dt=dt-0.1;
			if(dt<0)
			{
				dt=5.6;
			}

			flag3=1;
			EEPROM_write(0x13,dt1);
			EEPROM_write(0x14,dt2);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b010000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(10);
			J0;
		}
		
		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////
	if(service==8)
	
	{
		if(delta_H>=100){service=service+1;}
		
		if((dh<=10)&&(delta_H<100))
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("Ўёcїepe·ёc      ");//Допустимая
			
			
			lcd_gotoxy(0,1);              //перешли
			sprintf(buff,"Hm+/-  %.1f%%     ",dh);
			lcd_puts(buff);
		}
		if(dh>10)
		{
			dh=0;
		}
		
		
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			dh=dh+0.5;
			if(dh>10)
			{
				dh=0;
			}

			flag2=1;
			dh1=dh/1;
			dh2=((int)dh*10)%10;
			EEPROM_write(0x15,dh1);
			EEPROM_write(0x16,dh2);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
		
		if ((!(PINB & 0b010000))&&(flag3==0) )//кнопка выбора значения нажата
		{
			J1;
			dh=dh-0.5;
			if(dh<0)
			{
				dh=10;
			}

			flag3=1;
			EEPROM_write(0x15,dh1);
			EEPROM_write(0x16,dh2);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b010000)&&(flag3==1) )
		{
			J1;
			flag3=0;
			_delay_ms(10);
			J0;
		}
		
		
		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////
	if(service==9)
	
	{
		
		if(adress<128)
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("System_adres    ");//Допустимый
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("            ");//сдвиг фаз
			
			lcd_gotoxy(12, 1);
			lcd_num_to_str(adress/10, 2); // Выводим данные времени на LCD
			lcd_gotoxy(14, 1);
			lcd_num_to_str(adress%100, 1);
		}
		if(adress==128)
		{
			lcd_gotoxy(0, 0); // Выводим строки на LCD
			lcd_puts("Adress disable  ");//Контроль
			lcd_gotoxy(0, 1); // Выводим строки на LCD
			lcd_puts("        OTK§    ");//сдвига фаз ОТКЛ
			
		
		}
//////////////////////////////////////////////////////////////////////////////////////////
		
		if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			adress=adress+1;
			if(adress>128)
			{
				adress=0;
			}

           if(adress<0)
             {
	          adress=127;
             }

			flag2=1;
			EEPROM_write(0x10,adress);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b001000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
////////////////////////////////////////////////////////////////////////////////////////////////		
		
		if ((!(PINB & 0b0010000))&&(flag2==0) )//кнопка выбора значения нажата
		{
			J1;
			adress=adress-1;
			if(adress>128)
			{
				adress=0;
			}

            if(adress<0)
            {
	            adress=127;
            }
			  
			flag2=1;
			EEPROM_write(0x10,adress);
			_delay_ms(20);
			J0;
		}
		if ((PINB & 0b0010000)&&(flag2==1) )
		{
			flag2=0;
			J1;
			_delay_ms(10);
			J0;
		}
			
   }
	///////////////////////////////////////////////////////////////////////////////////////
	
	if(service==10)
	
	{
		lcd_gotoxy(0, 0); // Выводим строки на LCD
		lcd_puts("-TEST-TEST-TEST-");//Контроль
	
	if ((!(PINB & 0b001000))&&(flag2==0))//кнопка выбора значения нажата
	{
		
	  timer_M=timing;
	  J1;
	  RUN1;
	  RN1;
	  NORMAL1;
	  C1;
	  D1;
	  FL1;
	  G1;
	  H1;
	  F1;
	  _delay_ms(1000);
	  flag2=1;
	}
	
	if ((PINB & 0b001000)&&(flag2==1) )
	{
		
		menu_t=timing-timer_M;
		
		if(menu_t>6000){
		J1;
		_delay_ms(10);
		
		 RUN0;
		 RN0;
		 NORMAL0;
		 C0;
		 D0;
		 FL0;
		 G0;
		 H0;
		 F0;
		 J0;
		 flag2=0;
		}
	}
	
	}
}