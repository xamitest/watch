#ifndef _vars_h
#define _vars_h
#include <cortexm3_macro.h>
#include "bme280.h"

#define RAM_START 0x20000000
#define RAM_END 	0x20002000

#define BitBanding(Register, Bit_number, Reg_base, BB_base) ((vu32*) ((BB_base) + ((((vu32) &(Register)) - ((Reg_base)))<<5) + ((Bit_number)<<2)))
#define Peripheral_BB(Register, Bit_number) BitBanding(Register, Bit_number, PERIPH_BASE, PERIPH_BB_BASE)

#define led Peripheral_BB(GPIOC->ODR, 13)

#define APBCLK 		24000000UL
#define BAUDRATE  9600
#define BAUDRATEusr232 115200
#define MaxPacketLen 255
#define chCOM 0 // bluetooth
#define chUSR 1 // usr232
#define ChanelCount 3


extern vu8 CntTimeRxD;		// Счетчик таймаута.
extern vu8 COM_mode;
extern vu8 CntTimeRxUSR;		// Счетчик таймаута.
extern vu8 USR_mode;
extern vu8 Cnt1mSec;	// Счетчик по 1 мсек.
extern vu8 Cnt100mSec;	// Счетчик по 100 мсек.
extern vu8 Cnt10mSec; // Счетчик по 10 мсек.
extern vu8 Cnt1Sec;	// Счетчик по 1 сек.
extern vu8 Cnt1Min;	// Счетчик по 1 мин.
extern vu8 FlTime;	// Флаг временных событий
extern vu8 Check;	// защита от зависания
extern vu8 TimeCheck;	// Таймер
extern vu8 Event;	// 
extern vu8 P;	// 
extern vu8 PWM;	// Яркость

extern vu8 wday;
extern vu8 sec;
extern vu8 min;
extern vu8 hour;
extern vu8 hourDec;
extern vu8 mday;
extern vu8 mon;
extern vu32 year;
extern vu32 us;
extern vu8 TimeForCO2;
extern vu16 CO2;


extern char namesend[];
extern char pinsend[];

extern u8 del;
// КАНАЛ
//=======
typedef struct _chanel_t{
	vu8 chanelID;											// код канала 3 бита
	vu8 chState;											// состояие канала.
	vu8 buffOUT[MaxPacketLen];				// буфер отправки.
	vu8 buffOUTLen;										// длина отправляемых данных.
	vu8 ptrOUT;												// указатель на текущий отправляемый байт.
	void (*SendFunc) (void);							// указатель на функцию отправки.
	vu8 buffIN[MaxPacketLen];					// буфер приема байтов.
	vu8 ptrIN;												// указатель на последний принятый байт.
	vu8 dummY;
	vu8 PakIN[MaxPacketLen];					// принятый пакет
	vu8 PakINLen;											// длина данных в пакете
} ChanelType;

extern ChanelType chList[];

// состояние канала в chState.
#define chSend		(1<<0)		// канал занят отправкой.
#define chRecv		(1<<1)		// канал занят ожиданием ответа ??????????? убрать отсюда, сделать анализ в очереди
#define chEnaData	(1<<2)		// готов пакет в буфере PakIN, пока не сбросим из main нельзя портить PakIN
#define chPakInOFlow (1<<3)		// предыдущий пакет еще не считан = переполнение пакетов в канале, для информации

#define SEC_A_DAY 86400
typedef struct{
	u32 year;
	u8 mon;
	u8 mday;
	u8 hour;
	u8 min;
	u8 sec;
	u8 wday;
} unix_cal;

void timer_to_cal (vu32 timer, unix_cal * unix_time);
vu32 cal_to_timer (unix_cal * unix_time);
void RTC_SetCounter(vu32 count)      ;
#define ClearAllSeg *DIG1=1; *DIG2=1;*DIG3=1; *DIG4=1;
	
// subs.c
void SystemInit(void);
void SendToCOM(void);
void SendToUSR232(void);
void InitPcktMan(void);
void PacketCycle(void);
u16 crc16(vu8* pck, vu8 len);
vu8 itoa(s32 i, u8* bb);
void Delay(u16 us);

extern long temperature;
extern long pressure;
extern float press_f;
extern long humidity;
extern vu16 Pill;
#define SetCS()		(GPIOB->BSRR=(BIT(12) << 16))		// Выбрать SD->L.
#define ResetCS()	(GPIOB->BSRR=BIT(12))		// Отключить SD->H.
#define SetSPIIE()	(SPI2->CR2 |= BIT(SPI_RXNEIE))		// Разрешить прерывание RX.
#define ResetSPIIE()	(SPI2->CR2 &= ~BIT(SPI_RXNEIE))		// Запретить прерывание RX.
extern vu8 BufFromSPI[20];
extern vu8 Buf2SPI[20];
extern vu8 PtrByteSPI;
extern vu8 CntByteSPI;
extern vu8 SPI_mode;
vu8 Read8(vu8 Com);
vu16 Read16(vu8 Com);
void Write8(vu8 Com, vu8 Data);
vu32 Read24(vu8 Com);

#endif