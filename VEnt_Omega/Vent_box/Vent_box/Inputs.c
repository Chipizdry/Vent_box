


#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"
#include "main.h"

void Alarm_line()
{
	fire=read_adc(0); //Чтение состояния входа ПОЖАР
	if ((590<=fire)&&(fire  <=700)&&(TypeAL==1))
	{
		preority=2;
		
	}
	if((fire>=400)&&(fire<589)&&(TypeAL==0))
	
	{
		preority=2;

	}
	
	
	if((fire<400)||(fire>750)  ) //Авария входа ТРЕВОГА
	{
		preority=1;	
	}
	
	if((fire>=400)&&(fire<589)&&(TypeAL==1)) //Норма входа ТРЕВОГА
	{
		preority=0;
			
	}
	if ((590<=fire)&&(fire<=700)&&(TypeAL==0)) //Норма входа ТРЕВОГА
	{
		preority=0;
			
	}
}

void PS500_line()
{
	preasure=read_adc(1); //Чтение состояния входа Датчика давления
	if ((590<=preasure) && (preasure  <=700) && (TypePS==1)&& ((working==1)||(autorun==1))  ) //Сработка в рабочем режиме
	{
		technic=1;
		C1;
	}
	
	if((preasure>=400)&&(preasure<589) && (TypePS==0)&& ((working==1)||(autorun==1))  )  //Сработка в рабочем режиме
	{
		technic=1;
		C1;
	}
	
	if ((590<=preasure) && (preasure  <=700) &&(TypePS==1)&& ((working==0)&&(autorun==0))  ) //Сработка в режиме ожидания
	{
		technic=3;
		C1;	
	}
	
	if ((preasure>=400)&&(preasure<589) &&(TypePS==0)&& ((working==0)&&(autorun==0))  ) //Сработка в режиме ожидания
	{
		technic=3;
		C1;
	}
	
	
	
	if((preasure<400)||(preasure>750)) //Авария цепи датчика давления
	{
		technic=2;
		
		D1;//  Аткивация выхода АВАРИЯ
	}
	
	if((preasure>=400)&&(preasure<589) && (TypePS==1))  //Норма датчика
	{
		technic=0;
		C0;
	} 
	
	if ((590<=preasure) && (preasure<=700) && (TypePS==0)) //Норма датчика
	{
		technic=0;
		C0;
	}
		
}