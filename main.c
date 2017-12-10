#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h> // Medium density 64 Kb kB flash
#include "vars.h"
#include "watch.h"
#include "bme280.h"
#include "usr232.h"

vu8 Cnt1mSec;	// Счетчик по 1 мсек.
vu8 Cnt100mSec;	// Счетчик по 100 мсек.
vu8 Cnt10mSec; // Счетчик по 10 мсек.
vu8 Cnt1Sec;	// Счетчик по 1 сек.
vu8 Cnt1Min;	// Счетчик по 1 мин.
vu8 FlTime;		// Флаг временных событий
vu8 CntTimeRxD;		// Счетчик таймаута.
vu8 COM_mode;
vu8 CntTimeRxUSR;
vu8 USR_mode;
vu8 Check; 
vu8 TimeCheck;	// Таймер
vu8 Event;  // после перезагрузки поменять пин или название
vu8 P;
vu8 wday;
vu8 sec;
vu8 min;
vu8 hour;
vu8 hourDec;
vu8 mday;
vu8 mon;
vu32 year;
vu32 us;
vu8 PWM;
vu16 Pill;
float press_f;

vu8 TimeForCO2; // Раз в 10 сек;

u8 del;
char namesend[30];
char pinsend[20];

vu8 BufFromSPI[20];
vu8 Buf2SPI[20];
vu8 PtrByteSPI;
vu8 CntByteSPI;
vu8 SPI_mode;
long temperature = 0;
long pressure = 0;
float press_f;
long humidity = 0;

ChanelType chList[ChanelCount]; // Список поддерживаемых каналов.
vu8 PackToReadCO2[]= {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
vu16 CO2;

int main(void)
{
	SystemInit();		// Инициализация периферии.
	InitPcktMan();
	WDR();
	Check=0;
	TimeCheck=0;
	vu8 i,j;
	P=0;
	vu32 time;
	unix_cal unix_time;

	Write8(BME280_REGISTER_SOFTRESET, 0xB6);
	vu32 r=100000;
	while(--r);	
	BMP280_Init();
	while(1)
	{	
		ADC1->CR2 |=BIT(ADC_SWSTART);	
		if(FlTime & BIT(1)){ //10 мсек
			FlTime &= ~BIT(1);
			WDR();
		}
		if(FlTime & BIT(2)){ //100 мсек
			FlTime &= ~BIT(2);	 
			if (++blink>10){blink=0;}
			*led=1;
			bmp280Convert(&temperature, &pressure, &humidity);
			pressure/=133;
			PacketCycle();
		}
		if(FlTime & BIT(3)){ //1 сек
			//ADC1->CR2 |=BIT(ADC_ADON);		// 
			
			FlTime &= ~BIT(3); 
		//	GPIOC->BSRR |= 0x100; // Led
			//*led=0;
			Checknwp();
			time = (u32)((RTC->CNTH << 16) | RTC->CNTL);
			timer_to_cal (time, &unix_time);
			wday = ((unix_time.wday/10)<<4)+(unix_time.wday-(unix_time.wday/10)*10);
			sec = ((unix_time.sec/10)<<4)+(unix_time.sec-(unix_time.sec/10)*10);
			min = ((unix_time.min/10)<<4)+(unix_time.min-(unix_time.min/10)*10);
			hour = ((unix_time.hour/10)<<4)+(unix_time.hour-(unix_time.hour/10)*10);
			mday = ((unix_time.mday/10)<<4)+(unix_time.mday-(unix_time.mday/10)*10);
			mon = ((unix_time.mon/10)<<4)+(unix_time.mon-(unix_time.mon/10)*10);
			year = ((unix_time.year/10)<<4)+(unix_time.year-(unix_time.year/10)*10);
			hourDec=unix_time.hour;
			
			if (++TimeForCO2>10) {
				TimeForCO2=0;
				for (i=0; i<sizeof(PackToReadCO2); i++){
					chList[chCOM].buffOUT[i] = PackToReadCO2[i];
				}
				chList[chCOM].ptrOUT=0;
				chList[chCOM].buffOUTLen=i;
				chList[chCOM].SendFunc();
				chList[chCOM].chState=0;
			}
			if (++ComTimeUSR>30) {
				FillBuff();
				ComTimeUSR=0;
				for (i=0; i<POST_Len; i++){
					chList[chUSR].buffOUT[i] = POST[i];
				}
				chList[chUSR].ptrOUT=0;
				chList[chUSR].buffOUTLen=i;
				chList[chUSR].SendFunc();
				chList[chUSR].chState=0;
			}
		}
		if(FlTime & BIT(4)){ //1 мин
			FlTime &= ~BIT(4);//BKP->DR1 |= BIT(0);
			//GPIOC->BSRR |= 0x00000100; 
		}		
	}
}