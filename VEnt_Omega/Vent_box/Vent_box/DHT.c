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
		
	}
	if(hum==0){test=test+1;}
		if (test>100){test=100;receivemode=1;}
			if (test<100){receivemode=0;}
	if(hum==1){test=test-1;}	
		if (test<4){receivemode=0;test=8;}
				
}


void pr()
{  
	 dht_read();
	lcd_gotoxy(0,1);              //перешли
	sprintf(buff,"Tmp%.1fC/Hm%.1f%%  ",tm,hd);
	lcd_puts(buff);
	
}
