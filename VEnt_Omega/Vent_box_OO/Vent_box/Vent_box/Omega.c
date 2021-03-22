/*
 * Omega_slave_.c
 *
 * Created: 11.01.2021 19:22:31
 *  Author: Red
 */ 
 
 #include "Omega.h"
// #include "main.h"
 void Omega_slave() {
 
 
// PORTD|= (1 <<PD1); // Вспомогательная строб-индикация состояния 


 stats|=(PINB & 0b0000001)|(PINB & 0b0000100); //(PORTB & (1 << PINB0));      //Чтение состояния входа
 if (( stats ==1)&&(bit_flag==0))
 {
	 
	 if((8<low)&& (low<11)){low=0;}    // интерпритация нуля
	 if((17<low)&& (low<21)){low=1;}   // интерпритация единицы
	 if((26<low)&& (low<35)){low=2;tct=0; input_bit=0;adress_t=0;directive=0;}  // команда начала приёма 
	 
	 detect[tct]=low;

	 
	 if (tct==8)
	 {
		 adress_t|= (detect[2]<<6)|(detect[3]<<5)|(detect[4]<<4)|(detect[5]<<3)|(detect[6]<<2)|(detect[7]<<1)|(detect[8]) ;
		 if(adress_t==0){adres_call=0;}
	 }
	 if (tct==13)
	 {
		 directive|= (detect[9]<<4)|(detect[10]<<3)|(detect[11]<<2)|(detect[12]<<1)|(detect[13]) ;
	 }
	 
	 if((adress_t==adress)&&(tct==9)) {  PORTB|= (1 <<PB1);}                 //   OWR в активном состоянии
	 // if((adress_t==adress)&&(tct==14)){digitalWrite(13, HIGH);}//СОСТОЯНИЕ ТРЕВОГИ
	 
	 if((adress_t==adress)&&(tct==13)){  PORTB |= (1 <<PB1);}                  //{digitalWrite(13, HIGH);}
	 if((adress_t==adress)&&(tct==22)){  PORTB |= (1 <<PB1);}                  //{digitalWrite(13, HIGH);}
	 if((adress_t==adress)&&(directive==3)&&(tct>=14)&&(tct<22))
	 {
		 temp_ID|=(device_ID>>(21-tct))&(0b1);
		 if(temp_ID==1){  PORTB |= (1 <<PB1);}                  //{digitalWrite(13, HIGH);}
		 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                //{digitalWrite(13,LOW);}
	 };
	 bit_flag=1;
	 hi_flag=0;
	 low=0;
	 temp_ID=0;
	 if((detect[1]==1)&&(detect[2]==0)&&(tct==2))
	 {
		 adres_call=adres_call+1;
		 if(adres_call==adress){
			 adress_t=adres_call;
			 
		{  PORTB |= (1 <<PB1);}                  // digitalWrite(13, HIGH);
		  }}
		 tct=tct+1;
	 }
	 
	 
	 if (( stats ==1)&&(bit_flag==1))
	 {
		 active =active+1;
		 
	 }
	 
	 
	 if (( stats ==0)&&(hi_flag==0))
	 {
		  PORTB &=~ (1 <<PB1);                // digitalWrite(13,LOW);
		 
		 hi_flag=1;
		 bit_flag=0;
		 active=0;
		 input_bit=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	 }
	 
	 if (( stats ==0)&&(hi_flag==1))
	 {
		 
		 active=0;
		 low=low+1;
	 }

	 if((tct>=2)&&(frame==tct))
	 {
		 tct=0;
		 
		 input_bit=1;
		
	 }
		
	
	 //PORTD &=~ (1 <<PD1);  // Вспомогательная строб-индикация состояния 
	 
	 }