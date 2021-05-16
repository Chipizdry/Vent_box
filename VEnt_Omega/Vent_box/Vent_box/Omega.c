/*
 * Omega_slave_.c
 *
 * Created: 11.01.2021 19:22:31
 *  Author: Red
 */ 
 
 #include "Omega.h"
 void Omega_slave() {
 
 
// PORTD|= (1 <<PD1); // Вспомогательная строб-индикация состояния 
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

	 if((adress_t==adress)&&(tct>=8)) {protocol();}
	 
	   
	 bit_flag=1;
	 hi_flag=0;
	 low=0;
	 temp_ID=0;
	 if((detect[1]==1)&&(detect[2]==0)&&(tct==2))
	  {
		 adres_call=adres_call+1;
		 if(adres_call==adress)
		    {
			 adress_t=adres_call;{  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);} 	          
		    }
	  }
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

//	 PORTD &=~(1 <<PD1);  // Вспомогательная строб-индикация состояния 
	 
	 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	 
	 void protocol(void)
	 {
		 if (tct==13)
		 {
			 directive|=(detect[10]<<3)|(detect[11]<<2)|(detect[12]<<1)|(detect[13]) ; //Определение типа запроса 
		 }
		 
		if(tct==9) {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //OWR в активном состоянии при запросе от ППКП  
		if(tct==13){  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //OWR в активном состоянии при запросе от программатора/ППКП
		if((tct==14)&&((stat[0]==1)||(external==2)))   {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //СОСТОЯНИЕ ТРЕВОГИ 
		 
		 
		if(tct>=13)
		{ 
			
			if(tct==22){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==31){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==40){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==49){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==58){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==67){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			if(tct==76){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
				
				
		  switch(directive)
		   {
			   
		   case 0 :
		   if(tct==9) {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}                 //OWR в активном состоянии при запросе от ППКП
		   if(tct==13){  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}                  //OWR в активном состоянии при запросе от программатора/ППКП   
		   if((tct==14)&&((stat[0]==1)||(external==2)))   {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //СОСТОЯНИЕ ТРЕВОГИ
			   
			   if(tct==22){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==31){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==40){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==49){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==58){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==67){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   if(tct==76){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
			   
		   break;
		   
		   case 2 :
		  
		   if(tct==13){  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}                  //OWR в активном состоянии при запросе от программатора/ППКП
		   if((tct==14)&&((stat[0]==1)||(external==2)))   {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //СОСТОЯНИЕ ТРЕВОГИ
		   break;
		   
		   case 3 :
		 
		   if(tct==13){  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}                  //OWR в активном состоянии при запросе от программатора/ППКП
		   if((tct==14)&&((stat[0]==1)||(external==2)))   {  PORTB|= (1 <<PB1); PORTC|= (1 <<PC5);}   //СОСТОЯНИЕ ТРЕВОГИ
		
		   if(tct==22){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации 
		   if(tct==31){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		   if(tct==40){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		   if(tct==49){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		   if(tct==58){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		   if(tct==67){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		   if(tct==76){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  // Импульс синхронизации
		
	   	   if((tct>=14)&&(tct<22))   //индентификатор устройства
			    {
				 temp_ID|=(device_ID>>(21-tct))&(0b1);
				 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}
			    }  
				
			if((tct==30)&&(tct<32))  //Активация выхода -тревога
			{
				temp_ID|=((external)&(0b1));
				if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				if(temp_ID==0){  PORTB &=~(1 <<PB1);}
			}	
				
				
				
		   if((tct>=34)&&(tct<36))  //ручной режим (НЕ АВТО)
			    {
				 temp_ID|=((mode)&(0b1));
				 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				 if(temp_ID==0){  PORTB &=~ (1 <<PB1);}
			    }
       ///////////////////////////////////////////////////////////////////////////// 
			if((tct>=36)&&(tct<40))  //Активация выхода -тревога
			{
				temp_ID|=((external)&(0b1));
				if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				if(temp_ID==0){  PORTB &=~(1 <<PB1);}
			}
		////////////////////////////////////////////////////////////////////////////		 
		/*	 
			if((tct>=42)&&(tct<46))  //Статус прибора.выходов
			{
				temp_ID|=((1)&(0b1));
				if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				if(temp_ID==0){  PORTB &=~(1 <<PB1);}
			}
				 
			if((tct>=49)&&(tct<50))  //авария датчика??????
			{
				temp_ID|=((1)&(0b1));
				if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				if(temp_ID==0){  PORTB &=~(1 <<PB1);}
			}
		*/	
				 
		   if((tct>=39)&&(tct<40))  //авария датчика DHT
			    {
				 temp_ID|=((receivemode)&(0b1));
				 if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				 if(temp_ID==0){  PORTB &=~(1 <<PB1);}
			    }   
			 
		   if((tct>=51)&&(tct<57))  //состояние АЦП входа AL
			    {
				  temp_ID|=((fire/4)>>(57-tct))&(0b1);
				  if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
				  if(temp_ID==0){  PORTB &=~ (1 <<PB1);}          
			    }
				
		   if((tct>=60)&&(tct<67)) // температура
				{
				  temp_ID|=(tmp>>(66-tct))&(0b1);
				  if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                  
				  if(temp_ID==0){  PORTB &=~ (1 <<PB1);}                
				}
		   if((tct>=69)&&(tct<76))  //состояние АЦП входа PS
			    {
				temp_ID|=((preasure/4)>>(75-tct))&(0b1);
				if(temp_ID==1){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                
				if(temp_ID==0){  PORTB &=~ (1 <<PB1);}               
			    } 
			   
		   break;
		   
		   case 14 :
		   if(tct==13){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}                 
		   if(tct==30){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
		   if(tct==45){  PORTB |= (1 <<PB1); PORTC|= (1 <<PC5);}
		   if(tct==46)
		   {
			   if((detect[35]==1)&&(detect[42]==1)) {J1;external=0;}
			   if((detect[36]==1)&&(detect[43]==1)) {J0;external=0;}
			   if((detect[38]==1)&&(detect[45]==1)) {external=1;}
			   if((detect[37]==1)&&(detect[44]==1)) {external=0;}
		   }
		   break;
		   
		 }
	  }
		 
 }

void start(void){
	/*
if(soft_start==1)
   {
  if(pwm_finish==0)

  {
	
    blink=blink+1;	
	if(blink<31496){tk=blink/400;}

    peak=0;	
    if(pwr_flag==0){peak=read_adc(6);}

    if((peak>=495)&&(peak<=(529))&&(pwr_flag==0)&&((blink-blink_detect)>69))
	{
	blink_detect=blink;
	pwr_flag=1;
	run_status=tk;
	RN1;	
    }
    
    if(pwr_flag==1)
	{
	if(run_status>0){run_status--;}
	if(run_status==0){RN0;pwr_flag=0;}
	}

    else{RN0;}
	if(blink>=31496){pwm_finish=1;RN1;}	
 }
	}
	
	*/
	if(soft_start==1)
	{
		if(pwm_finish==0)

		{
			
			blink=blink+1;
			if(blink<47244){tk=blink/600;}

			  peak=0;
			  if(pwr_flag==0){peak=read_adc(6);}

			  if((peak>=502)&&(peak<=522)&&(pwr_flag==0)&&((blink-blink_detect)>73))
			  {
				blink_detect=blink;
				pwr_flag=1;
				run_status=0;
				latch_1=0;
				RN0;
			  }
			
			  if((blink-blink_detect)>77){pwr_flag=0;}
			  if(pwr_flag==1)
			  {   
				run_status++;
				pwr_count=79-tk;
				if((run_status==pwr_count)&&(latch_1==0)){RN1;latch_1=1;}
				if(run_status>73){pwr_flag=0;};	
			  }

			  if(blink>=23622){pwm_finish=1;RN1;}
		}
	}
	
	
	
	
	
}
