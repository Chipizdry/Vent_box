/*
 * AirCond.c
 *
 * Created: 28.03.2021 19:35:12
 *  Author: Red
 */ 
#include "AirCond.h"

unsigned char ind_t=0;
unsigned char ind_h=0;

void vent_status(void){
	
	
	if((delta_T<=60)&&(delta_T>=-10)){
	if((tm>=delta_T)&&(ind_t==0)){
	ind_t=1;
	G1;//Светодиод L2/D12	
	 temp_alarm=1;
	}
	
	if((tm<=(delta_T-dt))&&(ind_t==1)){
    ind_t=0;
	G0;//Светодиод L2/D12	
	 temp_alarm=0;
	}
  }
 ////////////////////////////////////////////// 
  if(delta_H<=99){
	  if((hd>=delta_H)&&(ind_h==0)){
		  ind_h=1;
		  H1;//Светодиод L1/D8
		  hum_alarm=1;
	  }
	  
	  if((hd<=(delta_H-dh))&&(ind_h==1)){
		  ind_h=0;
		  H0;//Светодиод L1/D8
		  hum_alarm=0;
	  }
  }
		
	
}