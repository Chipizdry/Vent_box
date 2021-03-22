/*
 * DHT.c
 *
 * Created: 18.01.2021 20:11:58
 *  Author: Red
 */ 

#include "DHT.h"
#include <stdint.h>
#include <stdio.h>

int read_dht_hum()   //функция чтения данных датчика
{
   
	unsigned char i,j;

	//=============MCU send START
	DHT_DDR|=(1<<DHT_BIT); //pin as output
	DHT_PORT&=~(1<<DHT_BIT); //0
	_delay_ms(18);
	DHT_PORT|=(1<<DHT_BIT); //1
	DHT_DDR&=~(1<<DHT_BIT); //pin as input
	//=============check DHT11 response
	_delay_us(50);
	if (DHT_PIN&(1<<DHT_BIT))
	{
		return 0;
	}
	_delay_us(80);
	if (!(DHT_PIN&(1<<DHT_BIT)))
	{
		return 0;
	}
	//===============receive 40 data bits
	
	
	
	 time_loop=timing;
	 /*
	 while ((DHT_PIN&(1<<DHT_BIT)));
	for (int x = 0; x<5; x++)     // принимать буду 5 байт по 8 бит:)
	{
		for (int z =8; z>0; z--)
		{
			while(!(PIND & (1<<PIND7)))   // датчик прижал вывод к земле , ждем логическую единицу на
			//выходе датчика
			{
			}

			_delay_us(45);                        // датчик выдал бит если 27 мс то 0 если 70 мс то 1, жду 45 мс
			if (PIND & (1<<PIND7))             // если после 45 мс на входе 1 то и в бит записываем единицу
			{
				data[x] |= (1<<(z-1));
			}
			else
			{
				data[x] |= (0<<(z-1));              // в противном случае у нас 0  пауза между битами у нас 50 мс
			}
			while (PIND & (1<<PIND7))       // здесь если после 45 мс была единица ждем её окончания
			{

			}
		}
	}
	return 1;
	*/
	 
	while ((DHT_PIN&(1<<DHT_BIT)));
	for (j=0; j<5; j++)
	{    
		
		   
		data[j]=0;
		for(i=0; i<8; i++)
		{
			
			while (!(DHT_PIN&(1<<DHT_BIT)));
			_delay_us (26);//30
			if (DHT_PIN&(1<<DHT_BIT))
			data[j]|=1<<(7-i);
			
			while ((DHT_PIN&(1<<DHT_BIT)));
		}
	}
  
	return 1;
	//DHT11 data[0]-humidity, data[2]-temperature
	//DHT22 data[0]-data[1]-humidity, data[2]-data[3]-temperature
	
	
	
}



void dht_read()
{
	hum=0;
//	cli();
	hum = read_dht_hum();
//	sei();
	if(hum==1)
	{
		 test=0;
		 check_sum=(data[0])+(data[1])+(data[2])+(data[3]);
		 tm= data[3]*0.1 + (data[2] & 0b01111111)*25.6;
		 tmp=data[3]*0.1 + (data[2] & 0b01111111)*25.6;
		 if (data[2] & 0b10000000)  tm*= -1;
		 if (data[2] & 0b10000000)  tmp*= -1;
		 hd=  data[1]*0.1 + data[0]*25.6;
		//check_sum=tm+hd;	
	}
	if(hum==0){test=test+1;}
		if (test>100){test=100;receivemode=1;}
			if (test<=100){receivemode=0;}
}


void pr()
{   dht_read();
	/*
	lcd_gotoxy(7,0);  
	
	lcd_num_to_str(check_sum, 4);
	
	lcd_gotoxy(12,0);
	
	lcd_num_to_str(data[4], 4);
	*/
	//if(check_sum==data[4])
	//{	
	lcd_gotoxy(0,1);              //перешли
	sprintf(buff,"Tmp%.1fC/Hm%.1f%%  ",tm,hd);
	lcd_puts(buff);
	//}
	
}
