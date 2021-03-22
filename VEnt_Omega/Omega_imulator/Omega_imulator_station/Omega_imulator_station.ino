#include <avr/io.h>
#define F_CPU              16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OMEGA_PORT        PORTC
#define OMEGA_DDR         DDRC
#define OMEGA_PIN         PINC
#define OMEGA_DQ             5

int stats;
int timing=0;
int milis;
int active;
int low;
unsigned char bit_flag;
unsigned char hi_flag;
int tct;
int input_bit;
int adres_call;
long rd;
int frame=0;
int answer=0;
int retn=0;
int adress_t;
int adress=9;
int directive=0;
int device_ID=108;// 157-блок коммутации ,89-СПРА ,108-БСА
int temp_ID;
int result[145];
int out[145];
int detect[145]={0,0,0,0,0};
int bffr[145];
ISR(TIMER0_COMPA_vect){
  digitalWrite(4,HIGH);
  
    
  timing++;
  stats = digitalRead(A3);
  answer = digitalRead(A5);
  if (( stats ==1)&&(bit_flag==0))
  {   
    
    if((8<low)&& (low<11)){low=0;}
    if((17<low)&& (low<21)){low=1;}
    if((26<low)&& (low<35)){low=2;tct=0; input_bit=0;adress_t=0;directive=0;}
    
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
   
    if((adress_t==adress)&&(tct==9)){digitalWrite(12, HIGH);}

         // if((adress_t==adress)&&(tct==14)){digitalWrite(13, HIGH);}//СОСТОЯНИЕ ТРЕВОГИ 
    
    if((adress_t==adress)&&(tct==13)){digitalWrite(13, HIGH);}
    if((adress_t==adress)&&(tct==22)){digitalWrite(13, HIGH);}
    if((adress_t==adress)&&(directive==3)&&(tct>=14)&&(tct<22))
      {         
           temp_ID|=(device_ID>>(21-tct))&(0b1);
           if(temp_ID==1){digitalWrite(13, HIGH);} 
           if(temp_ID==0){digitalWrite(13,LOW);} 
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
            
            digitalWrite(13, HIGH); }}
    tct=tct+1;
  }
  
  
  if (( stats ==1)&&(bit_flag==1))
  {   
    active =active+1; 
     
     if(answer==1){retn=retn+1;}
     
  /*  if(23<=active)
      {
      low=3;
      detect[tct]=low;
      tct=tct+1;
     // active=0;
     // if((detect[0]==2)&&(tct>=2))
     //    {
     //    frame=tct;
     //    }
     
      }  
      */
   }
  
  
  if (( stats ==0)&&(hi_flag==0))
  {
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    hi_flag=1;
    bit_flag=0; 
    active=0;
    input_bit=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
  
  if (( stats ==0)&&(hi_flag==1))
  {
     if((retn<23)&&(retn>16))
     {
     result[tct]=1;
     }
    // else {result[tct]=0;}
    
    active=0;
    retn=0;
    low=low+1;
  }
  
   if((tct>=2)&&(frame==tct))
  {
    tct=0;
    
    input_bit=1;
    for(int i=0;i<frame;i++)
  {
    
  bffr[i]=detect[i];
  out[i]=result[i];
  result[i]=0;
  detect[i]=0;
  }
 
  }
  digitalWrite(4,LOW);
}

ISR(TIMER1_COMPA_vect){
  
  milis++;
   
}

int main(void)
{
  TCCR0A  = 0x00;
  TCCR0B |= (0 << CS12)|(1 << CS11)|(0 << CS10)|(1 << WGM12); //предделитель clk/1024, режим таймера СТС
  TCNT0 = 0x00;
  OCR0A = 255; // максимальный предел счета
  TIMSK0 = (1 << OCIE0A); // разрешение прерывания по совпадению
/*  
  TCCR1A = 0x00;
  TCCR1B |= (1 << CS12)|(0 << CS11)|(1 << CS10)|(1 << WGM12); //предделитель clk/32, режим таймера СТС
  TCNT1 = 0x00;
  OCR1A = 15625; // максимальный предел счета
  TIMSK1 = (1 << OCIE1A); // разрешение прерывания по совпадению
  */
    /* Replace with your application code */
   // Настройка портов ввода/вывода
   DDRC = 0b00000000;
   DDRB = 0b00000000;
   PORTB= 0b00000000;
   DDRD = 0b11111110;
   PORTC= 0b00001000;
   Serial.begin(230400);
   pinMode(4, OUTPUT);           // назначить выводу порт ввода
   pinMode(A5,INPUT);
   pinMode(A3,INPUT);
   pinMode(13, OUTPUT); 
   digitalWrite(13, LOW);       // вsключить подтягивающий резистор
   //digitalWrite(A3,HIGH);
    sei();
     OMEGA_DDR &= ~(1 << OMEGA_DQ); // вход
    while (1) 
    {

      
   for(int g=0;g<frame;g++)
   {
    
    Serial.print(g);
    Serial.print(":");
    if(out[g]==0)
    { Serial.println( bffr[g]);}
    if(out[g]==1)
    { Serial.print( bffr[g]);
  
     if((g==14)||(g==23)||(g==32)||(g==41)||(g==50)||(g==59)||(g==68)||(g==77)||(g==86)||(g==95))
      {
        Serial.println(";strobe");
      }
      else{ 
      Serial.print(";ans:");Serial.println( out[g]) ; }
      }
    
     if(g==(frame-1)){rd=rd+1;Serial.print("Adr:");Serial.println(adress_t);Serial.print("Cmd:");Serial.println(directive);Serial.print("Search:");Serial.println(adres_call); Serial.print("Rst:");Serial.println(rd);}
   } 
   
   frame=0;
   
    }
}
