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
int detect[80]={0,0,0,0,0};
int bffr[80];
ISR(TIMER0_COMPA_vect){
  digitalWrite(4,HIGH);
  
    
  timing++;
  stats = digitalRead(A5);
  if (( stats ==1)&&(bit_flag==0))
  {   
    
    if((8<low)&& (low<11)){low=0;}
    if((17<low)&& (low<21)){low=1;}
    if((26<low)&& (low<35)){low=2;tct=0;}
  
    detect[tct]=low; 
    bit_flag=1;
    hi_flag=0;
    low=0;
    if((detect[1]==1)&&(detect[2]==0)&&(tct>1)&&(tct<3)){adres_call=adres_call+1;digitalWrite(13, HIGH); }
    tct=tct+1;
  }
  
  
  if (( stats ==1)&&(bit_flag==1))
  {   
    active =active+1; 

    if(detect[1]==1){adres_call=adres_call+1;}
    if(31<=active)
      {
      low=3;
      detect[tct]=low;
      tct=tct+1;
      active=0;
      if((detect[0]==2)&&(tct>=2))
         {
         frame=tct;
         }
      }  
   }
  
  
  if (( stats ==0)&&(hi_flag==0))
  {
     digitalWrite(13,LOW);
    hi_flag=1;
    bit_flag=0; 
    active=0;
  }
  
  if (( stats ==0)&&(hi_flag==1))
  {
    active=0;
    low=low+1;
  }
  
   if((tct>=2)&&(frame==tct))
  {
    tct=0;
  
    for(int i=0;i<frame;i++)
  {
  bffr[i]=detect[i];
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
   PORTB= 0b00011000;
   DDRD = 0b11111110;
   PORTC= 0b00000000;
   Serial.begin(115200);
   pinMode(4, OUTPUT);           // назначить выводу порт ввода
   pinMode(A5,INPUT);
   pinMode(13, OUTPUT); 
   digitalWrite(13, LOW);       // вsключить подтягивающий резистор
   //digitalWrite(A5,HIGH);
    sei();
     OMEGA_DDR &= ~(1 << OMEGA_DQ); // вход
    while (1) 
    {
   for(int g=0;g<frame;g++)
   {// digitalWrite(13, HIGH); 
    
    Serial.print(g);
    Serial.print(":");
    Serial.println( bffr[g]);
     if(g==(frame-1)){Serial.println("ok"); rd=rd+1; Serial.print("Reset:");Serial.println(rd);}
   } 
   frame=0;
   // digitalWrite(13, LOW); 
 // Serial.println(stats);
    }
}
