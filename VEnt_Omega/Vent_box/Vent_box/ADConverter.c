
#include "ADConverter.h"

// Функция чтения АЦП
int read_adc (unsigned char ch)
{
	ADMUX = ch; // Выбираем канал АЦП
	ADCSRA |= (1 << ADSC); // Запускаем преобразование
	while((ADCSRA & (1 << ADSC))); // Ждем окончания преобразования
	ADC=(ADCL|ADCH<<8);
	return(ADC); // Возвращаем значение АЦП
	ADCL=0;
	ADCH=0;
}

// Действующее значение АЦП
int current_adc ()
{
	u_curr=0;
	v_curr=0;
	w_curr=0;
	
fire=read_adc(0); //Чтение состояния входа ПОЖАР	
	for(int i=1;i<120;i++)
	{
		volt_1=(int) read_adc(3);
		
		if(u_curr <= volt_1)
		{
			u_curr =volt_1;
			
			if(u_curr <512)
			{
				u_curr=512;
			}
		}
		
		volt_2=(int) read_adc(7);
		
		if(v_curr <= volt_2)
		{
			v_curr = volt_2;
			
			if(v_curr <512)
			{
				v_curr=512;
			}
		}
		volt_3=(int) read_adc(6);
		
		
		if(w_curr <= volt_3)
		{
			w_curr =volt_3;
			
			if(w_curr <512)
			{
				w_curr=512;
			}
		}
		
	}
	return u_curr;
	return v_curr;
	return w_curr;
	return volt_3;
}