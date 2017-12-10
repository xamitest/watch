#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h>
#include "watch.h"

#define On 1
#define Off 0

#define TimeTime 5 // Сек. отображения времени
#define TimeTemp 1 // Сек. отображения температуры
#define TimeHum 1  // Сек. отображения влажности
#define TimePres 1 // Сек. отображения давления
#define TimeCO2 1 // Сек. отображения CO2

#define TimePoll 2

vu8 TTime;
vu8 TTemp;
vu8 THum;
vu8 TPres;
vu8 Tco2;

vu8 nwp; // n work print Выбор режима отображения информации
vu8 ttp; // time to print
vu8 tpol; // time poll
vu8 hourzero;
vu16 blink;

void OutAll(vu8 seg1, vu8 seg2, vu8 seg3, vu8 seg4) // Вывод всех сегментов
{
	if (ttp==0) {
		OutSection(seg1);
		//*dp24_d=1;
		*DIG1=0; *DIG2=1; *DIG3=1; *DIG4=1;
		if (++tpol>=TimePoll) {tpol=0; ttp++; ClearAllSeg;	/*dp24_d=0;*/}		
	}
	else if (ttp==1) {
		OutSection(seg2);
		//*dp24_d=0;
		*DIG1=1; *DIG2=0; *DIG3=1; *DIG4=1;
		if (++tpol>=TimePoll) {tpol=0; ttp++; ClearAllSeg;}	
	}
	else if (ttp==2) {
		OutSection(seg3);
		//*dp24_d=1;
		*DIG1=1; *DIG2=1; *DIG3=0; *DIG4=1;
		if (++tpol>=TimePoll) {tpol=0; ttp++; ClearAllSeg;}
	}
	else if (ttp>=3) {
		OutSection(seg4);
		//*dp24_d=1;
		*DIG1=1; *DIG2=1; *DIG3=1; *DIG4=0;
		if (++tpol>=TimePoll) {tpol=0; ttp=0; ClearAllSeg;}	
	}
	CheckPoint(ttp, nwp);
}

void CheckPoint(u8 ttp, u8 who){
 if (who==0) { // Часы
	if (ttp == 1) {if(blink<5) {*dp24_d=0;} else {*dp24_d=1;}} else {*dp24_d=1;} // Часы с миганием 1.0
 } else if (who==1) { //temp
		if (ttp == 1) {*dp24_d=0;} else {*dp24_d=1;}
		} else {*dp24_d=1;}
    
}
	
void OutSection(vu8 i) // Вывод одной секции
{
	switch(i){
		case 0: *a=0; *b=0; *c=0; *d=0; *e=0; *f=0; *g=1;
			break;
		case 1: *b=0; *c=0; *a=1; *d=1; *e=1; *f=1; *g=1;
			break;
		case 2: *a=0; *b=0; *g=0; *e=0; *d=0; *c=1; *f=1;
			break;
		case 3: *a=0; *b=0; *c=0; *d=0; *g=0; *e=1; *f=1;
			break;
		case 4: *b=0; *c=0; *f=0; *g=0; *e=1; *a=1; *d=1;
			break;
		case 5: *a=0; *f=0; *g=0; *c=0; *d=0; *b=1; *e=1;
			break;
		case 6: *a=0; *f=0; *e=0; *d=0; *c=0; *g=0; *b=1;
			break;
		case 7: *a=0; *b=0; *c=0; *d=1; *e=1; *f=1; *g=1;
			break;
		case 8: *a=0; *b=0; *c=0; *d=0; *e=0; *f=0; *g=0;
			break;
		case 9: *a=0; *f=0; *g=0; *b=0; *c=0; *d=0; *e=1;
			break;
		case 'C': *a=0; *f=0; *e=0; *d=0; *b=1; *c=1; *g=1;
			break;
		case 'P': *a=0; *f=0; *e=0; *d=1; *g=0; *b=0; *c=1;
			break;
		case 'H': *b=0; *c=0; *e=0; *f=0; *g=0; *a=1; *d=1;
			break;
		case 't': *f=0; *e=0; *d=0; *g=0; *a=1; *b=1; *c=1;
			break;
		default: *a=1; *b=1; *c=1; *d=1; *e=1; *f=1; *g=1; // clear
			break;
	}
}

void Checknwp(void){ // в сек поллинг
	if (nwp==0) {	if (++TTime>TimeTime) {TTime=0; nwp=1; ClearAllSeg;}}
		else if (nwp==1){if (++TTemp>TimeTemp) {TTemp=0; nwp++; ClearAllSeg;}}
			else if (nwp==2){if (++THum>TimeHum) {THum=0; nwp++; ClearAllSeg;}}
				else if (nwp==3){if (++TPres>TimePres) {TPres=0; nwp++; ClearAllSeg;}}
					else if (nwp>=4){if (++Tco2>TimeCO2) {Tco2=0; nwp=0; ClearAllSeg;}}
				//	else {nwp=0;}
}

void Working(void){ // в микросек. поллинг
	u16 temp;
	u8 d4,d3,d2,d1;
	if (nwp==0) {
		hourzero=hour>>4;
		if(!hourzero) hourzero='X';
		OutAll(hourzero,hour&0x0F,min>>4,min&0x0F); // Time 
		//OutAll(min>>4,min&0x0F,(sec>>4),sec&0x0F); // Time
	}else if (nwp==1){
		temp=temperature;
		d4=temp/100;
		temp%=100;
		d3=temp/10;
		d2=temp%10;
		OutAll(d4,d3,d2,'C'); // Temp
	}else if (nwp==2){
			temp=humidity;
			d4=temp/10;
			d3=temp%10;
			OutAll(d4,d3,'X','H'); // Hum
	}else if (nwp==3){
				temp=pressure;
				d4=temp/100;
				temp%=100;
				d3=temp/10;
				d2=temp%10;
				OutAll(d4,d3,d2,'P'); // Pres
		}else if (nwp==4){
				temp=CO2;
				d4=temp/1000;
				temp = temp - d4*1000;
				d3=temp/100;
				temp%=100;
				d2=temp/10;
				d1=temp%10;
				if (CO2<9999 && CO2>100){
					if(!d4) d4='X';
					OutAll(d4,d3,d2,d1); // CO2
				}
				else {
					OutAll('E','E','E','E'); // CO2
					}
		}
}
