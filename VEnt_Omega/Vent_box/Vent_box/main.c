


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
int k=5;
int past;
int past2;
int timing;

char read_enable = 0;




  //----------------Работа прерывателя таймера------------------------------------
  ISR(TIMER2_COMPA_vect){
	   PORTD|= (1 <<PD1); // Вспомогательная строб-индикация состояния 
	  timing++;
		 Omega_slave();  
		 start();
	 PORTD &=~ (1 <<PD1);  // Вспомогательная строб-индикация состояния  
  }
  
  ISR(TIMER1_COMPA_vect){
	  milis++;	  
  }

int main(void)
{  
	
	J1;
	
	ADCSRA|=(1<<ADEN);// разрешаем работу АЦП
	ADMUX &= (0 << REFS1);
	ADMUX|=(1 << REFS0); //выставляем опорное напряжение
	ADMUX |= ~(1 <<ADLAR);//Правостороннее выравнивание
	ADCSRA |=(0<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //частота предделителя 64
	ADCSRB |=0b00000000; //устанавливаем free running mode непрерывное преобразование 
	DIDR0 |= (1 << ADC4D)|(1 << ADC5D)|(1 << ADC2D)|(1 << ADC1D)|(1 << ADC0D); // Отключаем неиспользуемые цифровые входы
    ACSR |= (1 << ACD);//отключаем аналоговый компаратор
    // Настройка портов ввода/вывода
    DDRC = 0b00100000;
	DDRB = 0b00000010;
	PORTB= 0b00011000;
    DDRD = 0b11111110;
	PORTC= 0b00000000;
//_________________________________________________________________________________________________
/*
    TCCR0A	= 0x00;
	TCCR0B |= (0 << CS02)|(1 << CS01)|(0 << CS00)|(1 << WGM02); //предделитель clk/8, режим таймера СТС
	//TCCR0B |= (1 << CS12)|(0 << CS11)|(1 << CS10)|(1 << WGM12); //предделитель clk/128, режим таймера СТС
	TCNT0 = 0x00;
	OCR0A = 150; // максимальный предел счета
	TIMSK0 = (1 << OCIE0A); // разрешение прерывания по совпадению
	*/
	TCCR1A = 0x00;
	TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10)|(1 << WGM12); //предделитель clk/32, режим таймера СТС
	TCNT1 = 0x00;
	OCR1A = 15625; // максимальный предел счета
	TIMSK1 = (1 << OCIE1A); // разрешение прерывания по совпадению
	
	TCCR2A|=(1<<WGM21);
	TCCR2B |= (0 << CS22)|(1 << CS21)|(0 << CS20)|(0 << WGM22); //предделитель clk/8, режим таймера СТС
	TCNT2 = 0x00;
	OCR2A = 255; // максимальный предел счета
	TIMSK2 |= (1 << OCIE2A); // разрешение прерывания по совпадению
	
	
	
	
	
	_delay_ms(200);
	
	lcd_init(); // Инициализация дисплея
	
	write_to_lcd(0x01, 0); // Очищаем дисплей
	
	lcd_gotoxy(0, 0); // Выводим строки на LCD
	//lcd_puts("POWER__ON ");
	lcd_puts("ЁёїaЅёe BK§°«EHO");   //ПИТАНИЕ ВКЛЮЧЕНО
	
	meter();
	volts();
	
	PIND|=0b01000000;//Подсветка дисплея 
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
	delta_T=0;
	delta_H=0;
	pwr=0;
	timer_M=0;
	timer_U=0;
	test=0;
	faza_fall=0;
	revers=0;
	regim_fall=0;
	adress=19;
	device_ID=157;// 157-блок коммутации ,89-СПРА ,108-БСА
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
 adress=EEPROM_read(0x10);
 if(adress>128){adress=0;}
 delta_T=EEPROM_read(0x11);
 if(delta_T>62){delta_T=61;}
 delta_H=EEPROM_read(0x12);
 if(delta_H>100){delta_T=100;}
 dt1=EEPROM_read(0x13);//Гистерезис температуры целые градусы
 dt2=EEPROM_read(0x14);//Гистерезис температуры десятые доли градуса	 
 dh1=EEPROM_read(0x15);//Гистерезис влажности целые проценты
 dh2=EEPROM_read(0x16);//Гистерезис влажности десятые проценты
 dt=dt1+(dt2*0.1); 
 dh=dh1+(dh2*0.1);
 service=0;
 fire=read_adc(0); //Чтение состояния входа ПОЖАР
 preasure=read_adc(1); // Состояние входа ВЫХОД НА РЕЖИМ


volts();
meter();
status();
sei();
j=0;
J0;
    while (1) 
	
  {
	if(soft_start==0){ 
	current_adc();
	Alarm_line();
    PS500_line();    }
	#if(VENT_SYSTEM==1)
	current_adc();
	meter();
	status();
	Service();
	
	if (regim!=2){mode=1;}
	if (regim==2){mode=0;}
	if( ((voltage+delta_U)<100)||((faza+delta_F)<100) )
	{
		RUN0;
		pwr=0;
		timer_U=timing;
	}
	
	if(  ((voltage+delta_U)>=100)|| (delta_U>40) )
	{
		if(  ((faza+delta_F)>=100)|| (delta_F>40) )
		{
			pwr=1;
			RUN1;
		}
	}

	#endif
	
	
	
	#if(VENT_SYSTEM==2)
	meter();
	ServiceMenu();
	status();
	vent_status();
	//valve_status();
	if (regim!=2){mode=1;}
	if (regim==2){mode=0;}
	if((voltage+delta_U)<100)
	{
		RUN0;
		
		pwr=0;
	}
	
	if(((voltage+delta_U)>=100)||(delta_U>40))
	{
			pwr=1;
			RUN1;
	}
	

	#endif
	
	

		 //Рабочие режимы   
//================================================================================
		if (!(PINB & 0b001000)  && flag==0 && service==0) // кнопка нажата
		{
			
			J1;
			PIND|=0b01000000;//Подсветка дисплея 
			regim++;
			flag=1;
			arm =0;
			d=0;
			_delay_ms(30);
			working=0;
			RN0;
			if(regim>3)
			{
				
				regim=1;
			}
			EEPROM_write(0x01, regim);
			_delay_ms(10);
			J0;
		}
		
		if( (PINB & 0b0001000)   &&  flag==1 && service==0) // кнопка отпущена
		{
			arm =0;
			flag=0;
			_delay_ms(10);
		}
						
//-----------------------------------------------------------------------
		if(regim==1 && service==0)     //первый режим (ручной старт)		
		{   
			#if(VENT_SYSTEM==1)
			ManualSet();
			#endif	
			#if(VENT_SYSTEM==2)
			Manual();
			#endif
		}
//--------------------------------------------------------------------------------		
		if(regim==2 && service==0)//второй режим (АВТОМАТИЧЕСКИЙ старт)		
		{	
			#if(VENT_SYSTEM==1)
			AutoSet();	
			#endif
			#if(VENT_SYSTEM==2)
			AutoTemp();
			#endif
		}
//---------------------------------------------------------------------------------------		
		if(regim==3  && service==0 )//третий  режим (Запуск отключён)
		
		{  	
			lcd_gotoxy(0, 0);
			lcd_puts("¤aѕycє OTK§°«ўH     "); //Запуск отключён
			#if(VENT_SYSTEM==1)
			MenuStatus();	
			#endif
			
			#if(VENT_SYSTEM==2)
			StatusBarTemp();
			
			#endif
			NORMAL0;	
		}
//----------------------------------------------------------------------------------------		 		
	if (timing>1500000000)
	{   
		lcd_init(); // Инициализация дисплея
		
		write_to_lcd(0x01, 0); // Очищаем дисплей
		timing=0;
		past=0;
		past2=0;
	}
	
 }	
			
}

	