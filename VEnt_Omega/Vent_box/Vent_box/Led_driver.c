/*
 * Led_driver.c
 *
 * Created: 30.11.2020 21:23:55
 *  Author: Red
 */ 
#include "Led_driver.h"

#if(VENT_SYSTEM==1) //Для систем ВД/ПД

void meter()
{
	lvl_1=0;
	lvl_2=0;
	lvl_3=0;
	revers=0;
	volts_level=0;
	faza_fall_1=0;
	faza_fall_2=0;
    al=0;
	measure=measure+1;
	u_1 =(u_curr -512)/1.414213*1.16;
	v_1 =(v_curr -512)/1.414213*1.16;
	w_1 =(w_curr -512)/1.414213*1.16;
	
	if( (u_1<(225-k)) || (u_1>(225+k)) )
	{
		
		lvl_1=0;
		if((timing-past2)<=7500)
		{
			F0;
		}
		
		if((timing-past2)>7500)
		{
			F1;
		}
		
	}

	else
	{
		lvl_1=1;
	}

	if( (v_1<(225-k)) || (v_1>(225+k)) )
	{
		
		lvl_2=0;
		if((timing-past2)<=7500)
		{
			G0;
		}
		
		if((timing-past2)>7500)
		{
			G1;
		}
	}
	else
	{
		lvl_2=1;
	}

	if( (w_1<(225-k)) || (w_1>(225+k)) )
	{
		
		lvl_3=0;
		if((timing-past2)<=7500)
		{
			H0;
		}
		
		if((timing-past2)>7500)
		{
			H1;
		}
		
	}

	else
	{
		lvl_3=1;
	}




	if((lvl_1==1)&&(lvl_2==1) &&(lvl_3==1))
	{
		volts_level=1;
		counter=counter+1;
	}
	
	if (volts_level==0)
	{   
		if (lvl_1==1)
		{F1;}
		if (lvl_2==1)
		{G1;}
		if (lvl_3==1)
		{H1;}
	}
	
	//------------------------------Реверс фазы ----------------------
	if (volts_level==1)
	{
		
		volt_1=0;
		volt_2=0;
		volt_3=0;

		volt_1=(int) read_adc(3);//6612
		_delay_us(6152);
		volt_2=(int) read_adc(6);//6612
		_delay_us(6152);
		volt_3=(int) read_adc(7);

		if( (   ( (volt_2>=(volt_1-k)) && (volt_2<=(volt_1+k)) ) && ( (volt_3>=(volt_2-k)) && (volt_3<=(volt_2+k)))  ))
		{
			revers=1;
			F1;
			G1;
			H1;
			faza_counter=faza_counter+1;
			
		}

		if(     ((volt_1-k)>(volt_2))  ||  ((volt_2)>(volt_1+k))  ||   (( volt_1+k)<(volt_3)) || ((volt_3)>(volt_1+k))   )
		{
			faza_fall_1=1;
		}

		volt_1=0;
		volt_2=0;
		volt_3=0;

		//--------------------------------------Вычисление реверса фазы--------------------------------------------------
		volt_1=(int) read_adc(3);
		_delay_us(6152);
		volt_2=(int) read_adc(7);
		_delay_us(6152);
		volt_3=(int) read_adc(6);
		
		if(     ((volt_1-k)>(volt_2))  ||  ((volt_2)>(volt_1+k))  ||   (( volt_1+k)<(volt_3)) || ((volt_3)>(volt_1+k))   )
		{
			faza_fall_2=1;
		}

		if( (   ( (volt_2>=(volt_1-k)) && (volt_2<=(volt_1+k)) ) && ( (volt_3>=(volt_2-k)) && (volt_3<=(volt_2+k)))  ))
		{
			revers=2;
			if(   ((timing-past2)<3750) && ((timing-past2)>0)  )
			{
				F0;
				G0;
				H0;
			}
			
			if(  ((timing-past2)>=3750)  &&  ((timing-past2)<7500)  )
			{
				F0;
				G0;
				H1;
			}
			
			if(  ((timing-past2)>=7500)  &&  ((timing-past2)<11500)  )
			{
				F0;
				G1;
				H0;
			}
			
			if(  ((timing-past2)>=11500)  &&  ((timing-past2)<15000)  )
			{
				F1;
				G0;
				H0;
			}
			
		}
		faza_fall=faza_fall_1*faza_fall_2;

		if( faza_fall==1)
		{
			if((timing-past2)<=2500)
			{
				F0;
				G0;
				H0;
			}
			
			if (((timing-past2)<=5000) && ((timing-past2) >2500) )
			{
				F1;
				G1;
				H1;
			}
			if(  ((timing-past2)<=7500) && ((timing-past2)>5000) )
			{
				F0;
				G0;
				H0;
			}
			if (((timing-past2)<=10000) && ((timing-past2) >7500) )
			{
				F1;
				G1;
				H1;
			}
			if(  ((timing-past2)<=12500) && ((timing-past2)>10000) )
			{
				F0;
				G0;
				H0;
			}
			if (((timing-past2)<=15000) && ((timing-past2) >12500) )
			{
				F1;
				G1;
				H1;
			}
			
			
		}


	}
	faza=faza_counter*100/measure;

	voltage=counter*100/measure;
	
	if(measure==100)
	{
		faza_counter=0;
		measure=0;
		counter=0;
		
	}
	
	
	if((timing-past2)>=15000)
	{
		past2=timing;
	}
		
}

void status()
{   
	if(preority==2) {stat[0]=1;}    //Сигнал ПОЖАР
	else {stat[0]=0;}                
	if(pwr==0) {stat[1]=1;}         //Авария питания
	else {stat[1]=0;}
	if(preority==1) {stat[2]=1;}    //Авария входа ПОЖАР
	else {stat[2]=0;}
	if(technic==2)  {stat[3]=1;}    //Авария входа датчика давления
	else {stat[3]=0;}
	if(volts_level==0) {stat[4]=1;} //Авария уровня напряжения 
	else {stat[4]=0;}
	if(faza_fall==1){stat[5]=1;}    //Авария очерёдности фаз(фазировки)
	else {stat[5]=0;}
	if(revers==2) {stat[6]=1;}      //Реверс фаз 
	else {stat[6]=0;}
	if(regim_fall==1) {stat[8]=1;} 	//Невыход на режим
	else {stat[8]=0;}	
	if(technic>2) {stat[9]=1;}   	//Ложная сработка датчика PS
	else {stat[9]=0;}	
		
    if(delta_F>40){stat[5]=0;} //игнор аварии фазировки 
	if(delta_U>40){stat[6]=0;} //игнор Реверса фаз 
for(int i=1; i<10; i++)
  {
	  al=al+stat[i];
	 
  }
        if(al==0) D0;
        if(al>0) D1;	
}
	
#endif

#if(VENT_SYSTEM==2) //Для систем ОВ
void meter()
{
	
	lvl_3=0;
	volts_level=0;
	al=0;
	measure=measure+1;
	
	w_1 =(w_curr -512)/1.414213*1.16;

	if( (w_1<(225-k)) || (w_1>(225+k)) )
	{
		
		lvl_3=0;
		if((timing-past2)<=7500)
		{
			RUN0;
		}
		
		if((timing-past2)>7500)
		{
			RUN1;
		}
		
	}

	else
	{
		lvl_3=1;
		volts_level=1;
		counter=counter+1;
		RUN1;	
	}

    volts_level=1;
	voltage=counter*100/measure;
	
	if(measure==100)
	{
		measure=0;
		counter=0;//??????????????????????????????????
		
	}
	
	
	if((timing-past2)>=15000)
	{
		past2=timing;
	}
	
}

void status()
{
	if(preority==2) {stat[0]=1;}    //Сигнал ПОЖАР
	else {stat[0]=0;}
	if(pwr==0) {stat[1]=1;}         //Авария питания
	else {stat[1]=0;}
	if(preority==1) {stat[2]=1;}    //Авария входа ПОЖАР
	else {stat[2]=0;}
	if(technic==2)  {stat[3]=1;}    //Авария входа датчика давления
	else {stat[3]=0;}
	if(volts_level==0) {stat[4]=1;} //Авария уровня напряжения
	else {stat[4]=0;}
	if(faza_fall==1){stat[5]=1;}    //Авария очерёдности фаз(фазировки)
	else {stat[5]=0;}
	if(revers==2) {stat[6]=1;}      //Реверс фаз
	else {stat[6]=0;}
	if(regim_fall==1) {stat[8]=1;} 	//Невыход на режим
	else {stat[8]=0;}
	if(technic>2) {stat[9]=1;}   	//Ложная сработка датчика PS
	else {stat[9]=0;}
	
	if(delta_F>40){stat[5]=0;} //игнор аварии фазировки
	if(delta_U>40){stat[6]=0;} //игнор Реверса фаз
	for(int i=1; i<10; i++)
	{
		al=al+stat[i];
		
	}
	if(al==0) D0;
	if(al>0) D1;
}

#endif