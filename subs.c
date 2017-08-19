#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h>
#include "vars.h"


// Init system clock
void SystemInit(void)
{
	vu16 HSE_STARTUP_TIMEOUT=0x5000;
	vu32 StartUpCounter=0;
	
	vu32* pDest;
	CLI(); // Запрет всех прерываний
	
	for(pDest=(u32*)RAM_START;pDest<(u32*)RAM_END;pDest +=4) *(pDest)=0; 
	
	RCC->CR |= BIT(RCC_HSEON); // Enable HSE
	 do
  {
    StartUpCounter++;  
  } while(((RCC->CR & BIT(RCC_HSERDY)) == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
	
	 FLASH->ACR |= BIT(FLASH_PRFTBE) | BIT(FLASH_LATENCY0);
	    /* HCLK = SYSCLK */
   RCC->CFGR &= ~(0xFFFFFFFF);
	    /* PLL configuration = HSE * 3 = 24 MHz */
   RCC->CFGR |= BIT(RCC_PLLSRC) | BIT(RCC_PLLMUL0);
	 RCC->CR |= BIT(RCC_PLLON);
	 while((RCC->CR & BIT(RCC_PLLRDY)) == 0){}

	    /* Select PLL as system clock source */
   RCC->CFGR |= BIT(RCC_SW1);    
	 StartUpCounter=200;
   while(StartUpCounter--){NOP();}
	 
	RCC->APB1ENR |= BIT(RCC_PWREN) | BIT(RCC_BKPEN) | BIT(RCC_TIM7EN) | BIT(RCC_SPI2EN);  //Включить тактирование PWR и Backup, TIM7
	RCC->APB2ENR |= (BIT(RCC_IOPAEN)|BIT(RCC_IOPBEN)|BIT(RCC_IOPCEN));
	RCC->APB2ENR |= BIT(RCC_AFIOEN);
	RCC->APB2ENR |= BIT(RCC_USART1EN);
	 	 
	PWR->CR |= BIT(PWR_DBP);   		//Разрешить доступ к Backup области
	 // usart
	GPIOA->CRH &= ~(0x00F0); //clear PA.9 configuration-bit 
  GPIOA->CRH   |= (0x0BUL  << 4); //Tx (PA9) - alt. out push-pull

  GPIOA->CRH &= ~(0x0F00); //clear PA.10 configuration-bit 
  GPIOA->CRH   |= (0x04UL  << 8); //Rx (PA10) - floating
	 
	GPIOB->CRH &=~0xFFFFFFFF;
	GPIOB->CRL &=~0xFFFFFFFF;
	 
	GPIOB->CRH |= BIT(20) | BIT(21) | BIT(23); //SPIx_SCK PB13 Alternate function push-pull
	GPIOB->CRH |= BIT(28) | BIT(29) | BIT(31); //SPIx_MOSI PB15 Alternate function push-pull
	GPIOB->CRH |= BIT(25); //SPIx_MISO PB14 Input floating / Input pull-up
	GPIOB->CRH |= BIT(16) | BIT(17); //SPIx_NSS PB12 Not used. Can be used as a GPIO
	ResetCS();
	
	
	// SPI2 - разрешение работы. Режим мастер, 8 бит, MSB первый.
	SPI2->CR1 &= ~BIT(SPI_SPE);		// Запрет работы.
	SPI2->CR2 |=BIT(SPI_SSOE);		// NSS на аппаратный выход, иначе ерунда.
	SPI2->CR1 |=(BIT(SPI_MSTR)|BIT(SPI_BR1));		// Режим мастер, 60МГц/256=234 кГц.
	SPI2->CR1 &= ~(BIT(SPI_DFF));
	SPI2->CR1 |=BIT(SPI_SPE);		// Разрешена работа.
	 
	USART1->CR1 &= ~BIT(USART_UE); // выключим
	USART1->BRR =(APBCLK+BAUDRATE/2)/BAUDRATE; // (fck + baudrate /2 ) / baudrate. baudrate =9600;
	USART1->CR1 &= ~BIT(USART_PCE);		// none parity.
				// установка количества стоп битов.
	USART1->CR2 &= ~BIT(USART_STOP0);
	USART1->CR2 &= ~BIT(USART_STOP1);
	USART1->CR1 |= BIT(USART_TE) | BIT(USART_RE) | BIT(USART_UE); 	// включим
	USART1->CR1 |= BIT(USART_RXNEIE);
	
	vu8 i = USART1->DR;
	
	vu32 DR1=BKP->DR1;
	vu32 CR=BKP->CR;
	
  if (((RCC->BDCR & BIT(RCC_RTCSEN)) != BIT(RCC_RTCSEN))) //Проверка работы часов, если не включены, то инициализировать1
  {
  BKP->DR1 |= BIT(0);
  RCC->BDCR |= BIT(RCC_BDRST);  //Сбросить Backup область
		
  RCC->BDCR &= ~BIT(RCC_BDRST);
  RCC->BDCR |= BIT(RCC_RTCSEN) | BIT(RCC_RTCSEL0);   //Выбрать LSE источник (кварц 32768) и подать тактирование
  if ((RCC->BDCR & BIT(RCC_LSEON))!=BIT(RCC_LSEON)){
	RCC->BDCR |= BIT(RCC_LSEON);
	while ((RCC->BDCR & BIT(RCC_LSEON)) != BIT(RCC_LSEON)){} //Дождаться включения
	}  //Включить LSE
 
  BKP->RTCCR |= 3;                                         //калибровка RTC
  while (!(RTC->CRL & BIT(RTC_RTOFF)));                    //проверить закончены ли изменения регистров RTC
  RTC->CRL  |=  BIT(RTC_CNF);                              //Разрешить Запись в регистры RTC
  RTC->PRLL  = 0x7FFF;                                     //Настроит делитель на 32768 (32767+1)
  //RTC->CRL  &=  ~BIT(RTC_CNF);                             //Запретить запись в регистры RTC
  while (!(RTC->CRL & BIT(RTC_RTOFF)));                    //Дождаться окончания записи
  RTC->CRL &= (u16)~BIT(RTC_RSF);                      //Синхронизировать RTC
  while((RTC->CRL & BIT(RTC_RSF)) != BIT(RTC_RSF)){}         //Дождаться синхронизации
 // PWR->CR &= ~BIT(PWR_DBP);                                  //запретить доступ к Backup области
	unix_cal set_time;

	set_time.mday = 1;
	set_time.mon = 1;
	set_time.sec = 55;
	set_time.min = 16;
	set_time.hour = 00;
	set_time.wday = 2;
	set_time.year = 2017;
		
	RTC_SetCounter(cal_to_timer (&set_time));
	
  }
	PWR->CR &= ~BIT(PWR_DBP); 

	
			 		// TIM for Delay	T
	/*TIM7->DIER &= ~BIT(TIM6_UIE);
	TIM7->CR1 &= ~BIT(TIM6_CEN);
	TIM7->PSC = 24 - 1; // wtf? 30 было
	TIM7->CNT = 0;
	TIM7->ARR = 100;
	TIM7->DIER |= BIT(TIM6_UIE);
	TIM7->CR1 |= BIT(TIM6_CEN);*/
	
	NVIC->Enable[1] |= BIT(NVIC_USART1) | BIT(NVIC_SPI2);
	NVIC->Priority[9]=0; NVIC->Priority[9]=0x00300020; // USART1 - 3
//	NVIC->Priority[11]=0; NVIC->Priority[11]=0x00000500 // TIM7 - 5
	//   SysTick   
	STK->LOAD=0x5DC0-1;		//  24000
	STK->VAL=0x5DC0-1;        // 24000
	SCB->SHPR3 |=0xe0000000;		// Приоритет SysTick=14.
	STK->CTRL |=BIT(STK_ENABLE)|BIT(STK_TICKINT)|BIT(STK_CLKSOURCE);		// AHB.//
	
  // IWDG - запуск WDT.
	RCC->CSR |=BIT(RCC_LSION);		// Включить LSI для IWDG.
	IWDG->KR=0x5555;		// Ключ доступа к регистрам IWDG.
	IWDG->PR=2;		// Предделитель =/16, T=1,77 сек.
	IWDG->KR=0xcccc;		// Ключ запуска IWDG.
	
	GPIOC->CRH |= BIT(20); //c13 led
	
	GPIOA->CRL |= BIT(4); //a1
	GPIOA->CRL |= BIT(8); //a2
	GPIOA->CRL |= BIT(12); //a3
	GPIOA->CRL |= BIT(16); //a4
	GPIOA->CRL |= BIT(20); //a5
	GPIOA->CRL |= BIT(24); //a6
	GPIOA->CRL |= BIT(28); //a7
	
	GPIOB->CRL |= BIT(0); //b0
	GPIOB->CRL |= BIT(4); //b1
	GPIOB->CRL |= BIT(28); //b7
	GPIOB->CRH |= BIT(8); //b10
	GPIOB->CRH |= BIT(12); //b11
		GPIOA->CRL |= BIT(1); //b4
	SEI();		// Глобальное разрешение прерываний.
}


//=== Chanel init ===//
void InitPcktMan(void){
vu8 i;
	for(i=0;i<ChanelCount;i++){/*QSIn[i] = QSOut[i] = QSNum[i] = 0;*/} //
//	QRIn=QROut=QRNum=0;
	
	chList[chCOM].chanelID=chCOM;
	chList[chCOM].chState=0;
	chList[chCOM].buffOUTLen=0;
	chList[chCOM].SendFunc=SendToCOM;
}

//=== Send data ===//
void SendToCOM(void){
	USART1->CR1 &=  ~BIT(USART_RXNEIE);	// Disable RX int
	USART1->CR1 |= 	BIT(USART_TE);  		// Enable TX int
	USART1->DR = chList[chCOM].buffOUT[chList[chCOM].ptrOUT];
	USART1->CR1 |= 	BIT(USART_TXEIE);  		// Enable TX int
}

void PacketCycle(void){
	vu8 i,j,LenPack,Len,PackCRC;
	vu8 Buf[250]; 
	vu16 CalcCRC ;
	u8 aa,bb,R;
		for(i=0;i<ChanelCount;i++){
			if(chList[i].chState & chEnaData){
				
				/*for (j=0;j<chList[i].PakINLen;j++){
					chList[i].buffOUT[j] = chList[i].PakIN[j];
				}
				chList[chCOM].ptrOUT=0;
				chList[chCOM].buffOUTLen=j;
				chList[chCOM].SendFunc();
				*/
				PackCRC=0;
				for (j = 1; j < 8; j++) {PackCRC+=chList[i].PakIN[j];}
				PackCRC = 255 - PackCRC;
				PackCRC++;
				
				if (chList[i].PakIN[1]==0x86 && chList[i].PakIN[8]==PackCRC) {// Ответил MH-Z19
					CO2 = chList[i].PakIN[2] * 256 + chList[i].PakIN[3];
				}
				chList[i].chState=0;
			}
		}
		for(i=0;i<ChanelCount;i++){ // тут ответ
			//if(chList[i].chState & chEnaData){
			
			//}
		}
}
u16 crc16(vu8* pck, vu8 len){
	vu16  result;
	vu8 i, j;

	result = 0xFFFF;
	for (i = 0; i < (len - 2); i++)  {
		result ^= pck[i];
		for (j = 0; j < 8; j++) {
			if ((result & 0x01) == 1)
				result = (result >> 1) ^ 0xA001;
			else
				result >>= 1;
		}
	}
	return result;
}

vu8 itoa(s32 i, u8* bb){
    char const digit[] = "0123456789";
    char* p = bb;
    u8 j;
    j = 0;
    if(i<0){
        *p++ = '-';
        i *= -1;
        j++;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        j++;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return j;
}

void timer_to_cal (vu32 timer, unix_cal * unix_time)
{
	vu32 a;
	vu8 b;
	vu8 c;
	vu8 d;
	vu32 time;

	time = timer%SEC_A_DAY;
	a = ((timer+43200)/(86400>>1)) + (2440587<<1) + 1;
	a>>=1;
	unix_time->wday = a%7;
	a+=32044;
	b=(4*a+3)/146097;
	a=a-(146097*b)/4;
	c=(4*a+3)/1461;
	a=a-(1461*c)/4;
	d=(5*a+2)/153;
	unix_time->mday=a-(153*d+2)/5+1;
	unix_time->mon=d+3-12*(d/10);
	unix_time->year=100*b+c-4800+(d/10);
	unix_time->hour=time/3600;
	unix_time->min=(time%3600)/60;
	unix_time->sec=(time%3600)%60;
}

vu32 cal_to_timer (unix_cal * unix_time)
{
	vu8 a;
	vu32 y;
	vu8 m;
	vu32 Uday;
	vu32 time;

	a=((14-unix_time->mon)/12);
	y=unix_time->year+4800-a;
	m=unix_time->mon+(12*a)-3;
	Uday=(unix_time->mday+((153*m+2)/5)+365*y+(y/4)-(y/100)+(y/400)-32045)-2440588;
	time=Uday*86400;
	time+=unix_time->sec+unix_time->min*60+unix_time->hour*3600;
	return time;
}

void RTC_SetCounter(vu32 count)                                                    //Записать новое значение счетчика
{
 //RCC->APB1ENR |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;  //включить тактирование PWR и Backup
 //PWR->CR |= PWR_CR_DBP;                                                            //разрешить доступ к Backup области
 //while (!(RTC->CRL & RTC_CRL_RTOFF));                                         //проверить закончены ли изменения регистров RTC
 RTC->CRL |= BIT(RTC_CNF);;                                                          //Разрешить Запись в регистры RTC
 RTC->CNTH = count>>16;                                                              //записать новое значение счетного регистра
 RTC->CNTL = count;
 RTC->CRL &= ~ BIT(RTC_CNF);                                                      //Запретить запись в регистры RTC
 while (!(RTC->CRL & BIT(RTC_RTOFF)));                                         //Дождаться окончания записи
 //PWR->CR &= ~PWR_CR_DBP;                                                         //запретить доступ к Backup области
}
//=== Прочитать ответ из Радио  ===//
vu8 Read8(vu8 Com){
vu16 i;
	if(((SPI_mode & BIT(4)) && ((SPI_mode & BIT(7))==0)) || 1){		// М/сх Радио есть и канал не занят.
		Buf2SPI[0]=0;		// Данное.
		SetCS();		// Выставить /CS.
		SPI_mode |=BIT(7);		// Заняли канал.
		PtrByteSPI=0;
		CntByteSPI=1;		// Передадим 1 байт.
		SPI2->DR=Com;		// Команду выдаем.
		SetSPIIE();		// Разрешить прерывание.
		i=200;
		while((SPI_mode & BIT(7))&&(--i)) NOP();		// Ожидание конца.
		if(i==0){
			ResetSPIIE();		// Запретить прерывание.
			ResetCS();		// Снять /CS.
			*led=1;
			SPI_mode &= ~BIT(7);		// Освобождаем канал.
		}
		return (BufFromSPI[1]);
	}
	else return 0;
}

vu16 Read16(vu8 Com){
vu16 i;
		Buf2SPI[0]=0;		// Данное.
		Buf2SPI[1]=0;
		SetCS();		// Выставить /CS.
		SPI_mode |=BIT(7);		// Заняли канал.
		PtrByteSPI=0;
		CntByteSPI=2;		// Передадим 1 байт.
		SPI2->DR=Com;		// Команду выдаем.
		SetSPIIE();		// Разрешить прерывание.
		i=200;
		while((SPI_mode & BIT(7))&&(--i)) NOP();		// Ожидание конца.
		if(i==0){
			ResetSPIIE();		// Запретить прерывание.
			ResetCS();		// Снять /CS.
			*led=1;
			SPI_mode &= ~BIT(7);		// Освобождаем канал.
		}
	return ((BufFromSPI[2]<<8) | BufFromSPI[1]);
}

vu32 Read24(vu8 Com){
	vu32 ret;
	ret = (Read8(Com | 0x80)<<16) | (Read8((Com + 1) | 0x80)<<8) | (Read8((Com + 2) | 0x80));
	return (ret>>4);
}

void Write8(vu8 Com, vu8 Data){
vu16 i;
	if(((SPI_mode & BIT(4))&&((SPI_mode & BIT(7))==0))||1){		// М/сх Радио есть и канал не занят.
		Buf2SPI[0]=Data;		// Данное.
		SetCS();		// Выставить /CS.
		SPI_mode |=BIT(7);		// Заняли канал.
		PtrByteSPI=0;
		CntByteSPI=1;		// Передадим 1 байт.		
		Com &=~BIT(7);
				SPI2->DR=(Com);		// Команду выдаем.
				SetSPIIE();		// Разрешить прерывание.
		i=200;
		while((SPI_mode & BIT(7))&&(--i)) NOP();		// Ожидание конца.
		if(i==0){
			ResetSPIIE();		// Запретить прерывание.
			ResetCS();		// Снять /CS.
			SPI_mode &= ~BIT(7);		// Освобождаем канал.
		}
	}
}