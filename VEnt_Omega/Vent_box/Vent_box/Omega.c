/*
 * Omega_slave_.c
 *
 * Created: 11.01.2021 19:22:31
 *  Author: Red
 */ 
 
 #include "Omega.h"
// #include "main.h"
 void Omega_slave() {
 
 
 PORTD|= (1 <<PD1); // Вспомогательная строб-индикация состояния 

   stats=(PINB & 0b0000001); //Чтение состояния входа

 if (( stats ==1)&&(bit_flag==0))
 {
	 
	 if((8<low)&& (low<11)){low=0;}    // интерпритация нуля
	 if((17<low)&& (low<21)){low=1;}   // интерпритация единицы
	 if((26<low)&& (low<35)){low=2;tct=0; input_bit=0;adress_t=0;directive=0;}  // команда начала приёма 
	 if(low>1000){tct=0; input_bit=0;adress_t=0;directive=0;low=0;external=0;}
	 detect[tct]=low;

	 
	 if (tct==8)
	 {
		 adress_t|= (detect[2]<<6)|(detect[3]<<5)|(detect[4]<<4)|(detect[5]<<3)|(detect[6]<<2)|(detect[7]<<1)|(detect[8]) ;
		 if(adress_t==0){adres_call=0;}
	 }
	 if (tct==13)
	 {
		 directive|=(detect[10]<<3)|(detect[11]<<2)|(detect[12]<<1)|(detect[13]) ;
	 }
	 
	 if((adress_t==adress)&&(tct==9)) {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}                 //   OWR в активном состоянии
	 if((adress_t==adress)&&(tct==14)&&((stat[0]==1)||(external==2))){  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //СОСТОЯНИЕ ТРЕВОГИ
	 if((adress_t==adress)&&(tct==30)&&(external==2)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}  //Активация режима ПОЖАР   
	// if((adress_t==adress)&&(tct==13)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
	 
	// if((adress_t==adress)&&((directive==3)||(directive==0))){
	 if((adress_t==adress)&&(tct==13)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
	 if((adress_t==adress)&&(tct==22)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
     if((adress_t==adress)&&(tct==31)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
     if((adress_t==adress)&&(tct==40)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
	 if((adress_t==adress)&&(tct==49)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}	
	 if((adress_t==adress)&&(tct==58)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}		 
	 if((adress_t==adress)&&(tct==67)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}	
	 if((adress_t==adress)&&(tct==76)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}	
	 //if((adress_t==adress)&&(tct==85)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}		 
	// }
	 if((adress_t==adress)&&(directive==3)&&(tct>=14)&&(tct<22))   //индентификатор устройства
	 {
		 temp_ID|=(device_ID>>(21-tct))&(0b1);
		 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  
		 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                
	 }
	 
	  if((adress_t==adress)&&(directive==3)&&(tct>=39)&&(tct<40))  //авария датчика 
	  {
		  temp_ID|=((receivemode)&(0b1));
		  if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  
		  if(temp_ID==0){  PORTB &=~ (1 <<PB1);}               
	  }
	 
	 /*
	  if((adress_t==adress)&&(directive==3)&&(external==2)&&(tct>=37)&&(tct<38))  //активация выхода
	  { 
		   PORTB |= (1 <<PB1); 
		   PORTC|= (1 <<PC5);   
	  }
	  */
	  if((adress_t==adress)&&(directive==3)&&(tct>=34)&&(tct<36))  //ручной режим (НЕ АВТО)
	  {
		  temp_ID|=((mode)&(0b1));
		  if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
		  if(temp_ID==0){  PORTB &=~ (1 <<PB1);}
	  }
	 
	 if((adress_t==adress)&&(directive==3)&&(tct>=51)&&(tct<57))  //состояние АЦП входа AL
	 {
		 temp_ID|=((fire/4)>>(57-tct))&(0b1);
		 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  
		 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                //{digitalWrite(13,LOW);}
	 }
	 
	 if((adress_t==adress)&&(directive==3)&&(tct>=69)&&(tct<76))  //состояние АЦП входа PS
	 {
		 temp_ID|=((preasure/4)>>(75-tct))&(0b1);
		 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
		 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                //{digitalWrite(13,LOW);}
	 }
	 
	 if((adress_t==adress)&&(directive==3)&&(tct>=60)&&(tct<67)) // температура 
	 {
		 temp_ID|=(tmp>>(66-tct))&(0b1);
		 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
		 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                //{digitalWrite(13,LOW);}
	 }
	 
	// relay|= (detect[32]<<13)|(detect[33]<<12)|(detect[34]<<11)|(detect[35]<<10)|(detect[36]<<9)|(detect[37]<<8)|(detect[38]<<7)|(detect[39]<<6) |(detect[40]<<5)|(detect[41]<<4)|(detect[42]<<3)|(detect[43]<<2)|(detect[44]<<1)|(detect[45]); 
	 /////////////////////////////////////////////////////////////////////////////////////
	  if((adress_t==adress)&&(directive==14)&&(tct==13)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  //{digitalWrite(13, HIGH);}
	  if((adress_t==adress)&&(directive==14)&&(tct==30)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);} 
	  if((adress_t==adress)&&(directive==14)&&(tct==45)){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);} 
	  if((adress_t==adress)&&(directive==14)&&(tct==46))   
	  {
		  if((detect[38]==1)&&(detect[45]==1)) {external=2;}
		  if((detect[37]==1)&&(detect[44]==1)) {external=0;}
	  }
	 //////////////////////////////////////////////////////////////////////////////////////////
	 
	 bit_flag=1;
	 hi_flag=0;
	 low=0;
	 temp_ID=0;
	 if((detect[1]==1)&&(detect[2]==0)&&(tct==2))
	 {
		 adres_call=adres_call+1;
		 if(adres_call==adress){
			 adress_t=adres_call;
			 
		{  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // digitalWrite(13, HIGH);
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
		  PORTC&=~ (1 <<PC5);
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

	 PORTD &=~ (1 <<PD1);  // Вспомогательная строб-индикация состояния 
	 
	 }