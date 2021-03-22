


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
		//lcd_gotoxy(0,1);
		// lcd_puts("FIRE ALARM      ");
		//lcd_puts("!CёґЅa»_ЁOЈAP_! ");
		FL1;
	}
	if((fire>=400)&&(fire<589)&&(TypeAL==0))
	
	{
		preority=2;
		//lcd_gotoxy(0,1);
		// lcd_puts("FIRE ALARM      ");
		//lcd_puts("!CёґЅa»_ЁOЈAP_! ");
		FL1;
	}
	
	
	if((fire<400)||(fire>750)  ) //Авария входа ТРЕВОГА
	{
		preority=1;	
	}
	
	if((fire>=400)&&(fire<589)&&(TypeAL==1)) //Норма входа ТРЕВОГА
	{
		preority=0;
		FL0;
		
	}
	if ((590<=fire)&&(fire<=700)&&(TypeAL==0)) //Норма входа ТРЕВОГА
	{
		preority=0;
		FL0;
		
	}
}

void PS500_line()
{
	preasure=read_adc(1); //Чтение состояния входа Датчика давления
	if ((590<=preasure) && (preasure  <=700) &&   ((working==1)||(autorun==1))  ) //Сработка в рабочем режиме
	{
		technic=1;
		C1;
	}
	if ((590<=preasure) && (preasure  <=700) && ((working==0)&&(autorun==0))  ) //Сработка в режиме ожидания
	{
		technic=3;
		C1;
		
	}
	if((preasure<400)||(preasure>750)) //Авария цепи датчика давления
	{
		technic=2;
		
		D1;//  Аткивация выхода АВАРИЯ
	}
	
	if((preasure>=400)&&(preasure<589)  )  //Норма датчика
	{
		technic=0;
		C0;
	}
		
}