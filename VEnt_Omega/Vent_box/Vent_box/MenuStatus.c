/*
 * MenuStatus.c
 *
 * Created: 21.02.2021 17:35:20
 *  Author: Red
 */ 

#include "MenuStatus.h"
#include "Inputs.h"
#include "Registr.h"
#include "LCD.h"
#include "ADConverter.h"

#if(VENT_SYSTEM==1)
void MenuStatus(void)   //Äëÿ ñèñòåì ÂÄ/ÏÄ 
   {
	   
    
	lcd_gotoxy(0,1);
	tt=0;
	if(d==7){volts();}
	for(int m=d;m<7;m++)
	{
		
		if(stat[m]==1)
		{
			switch (m)
			{
				case 0 :
				lcd_puts("!C¸´½a» ¨O£AP_! ");
				tt=1;
				break;
				
				case 1 :
				lcd_puts("A³ap¸Ç ¾¸¿a½¸Ç  ");
				tt=1;
				break;
				
				case 2 :
				lcd_puts("A³ap¸Ç ³xoãa AL ");
				tt=1;
				break;
				
				case 3 :
				lcd_puts("A³ap¸Ç ³xoãa PS ");
				tt=1;
				break;
				
				case 4 :
				lcd_puts("A³ap¸Ç 380B     ");
				tt=1;
				break;
				
				case 5 :
				lcd_puts("A³ap¸Ç äa·¸po³º¸");
				tt=1;
				break;
				
				case 6 :
				lcd_puts("Pe³epc äa· 380B ");
				tt=1;
				break;
				
			}
			d=m;
			break;
		}
		
	}
	if (tt==0) {volts();d=0;}
	
	if( (!(PINB & 0b0010000)) && flag2==0) { flag2=1;}
	
	if( (PINB & 0b0010000) && flag2==1 )
	{
		J1;
		flag2=0;
		d=d+1;
		
		
		if(stat[d]==0)
		{
			
			for(int n=d;n<7;n++)
			{
				if(stat[n]==1) {d=n; break;}
			}
			
			if(d>7) d=0;
			_delay_ms(20);
			
		}
		J0;
		}
		
}	  

#endif

#if(VENT_SYSTEM==2)      //Äëÿ ñèñòåì ÎÂ

void StatusBarTemp(void)

{   
	
	 if(regim!=1)
	 
	 {
	
		lcd_gotoxy(0,1);
		tt=0;
		if(d==7){pr();}
		for(int m=d;m<7;m++)
		{
			
			if(stat[m]==1)
			{
				switch (m)
				{
					case 0 :
					lcd_puts("!C¸´½a» ¨O£AP_! ");
					tt=1;
					break;
					
					case 1 :
					lcd_puts("A³ap¸Ç ¾¸¿a½¸Ç  ");
					tt=1;
					break;
					
					case 2 :
					lcd_puts("A³ap¸Ç ³xoãa AL ");
					tt=1;
					break;
					
					case 3 :
					lcd_puts("A³ap¸Ç ³xoãa PS ");
					tt=1;
					break;
					
					case 4 :
					lcd_puts("A³ap¸Ç 380B     ");
					tt=1;
					break;
					
					case 5 :
					lcd_puts("A³ap¸Ç äa·¸po³º¸");
					tt=1;
					break;
					
					case 6 :
					lcd_puts("Pe³epc äa· 380B ");
					tt=1;
					break;
					
				}
				d=m;
				break;
			}
			
		}
		if (tt==0) {pr();d=0;}
		
		if( (!(PINB & 0b0010000)) && flag2==0) { flag2=1;}
		
		if( (PINB & 0b0010000) && flag2==1 )
		{
			J1;
			flag2=0;
			d=d+1;
			
			
			if(stat[d]==0)
			{
				
				for(int n=d;n<7;n++)
				{
					if(stat[n]==1) {d=n; break;}
				}
				
				if(d>7) d=0;
				_delay_ms(20);
				
			}
			J0;
		}
		}
		
	 if(regim==1)
		 
		 
	 {
			 
			 lcd_gotoxy(0,1);
			 tt=0;
			 if(d==7){pr();}
			 for(int m=d;m<7;m++)
			 {
				 
				 if(stat[m]==1)
				 {
					 switch (m)
					 {
						 case 0 :
						 lcd_puts("!C¸´½a» ¨O£AP_! ");
						 tt=1;
						 break;
						 
						 case 1 :
						 lcd_puts("A³ap¸Ç ¾¸¿a½¸Ç  ");
						 tt=1;
						 break;
						 
						 case 2 :
						 lcd_puts("A³ap¸Ç ³xoãa AL ");
						 tt=1;
						 break;
						 
						 case 3 :
						 lcd_puts("A³ap¸Ç ³xoãa PS ");
						 tt=1;
						 break;
						 
						 case 4 :
						 lcd_puts("A³ap¸Ç 380B     ");
						 tt=1;
						 break;
						 
						 case 5 :
						 lcd_puts("A³ap¸Ç äa·¸po³º¸");
						 tt=1;
						 break;
						 
						 case 6 :
						 lcd_puts("Pe³epc äa· 380B ");
						 tt=1;
						 break;
						 
					 }
					 d=m;
					 break;
				 }
				 
			 }
			 if (tt==0) {pr();d=0;}
			 
			 if( (PINB & 0b00100000) && flag2==0) { flag2=1;}
			 
			 if( (!(PINB & 0b00100000)) && flag2==1 )
			 {
				 J1;
				 flag2=0;
				 d=d+1;
				 
				 
				 if(stat[d]==0)
				 {
					 
					 for(int n=d;n<7;n++)
					 {
						 if(stat[n]==1) {d=n; break;}
					 }
					 
					 if(d>7) d=0;
					 _delay_ms(20);
					 
				 }
				 J0;
			 }
		 }
				
}

#endif