
#include "Service.h"
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"

void Service () {

 // Сервисный режим
 if ((PINB & 0b0100000)  && flag1==0 && regim==3) //Кнопка нажата
 {
	 J1;
	 service++;
	 flag1 =1;
	 _delay_ms(50);
	 lcd_gotoxy(0, 1); // Выводим строки на LCD
	 lcd_puts("                ");
	 if(service>7)
	 {
		 regim=3;
		 service=1;
	 }
	 EEPROM_write(0x00, service);
	 J0;
 }
 
 if (!(PINB & 0b0100000) && flag1==1  && regim==3  ) //Кнопка отпущена
 {
	 flag1=0;
	 _delay_ms(20);
 }
 
 if(service==1)
 
 {
	 lcd_gotoxy(0, 0); // Выводим строки на LCD
	 lcd_puts("Oїє»oЅeЅёe      ");//Отклонение амплитуд
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
		 flag2=0;
		 J1;
		 _delay_ms(10);
		 J0;
	 }
 }
 
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
	 
 }
 
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
 
 if(service==5)
 
 {	 
	 delta_U=EEPROM_read(0x08);
	 if(delta_U<=40)
	 {   
		 lcd_gotoxy(0, 0); // Выводим строки на LCD
		 lcd_puts("аoѕycїёјГ№      ");//Допустимый
		 lcd_gotoxy(0, 1); // Выводим строки на LCD
		 lcd_puts("ѕepeєoc дa· %");//Перекос фаз
		 	   
		 lcd_gotoxy(14, 1);
		 lcd_num_to_str(delta_U/10, 1); // Выводим данные времени на LCD
		 lcd_gotoxy(15, 1);
		 lcd_num_to_str(delta_U%100, 1);		 
	 }
	 if(delta_U>40)
	 { 
	     lcd_gotoxy(0, 0); // Выводим строки на LCD
		 lcd_puts("KoЅїpo»Д        ");//Контроль
		 lcd_gotoxy(0, 1); // Выводим строки на LCD
		 lcd_puts("ѕepeєoca дa· OTK");//перекоса фаз откл
		  
	 }
	 
	 
	 if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
	 {
		 J1;
		 delta_U=delta_U+2;
		 if(delta_U>42)
		 {
			 delta_U=0;
		 }

		 flag2=1;
		 EEPROM_write(0x08,delta_U);
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
	 
 }
 
 if(service==6)
 
 {
	    
	  delta_F=EEPROM_read(0x09); 
	  if(delta_F<=40)
	  {  
		  lcd_gotoxy(0, 0); // Выводим строки на LCD
		  lcd_puts("аoѕycїёјГ№      ");//Допустимый
		  lcd_gotoxy(0, 1); // Выводим строки на LCD
		  lcd_puts("cгіёґ дa·   % ");//сдвиг фаз
		    
		  lcd_gotoxy(14, 1);
		  lcd_num_to_str(delta_F/10, 1); // Выводим данные времени на LCD
		  lcd_gotoxy(15, 1);
		  lcd_num_to_str(delta_F%100, 1);
	  }
	  if(delta_F>40)
	  { 
		  lcd_gotoxy(0, 0); // Выводим строки на LCD
		  lcd_puts("KoЅїpo»Д        ");//Контроль
		  lcd_gotoxy(0, 1); // Выводим строки на LCD
		  lcd_puts("cгіёґa дa· OTK§ ");//сдвига фаз ОТКЛ
	  
	  }
	  
	  
	  if ((!(PINB & 0b001000))&&(flag2==0) )//кнопка выбора значения нажата
	  {
		  J1;
		  delta_F=delta_F+2;
		  if(delta_F>42)
		  {
			  delta_F=0;
		  }

		  flag2=1;
		  EEPROM_write(0x09,delta_F);
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
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	  	 	
			   if ((!(PINB & 0b010000))&&(flag2==0) )//кнопка выбора значения нажата
			   {
				   J1;
				  flag2=1;
				 
				   _delay_ms(20);
				   J0;
			   }
			   if ((PINB & 0b010000)&&(flag2==1) )
			   {
				   
				    J1;
				    volt_1=(int) read_adc(3);//6612
				    _delay_us(6416);
				    volt_2=(int) read_adc(6);//6612
				    _delay_us(6416);
				    volt_3=(int) read_adc(7);
				    
				    //int current_adc ();
				    lcd_gotoxy(0, 1);
				    lcd_puts("U");
				    u =(volt_1)/1.414213*1.16;
				    lcd_gotoxy(1, 1);
				    lcd_num_to_str(u/10, 2); // Выводим данные АЦП1 на LCD
				    lcd_gotoxy(3, 1);
				    lcd_num_to_str(u%100, 1);
				    current_adc ();
				    lcd_gotoxy(4, 1);
				    lcd_puts("__V");
				    v =(volt_2)/1.414213*1.16;
				    lcd_gotoxy(7, 1);
				    lcd_num_to_str(v/10, 2); // Выводим данные АЦП2 на LCD
				    lcd_gotoxy(9, 1);
				    lcd_num_to_str(v%100, 1);
				    current_adc ();
				    lcd_gotoxy(10, 1);
				    lcd_puts("__W");
				    w =( volt_3 -512)/1.414213*1.16;
				    lcd_gotoxy(13, 1);
				    lcd_num_to_str(w/10, 2); // Выводим данные АЦП3 на LCD
				    lcd_gotoxy(15, 1);
				    lcd_num_to_str(w%100, 1);
				    u=0;
				    v=0;
				    w=0;
				   flag2=0;
				  
				   _delay_ms(10);
				   J0;
			   }
///////////////////////////////////////////////////////////////////////////////////////			   
 }
 
}