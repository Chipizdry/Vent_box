


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "main.h"

int  volt_1, volt_2 ,volt_3;
int fire =0;                //пуск авто
int preasure=0;             //сработка датчика давления
unsigned char flag  =0;     //промежуточная переменная
unsigned char TypePS=0;
unsigned char TypeAL=0;
unsigned char preority=0;
unsigned char working=0;    //работа двигателя ручной режим
unsigned char autorun=0;    //работа двигателя авто режим
unsigned char technic=0;
int temperatur=0;
unsigned int tt=0; 
int d=0;
int k=5;
int past;
int past2;
int timing;
int mn_time;
int receivemode = 1;
char read_enable = 0;




  //----------------Работа прерывателя таймера------------------------------------
  ISR(TIMER0_COMPA_vect){
	   PORTD|= (1 <<PD1); // Вспомогательная строб-индикация состояния 
	  timing=timing+1;
	  Omega_slave();  
	 PORTD &=~ (1 <<PD1);  // Вспомогательная строб-индикация состояния  
  }
  
  ISR(TIMER1_COMPA_vect){
	  milis++;	  
  }

int main(void)
{
	
	ADCSRA|=(1<<ADEN);// разрешаем работу АЦП
	ADMUX &= (0 << REFS1);
	ADMUX|=(1 << REFS0); //выставляем опорное напряжение
	ADMUX |= ~(1 <<ADLAR);//Правостороннее выравнивание
	ADCSRA |=(0<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //частота предделителя
	ADCSRB |=0b00000000; //устанавливаем free running mode непрерывное преобразование 
	DIDR0 |= (1 << ADC4D)|(1 << ADC5D)|(1 << ADC2D)|(1 << ADC1D)|(1 << ADC0D); // Отключаем неиспользуемые цифровые входы
    ACSR |= (1 << ACD);//отключаем аналоговый компаратор
    // Настройка портов ввода/вывода
    DDRC = 0b00000000;
	DDRB = 0b00000010;
	PORTB= 0b00011000;
    DDRD = 0b11111110;
	PORTC= 0b00000000;
//_________________________________________________________________________________________________
    TCCR0A	= 0x00;
	TCCR0B |= (0 << CS02)|(1 << CS01)|(0 << CS00)|(1 << WGM02); //предделитель clk/8, режим таймера СТС
	//TCCR0B |= (1 << CS12)|(0 << CS11)|(1 << CS10)|(1 << WGM12); //предделитель clk/128, режим таймера СТС
	TCNT0 = 0x00;
	OCR0A = 255; // максимальный предел счета
	TIMSK0 = (1 << OCIE0A); // разрешение прерывания по совпадению
	
	TCCR1A = 0x00;
	TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10)|(1 << WGM12); //предделитель clk/32, режим таймера СТС
	TCNT1 = 0x00;
	OCR1A = 15625; // максимальный предел счета
	TIMSK1 = (1 << OCIE1A); // разрешение прерывания по совпадению
	
	
	J1;
	_delay_ms(200);
	J0;
	lcd_init(); // Инициализация дисплея
	
	write_to_lcd(0x01, 0); // Очищаем дисплей
	
	lcd_gotoxy(0, 0); // Выводим строки на LCD
	//lcd_puts("POWER__ON ");
	lcd_puts("ЁёїaЅёe BK§°«EHO");   //ПИТАНИЕ ВКЛЮЧЕНО
	
	meter();
	volts();
	J1;
	PIND|=0b01000000;
	//_delay_ms(1000);
	volts();
	
	arm =0; 
	interval=5;
	milis=0;
	regim=3;      //режим работы ручной-авто
	flag1=0;
    flag2=0;
	flag3=0;
	delta_U=0;
	delta_F=0;
	pwr=0;
	timer_U=0;
	test=0;
	faza_fall=0;
	revers=0;
	
	adress=19;
	device_ID=108;// 157-блок коммутации ,89-СПРА ,108-БСА
//===================================================================================================================================================	
 regim=  EEPROM_read(0x01);    // Актуальный Рабочий режим
 interval=EEPROM_read(0x02);   // Время ВЫХОДА НА РЕЖИМ
 k=EEPROM_read(0x03);          // ОТКЛОНЕНИЕ НАПРЯЯЖЕНИЙ
 TypePS=EEPROM_read(0x06);     // Тип входа PS (NC/NO)
 if(TypePS>1){TypePS=1;}       // Определение значений по умолчанию 
 TypeAL=EEPROM_read(0x07);     // Тип входа AL (NC/NO)
 if(TypeAL>1){TypeAL=1;}       // Определение значений по умолчанию
 delta_U=EEPROM_read(0x08);	 
 if(delta_U>42){delta_U=41;}       // Определение значений по умолчанию
 delta_F=EEPROM_read(0x09);
 if(delta_F>42){delta_F=41;}
 service=7;
 fire=read_adc(0); //Чтение состояния входа ПОЖАР
 preasure=read_adc(1); // Состояние входа ВЫХОД НА РЕЖИМ


volts();
meter();
status();
sei();
j=0;
J0;
    while (1) 
  {  current_adc();
	Alarm_line();
	PS500_line();
	meter();
	status();
	//dht_read();
	Service();
	if( ((voltage+delta_U)<100)||((faza+delta_F)<100) )
	{
		RUN0;
		timer_U=milis;
		pwr=0;
	}
	
    if(  ((voltage+delta_U)>=100)|| (delta_U>40) )
    {
		if(  ((faza+delta_F)>=100)|| (delta_F>40) )
		{
	   pwr=1;	
	   RUN1;
		}
     }

		 //Рабочие режимы   
//================================================================================
		if (!(PINB & 0b001000)  && flag==0 && service==7) // кнопка нажата
		{
			
			
			regim++;
			flag=1;
			arm =0;
			J1;
			_delay_ms(30);
			working=0;
			RN0;
			if(regim>3)
			{
				
				regim=1;
			}
			EEPROM_write(0x01, regim);
			_delay_ms(10);
			J1;
		}
		
		if( (PINB & 0b0001000)   &&  flag==1 && service==7) // кнопка отпущена
		{
			arm =0;
			flag=0;
			_delay_ms(10);
		}
		
				
//-----------------------------------------------------------------------
		if(regim==1 && service==7)     //первый режим (ручной старт)		
		{   
			ManualSet();
		}
//--------------------------------------------------------------------------------		
		if(regim==2 && service==7)//второй режим (АВТОМАТИЧЕСКИЙ старт)		
		{	
			AutoSet();	
		}
//---------------------------------------------------------------------------------------		
		if(regim==3  && service==7 )//третий  режим (Запуск отключён)
		
		{  	
			lcd_gotoxy(0, 0);
			lcd_puts("¤aѕycє OTK§°«ўH     "); //Запуск отключён
		
				d=0;
			lcd_gotoxy(0,1);   
				if((stat[0]==1)&&search==0 && test==0 && tt==0) {lcd_puts("!CёґЅa» ЁOЈAP_! ");search=1;tt=0;d=d+1;test=1;}
					if(stat[0]==0) test=1;
				if((stat[1]==1)&&search==0 && test==1 && tt==1) {lcd_puts("AіapёЗ ѕёїaЅёЗ  ");search=1;tt=1;d=d+1;test=2;}
					else test=2;
				if((stat[2]==1)&&search==0 && test==2 && tt==2) {lcd_puts("AіapёЗ іxoгa AL ");search=1;tt=2;d=d+1;test=3;}
					else test=3;
				if((stat[3]==1)&&search==0 && test==3 && tt==3) {lcd_puts("AіapёЗ іxoгa PS ");search=1;tt=3;d=d+1;test=4;}
					else test=4;
				if((stat[4]==1)&&search==0 && test==4 && tt==4) {lcd_puts("AіapёЗ 380B  (3)");search=1;tt=4;d=d+1;test=5;}
					else test=5;
				if((stat[5]==1)&&search==0 && test==5 && tt==5) {lcd_puts("AіapёЗ дa·ёpoієё");search=1;tt=5;d=d+1;test=6;}
					else test=6;
				if((stat[6]==1)&&search==0 && test==6 && tt==6) {lcd_puts("Peіepc дa· 380B ");search=1;tt=6;d=d+1;test=7;}
					else test=7;
				search=0;	
				if((stat[7]==0)&&search==0 && test==7 && tt==7 && d==0) {
					volts();
					
					
			
					
					search=1;tt=7;}
					
				 if (d==0) {tt=tt+1;}
				 if (tt>7) {tt=0;}
				 if (d>7) {d=0;}
				 if(test==7) test=0;	 
				 
				if( (!(PINB & 0b0010000)) && flag2==0) flag2=1;
				
				if( (PINB & 0b0010000) && flag2==1 ) 
				{
					J1;
					flag2=0;
					search=0;
					tt=tt+1;
					
					
					 _delay_ms(20);
					 J0;
				}
				
			NORMAL0;
			
		}
		 		
	J0;
	if (timing>1000000)
	{
		timing=0;
		past=0;
		past2=0;
	}
	
 }	
			
}

	