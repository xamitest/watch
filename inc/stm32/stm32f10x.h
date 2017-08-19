// stm32f10x.h
#ifndef _stm32f10x_h_
#define _stm32f10x_h_

// Peripheral memory map
// Peripheral and SRAM base address in the alias region
#define PERIPH_BB_BASE ((u32)0x42000000)
#define SRAM_BB_BASE ((u32)0x22000000)

// Peripheral and SRAM base address in the bit-band region
#define SRAM_BASE ((u32)0x20000000)
#define PERIPH_BASE ((u32)0x40000000)

// Flash Option Bytes base address
#define OB_BASE ((u32)0x1FFFF800)

// Peripheral memory map
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE+0x10000)
#define AHBPERIPH_BASE (PERIPH_BASE+0x20000)

// Регистры из APB1PERIPH_BASE.
#define TIM2_BASE (APB1PERIPH_BASE+0x0000)
#define TIM3_BASE (APB1PERIPH_BASE+0x0400)
#define TIM4_BASE (APB1PERIPH_BASE+0x0800)
#define TIM5_BASE (APB1PERIPH_BASE+0x0C00)
#define TIM6_BASE (APB1PERIPH_BASE+0x1000)
#define TIM7_BASE (APB1PERIPH_BASE+0x1400)
#define TIM12_BASE (APB1PERIPH_BASE+0x1800)
#define TIM13_BASE (APB1PERIPH_BASE+0x1C00)
#define TIM14_BASE (APB1PERIPH_BASE+0x2000)
#define RTC_BASE (APB1PERIPH_BASE+0x2800)
#define WWDG_BASE (APB1PERIPH_BASE+0x2C00)
#define IWDG_BASE (APB1PERIPH_BASE+0x3000)
#define SPI2_BASE (APB1PERIPH_BASE+0x3800)
#define SPI3_BASE (APB1PERIPH_BASE+0x3C00)
#define USART2_BASE (APB1PERIPH_BASE+0x4400)
#define USART3_BASE (APB1PERIPH_BASE+0x4800)
#define USART4_BASE (APB1PERIPH_BASE+0x4C00)
#define USART5_BASE (APB1PERIPH_BASE+0x5000)
#define I2C1_BASE (APB1PERIPH_BASE+0x5400)
#define I2C2_BASE (APB1PERIPH_BASE+0x5800)
#define USB_BASE (APB1PERIPH_BASE+0x5C00)
#define CAN_BASE (APB1PERIPH_BASE+0x6400)
#define CAN2_BASE (APB1PERIPH_BASE+0x6800)
#define BKP_BASE (APB1PERIPH_BASE+0x6C00)
#define PWR_BASE (APB1PERIPH_BASE+0x7000)
#define DAC_BASE (APB1PERIPH_BASE+0x7400)

// Регистры из APB2PERIPH_BASE.
#define AFIO_BASE (APB2PERIPH_BASE+0x0000)
#define EXTI_BASE (APB2PERIPH_BASE+0x0400)
#define GPIOA_BASE (APB2PERIPH_BASE+0x0800)
#define GPIOB_BASE (APB2PERIPH_BASE+0x0C00)
#define GPIOC_BASE (APB2PERIPH_BASE+0x1000)
#define GPIOD_BASE (APB2PERIPH_BASE+0x1400)
#define GPIOE_BASE (APB2PERIPH_BASE+0x1800)
#define GPIOF_BASE (APB2PERIPH_BASE+0x1C00)
#define GPIOG_BASE (APB2PERIPH_BASE+0x2000)
#define ADC1_BASE (APB2PERIPH_BASE+0x2400)
#define ADC2_BASE (APB2PERIPH_BASE+0x2800)
#define TIM1_BASE (APB2PERIPH_BASE+0x2C00)
#define SPI1_BASE (APB2PERIPH_BASE+0x3000)
#define TIM8_BASE (APB2PERIPH_BASE+0x3400)
#define USART1_BASE (APB2PERIPH_BASE+0x3800)
#define TIM9_BASE (APB2PERIPH_BASE+0x4C00)
#define TIM10_BASE (APB2PERIPH_BASE+0x5000)
#define TIM11_BASE (APB2PERIPH_BASE+0x5400)

// Регистры из AHBPERIPH_BASE.
#define DMA1_BASE (AHBPERIPH_BASE+0x0000)
#define DMA2_BASE (AHBPERIPH_BASE+0x0400)
#define RCC_BASE (AHBPERIPH_BASE+0x1000)
#define FLASH_BASE (AHBPERIPH_BASE+0x2000)
#define CRC_BASE (AHBPERIPH_BASE+0x3000)
#define ETH_BASE (AHBPERIPH_BASE+0x8000)

#define USBGOTG_BASE (PERIPH_BASE+0x10000000)		// Глобальные регистры USB.
#define USBHOTG_BASE (PERIPH_BASE+0x10000400)		// Host-регистры USB.
#define USBDOTG_BASE (PERIPH_BASE+0x10000800)		// Device-регистры USB.
#define USBPOTG_BASE (PERIPH_BASE+0x10000E00)		// PWR-регистры USB.
#define USBHCOTG_BASE (PERIPH_BASE+0x10001000)		// Host-Channel-регистры USB.

// System Control Space memory map
#define SCS_BASE ((u32)0xE000E000)
#define SysTick_BASE (SCS_BASE+0x0010)
#define NVIC_BASE (SCS_BASE+0x0100)
#define SCB_BASE (SCS_BASE+0x0D00)

//=== Объявления регистров общего назначения.

//=== Контроллер RTC ===//
typedef struct{
	vu32 CRH;
	vu32 CRL;
	vu32 PRLH;
	vu32 PRLL;
	vu32 DIVH;
	vu32 DIVL;
	vu32 CNTH;
	vu32 CNTL;
	vu32 ALRH;
	vu32 ALRL;
} RTC_TypeDef;
#define RTC	((RTC_TypeDef *) RTC_BASE)
// CRH - регистр управления старший.
#define RTC_SECIE	0		// 
#define RTC_ALRIE	1		// 
#define RTC_OWIE	2		// 
// CRL - регистр управления младший.
#define RTC_SECF	0		// 
#define RTC_ALRF	1		// 
#define RTC_OWF	2		// 
#define RTC_RSF	3		// 
#define RTC_CNF	4		// 
#define RTC_RTOFF	5		// 

//=== Контроллер управления питанием PWR ===//
typedef struct{
	vu32 CR;
	vu32 CSR;
} PWR_TypeDef;
#define PWR	((PWR_TypeDef *) PWR_BASE)
// CR - управление.
#define PWR_LPDS	0		// 
#define PWR_PDDS	1		// 
#define PWR_CWUF	2		// 
#define PWR_CSBF	3		// 
#define PWR_PVDE	4		// 
#define PWR_PLS0	5		// 
#define PWR_PLS1	6		// 
#define PWR_PLS2	7		// 
#define PWR_DBP	8		// 
// CSR - управление/статус.
#define PWR_WUF	0		// 
#define PWR_SBF	1		// 
#define PWR_PWDO	2		// 
#define PWR_EWUP	8		// 

//=== Контроллер резерва BKP ===//
typedef struct{
	vu32 RESERVED0;
	vu32 DR1;
	vu32 DR2;
	vu32 DR3;
	vu32 DR4;
	vu32 DR5;
	vu32 DR6;
	vu32 DR7;
	vu32 DR8;
	vu32 DR9;
	vu32 DR10;
	vu32 RTCCR;
	vu32 CR;
	vu32 CSR;
	vu32 RESERVED1;
	vu32 RESERVED2;
	vu32 DR11;
	vu32 DR12;
	vu32 DR13;
	vu32 DR14;
	vu32 DR15;
	vu32 DR16;
	vu32 DR17;
	vu32 DR18;
	vu32 DR19;
	vu32 DR20;
	vu32 DR21;
	vu32 DR22;
	vu32 DR23;
	vu32 DR24;
	vu32 DR25;
	vu32 DR26;
	vu32 DR27;
	vu32 DR28;
	vu32 DR29;
	vu32 DR30;
	vu32 DR31;
	vu32 DR32;
	vu32 DR33;
	vu32 DR34;
	vu32 DR35;
	vu32 DR36;
	vu32 DR37;
	vu32 DR38;
	vu32 DR39;
	vu32 DR40;
	vu32 DR41;
	vu32 DR42;
} BKP_TypeDef;
#define BKP	((BKP_TypeDef *) BKP_BASE)
// RTCCR - калибровка RTC.
#define BKP_CAL0	0		// 
#define BKP_CAL1	1		// 
#define BKP_CAL2	2		// 
#define BKP_CAL3	3		// 
#define BKP_CAL4	4		// 
#define BKP_CAL5	5		// 
#define BKP_CAL6	6		// 
#define BKP_CCO	7		// 
#define BKP_ASOE	8		// 
#define BKP_ASOS	9		// 
// CR - управление резервированием.
#define BKP_TPE	0		// 
#define BKP_TPAL	1		// 
// CSR - управление/статус резервирования.
#define BKP_CTE	0		// 
#define BKP_CTI	1		// 
#define BKP_TPIE	2		// 
#define BKP_TEF	8		// 
#define BKP_TIF	9		// 

//=== Контроллер внешних событий/прерываний ===//
typedef struct{
	vu32 IMR;
	vu32 EMR;
	vu32 RTSR;
	vu32 FTSR;
	vu32 SWIER;
	vu32 PR;
} EXTI_TypeDef;
#define EXTI	((EXTI_TypeDef *) EXTI_BASE)
// IMR - регистр маскирования прерываний.
// EMR - регистр маскирования событий.
#define EXTI_MR0	0		// 
#define EXTI_MR1	1		// 
#define EXTI_MR2	2		// 
#define EXTI_MR3	3		// 
#define EXTI_MR4	4		// 
#define EXTI_MR5	5		// 
#define EXTI_MR6	6		// 
#define EXTI_MR7	7		// 
#define EXTI_MR8	8		// 
#define EXTI_MR9	9		// 
#define EXTI_MR10	10		// 
#define EXTI_MR11	11		// 
#define EXTI_MR12	12		// 
#define EXTI_MR13	13		// 
#define EXTI_MR14	14		// 
#define EXTI_MR15	15		// 
#define EXTI_MR16	16		// 
#define EXTI_MR17	17		// 
#define EXTI_MR18	18		// 
#define EXTI_MR19	19		// 
// RTSR - выбор триггера нарастания.
// FTSR - выбор триггера спада.
#define EXTI_TR0	0		// 
#define EXTI_TR1	1		// 
#define EXTI_TR2	2		// 
#define EXTI_TR3	3		// 
#define EXTI_TR4	4		// 
#define EXTI_TR5	5		// 
#define EXTI_TR6	6		// 
#define EXTI_TR7	7		// 
#define EXTI_TR8	8		// 
#define EXTI_TR9	9		// 
#define EXTI_TR10	10		// 
#define EXTI_TR11	11		// 
#define EXTI_TR12	12		// 
#define EXTI_TR13	13		// 
#define EXTI_TR14	14		// 
#define EXTI_TR15	15		// 
#define EXTI_TR16	16		// 
#define EXTI_TR17	17		// 
#define EXTI_TR18	18		// 
#define EXTI_TR19	19		// 
// SWIER - программные события прерываний.
#define EXTI_SWIER0	0		// 
#define EXTI_SWIER1	1		// 
#define EXTI_SWIER2	2		// 
#define EXTI_SWIER3	3		// 
#define EXTI_SWIER4	4		// 
#define EXTI_SWIER5	5		// 
#define EXTI_SWIER6	6		// 
#define EXTI_SWIER7	7		// 
#define EXTI_SWIER8	8		// 
#define EXTI_SWIER9	9		// 
#define EXTI_SWIER10	10		// 
#define EXTI_SWIER11	11		// 
#define EXTI_SWIER12	12		// 
#define EXTI_SWIER13	13		// 
#define EXTI_SWIER14	14		// 
#define EXTI_SWIER15	15		// 
#define EXTI_SWIER16	16		// 
#define EXTI_SWIER17	17		// 
#define EXTI_SWIER18	18		// 
#define EXTI_SWIER19	19		// 
// PR - регистр запросов прерываний.
#define EXTI_PR0	0		// 
#define EXTI_PR1	1		// 
#define EXTI_PR2	2		// 
#define EXTI_PR3	3		// 
#define EXTI_PR4	4		// 
#define EXTI_PR5	5		// 
#define EXTI_PR6	6		// 
#define EXTI_PR7	7		// 
#define EXTI_PR8	8		// 
#define EXTI_PR9	9		// 
#define EXTI_PR10	10		// 
#define EXTI_PR11	11		// 
#define EXTI_PR12	12		// 
#define EXTI_PR13	13		// 
#define EXTI_PR14	14		// 
#define EXTI_PR15	15		// 
#define EXTI_PR16	16		// 
#define EXTI_PR17	17		// 
#define EXTI_PR18	18		// 
#define EXTI_PR19	19		// 

//=== Опциональные байты ===//
typedef struct{
	vu16 RDP;
	vu16 USER;
	vu16 Data0;
	vu16 Data1;
	vu16 WRP0;
	vu16 WRP1;
	vu16 WRP2;
	vu16 WRP3;
} OB_TypeDef;
#define OB	((OB_TypeDef *) OB_BASE)

//=== Независимый WATCHDOG ===//
typedef struct{
	vu32 KR;
	vu32 PR;
	vu32 RLR;
	vu32 SR;
} IWDG_TypeDef;
#define IWDG	((IWDG_TypeDef *) IWDG_BASE)
// SR - регистр статуса.
#define IWDG_PVU	0		// 
#define IWDG_RVU	1		// 

//=== DMA регистры ===//
typedef struct{
	vu32 ISR;		// 0x0000
	vu32 IFCR;
	vu32 CCR1;
	vu32 CNDTR1;
	vu32 CPAR1;		// 0x0010
	vu32 CMAR1;
	vu32 RESERVED1;
	vu32 CCR2;
	vu32 CNDTR2;		// 0x0020
	vu32 CPAR2;
	vu32 CMAR2;
	vu32 RESERVED2;
	vu32 CCR3;		// 0x0030
	vu32 CNDTR3;
	vu32 CPAR3;
	vu32 CMAR3;
	vu32 RESERVED3;		// 0x0040
	vu32 CCR4;
	vu32 CNDTR4;
	vu32 CPAR4;
	vu32 CMAR4;		// 0x0050
	vu32 RESERVED4;
	vu32 CCR5;
	vu32 CNDTR5;
	vu32 CPAR5;		// 0x0060
	vu32 CMAR5;
	vu32 RESERVED5;
	vu32 CCR6;
	vu32 CNDTR6;		// 0x0070
	vu32 CPAR6;
	vu32 CMAR6;
	vu32 RESERVED6;
	vu32 CCR7;		// 0x0080
	vu32 CNDTR7;
	vu32 CPAR7;
	vu32 CMAR7;
	vu32 RESERVED7;		// 0x0090
} DMA_TypeDef;
#define DMA1	((DMA_TypeDef *) DMA1_BASE)
#define DMA2	((DMA_TypeDef *) DMA2_BASE)
// ISR - состояние прерываний 
#define DMA_GIF1	0		// 
#define DMA_TCIF1	1		// 
#define DMA_HTIF1	2		// 
#define DMA_TEIF1	3		// 
#define DMA_GIF2	4		// 
#define DMA_TCIF2	5		// 
#define DMA_HTIF2	6		// 
#define DMA_TEIF2	7		// 
#define DMA_GIF3	8		// 
#define DMA_TCIF3	9		// 
#define DMA_HTIF3	10		// 
#define DMA_TEIF3	11		// 
#define DMA_GIF4	12		// 
#define DMA_TCIF4	13		// 
#define DMA_HTIF4	14		// 
#define DMA_TEIF4	15		// 
#define DMA_GIF5	16		// 
#define DMA_TCIF5	17		// 
#define DMA_HTIF5	18		// 
#define DMA_TEIF5	19		// 
#define DMA_GIF6	20		// 
#define DMA_TCIF6	21		// 
#define DMA_HTIF6	22		// 
#define DMA_TEIF6	23		// 
#define DMA_GIF7	24		// 
#define DMA_TCIF7	25		// 
#define DMA_HTIF7	26		// 
#define DMA_TEIF7	27		// 
// IFCR - очистка флагов прерываний
#define DMA_CGIF1	0		// 
#define DMA_CTCIF1	1		// 
#define DMA_CHTIF1	2		// 
#define DMA_CTEIF1	3		// 
#define DMA_CGIF2	4		// 
#define DMA_CTCIF2	5		// 
#define DMA_CHTIF2	6		// 
#define DMA_CTEIF2	7		// 
#define DMA_CGIF3	8		// 
#define DMA_CTCIF3	9		// 
#define DMA_CHTIF3	10		// 
#define DMA_CTEIF3	11		// 
#define DMA_CGIF4	12		// 
#define DMA_CTCIF4	13		// 
#define DMA_CHTIF4	14		// 
#define DMA_CTEIF4	15		// 
#define DMA_CGIF5	16		// 
#define DMA_CTCIF5	17		// 
#define DMA_CHTIF5	18		// 
#define DMA_CTEIF5	19		// 
#define DMA_CGIF6	20		// 
#define DMA_CTCIF6	21		// 
#define DMA_CHTIF6	22		// 
#define DMA_CTEIF6	23		// 
#define DMA_CGIF7	24		// 
#define DMA_CTCIF7	25		// 
#define DMA_CHTIF7	26		// 
#define DMA_CTEIF7	27		// 
// CCRx - конфигурация канала x
#define DMA_EN	0		// 
#define DMA_TCIE	1		// 
#define DMA_HTIE	2		// 
#define DMA_TEIE	3		// 
#define DMA_DIR	4		// 
#define DMA_CIRC	5		// 
#define DMA_PINC	6		// 
#define DMA_MINC	7		// 
#define DMA_PSIZE0	8		// 
#define DMA_PSIZE1	9		// 
#define DMA_MSIZE0	10		// 
#define DMA_MSIZE1	11		// 
#define DMA_PL0	12		// 
#define DMA_PL1	13		// 
#define DMA_MEM2MEM	14		// 

//=== FlashMemoryInterfase ===//
typedef struct{
	vu32 ACR;		// 0x000
	vu32 KEYR;		// Значение 1 =0x45670123, значение 2 =0xCDEF89AB
	vu32 OPTKEYR;
	vu32 SR;
	vu32 CR;		// 0x010
	vu32 AR;		// Регистр адреса.
	vu32 RESERVED;
	vu32 OBR;
	vu32 WRPR;		// 0x010 Регистр защиты от записи.
} FLASH_TypeDef;
#define FLASH	((FLASH_TypeDef *) FLASH_BASE)
// ACR - управление доступом.
#define FLASH_LATENCY0	0		// Циклы ожидания.
#define FLASH_LATENCY1	1		// 
#define FLASH_LATENCY2	2		// 
#define FLASH_HLFCYA	3		// Разрешение полуциклового доступа.
#define FLASH_PRFTBE	4		// Разрешение буфера предвыборки.
#define FLASH_PRFTBS	5		// Статус буфера предвыборки.
// SR - статус.
#define FLASH_BSY	0		// Ожидание.
#define FLASH_PGERR	2		// Ошибка программирования.
#define FLASH_WRPRTERR	4		// Запись в защищенную область.
#define FLASH_EOP	5		// Конец операции.
// CR - управление.
#define FLASH_PG	0		// Программирование.
#define FLASH_PER	1		// Страничное стирание.
#define FLASH_MER	2		// Общее стирание.
#define FLASH_OPTPG	4		// Программирование байтов опций.
#define FLASH_OPTER	5		// Стирание байтов опций.
#define FLASH_STRT	6		// Старт.
#define FLASH_LOCK	7		// Замок.
#define FLASH_OPTWRE	9		// Разрешение записи байтов опций.
#define FLASH_ERRIE	10		// Разрешение прерывания по ошибке.
#define FLASH_EOPIE	12		// Разрешение прерывания по концу операции.
// OBR - опции.
#define FLASH_OPTERR	0		// Ошибка байта опций.
#define FLASH_PDPRT	1		// Защита от записи.
#define FLASH_WDG_SW	2		// 
#define FLASH_RST_STOP	3		// 
#define FLASH_RST_STDBY	4		// 

//=== RCC регистры ===//
typedef struct{
	vu32 CR;
	vu32 CFGR;
	vu32 CIR;
	vu32 APB2RSTR;
	vu32 APB1RSTR;
	vu32 AHBENR;
	vu32 APB2ENR;
	vu32 APB1ENR;
	vu32 BDCR;
	vu32 CSR;
	vu32 AHBSTR;
	vu32 CFGR2;
} RCC_TypeDef;
#define RCC	((RCC_TypeDef *) RCC_BASE)
// CR - 
#define RCC_HSION	0
#define RCC_HSIRDY	1
#define RCC_HSEON	16
#define RCC_HSERDY	17
#define RCC_HSEBYP	18
#define RCC_CSSON	19
#define RCC_PLLON	24
#define RCC_PLLRDY	25
// CFGR - 
#define RCC_SW0	0
#define RCC_SW1	1
#define RCC_SWS0	2
#define RCC_SWS1	3
#define RCC_HPRE0	4
#define RCC_HPRE1	5
#define RCC_HPRE2	6
#define RCC_HPRE3	7
#define RCC_PPRE10	8
#define RCC_PPRE11	9
#define RCC_PPRE12	10
#define RCC_PPRE20	11
#define RCC_PPRE21	12
#define RCC_PPRE22	13
#define RCC_ADCPRE0	14		// Делитель АЦП от PCLK2
#define RCC_ADCPRE1	15
#define RCC_PLLSRC	16
#define RCC_PLLXTPRE	17
#define RCC_PLLMUL0	18
#define RCC_PLLMUL1	19
#define RCC_PLLMUL2	20
#define RCC_PLLMUL3	21
#define RCC_USBPRE	22
#define RCC_MCO0	24
#define RCC_MCO1	25
#define RCC_MCO2	26
// CIR - 
#define RCC_LSIRDYF	0
#define RCC_LSERDYF	1
#define RCC_HSIRDYF	2
#define RCC_HSERDYF	3
#define RCC_PLLRDYF	4
#define RCC_CSSF	7
#define RCC_LSIRDYIE	8
#define RCC_LSERDYIE	9
#define RCC_HSIRDYIE	10
#define RCC_HSERDYIE	11
#define RCC_PLLRDYIE	12
#define RCC_LSIRDYC	16
#define RCC_LSERDYC	17
#define RCC_HSIRDYC	18
#define RCC_HSERDYC	19
#define RCC_PLLRDYC	20
#define RCC_CSSC	23
// APB2RSTR - 
#define RCC_AFIORST	0
#define RCC_IOPARST	2
#define RCC_IOPBRST	3
#define RCC_IOPCRST	4
#define RCC_IOPDRST	5
#define RCC_IOPERST	6
#define RCC_IOPFRST	7
#define RCC_IOPGRST	8
#define RCC_ADC1RST	9
#define RCC_ADC2RST	10
#define RCC_TIM1RST	11
#define RCC_SPI1RST	12
#define RCC_TIM8RST	13
#define RCC_USART1RST	14
#define RCC_ADC3RST	15
#define RCC_TIM9RST	19
#define RCC_TIM10RST	20
#define RCC_TIM11RST	21
// APB1RSTR - 
#define RCC_TIM2RST	0
#define RCC_TIM3RST	1
#define RCC_TIM4RST	2
#define RCC_TIM5RST	3
#define RCC_TIM6RST	4
#define RCC_TIM7RST	5
#define RCC_TIM12RST	6
#define RCC_TIM13RST	7
#define RCC_TIM14RST	8
#define RCC_WWDGRST	11
#define RCC_SPI2RST	14
#define RCC_SPI3RST	15
#define RCC_USART2RST	17
#define RCC_USART3RST	18
#define RCC_USART4RST	19
#define RCC_USART5RST	20
#define RCC_I2C1RST	21
#define RCC_I2C2RST	22
#define RCC_USBRST	23
#define RCC_CANRST	25
#define RCC_BKPRST	27
#define RCC_PWRRST	28
#define RCC_DACRST	29
// AHBENR - 
#define RCC_DMA1EN	0
#define RCC_DMA2EN	1
#define RCC_SRAMEN	2
#define RCC_FLITFEN	4
#define RCC_CRCEN	6
#define RCC_FSMCEN	8
#define RCC_SDIOEN	10
#define RCC_OTGFSEN	12
// APB2ENR - 
#define RCC_AFIOEN	0
#define RCC_IOPAEN	2
#define RCC_IOPBEN	3
#define RCC_IOPCEN	4
#define RCC_IOPDEN	5
#define RCC_IOPEEN	6
#define RCC_IOPFEN	7
#define RCC_IOPGEN	8
#define RCC_ADC1EN	9
#define RCC_ADC2EN	10
#define RCC_TIM1EN	11
#define RCC_SPI1EN	12
#define RCC_TIM8EN	13
#define RCC_USART1EN	14
#define RCC_ADC3EN	15
#define RCC_TIM9EN	19
#define RCC_TIM10EN	20
#define RCC_TIM11EN	21
// APB1ENR - 
#define RCC_TIM2EN	0
#define RCC_TIM3EN	1
#define RCC_TIM4EN	2
#define RCC_TIM5EN	3
#define RCC_TIM6EN	4
#define RCC_TIM7EN	5
#define RCC_TIM12EN	6
#define RCC_TIM13EN	7
#define RCC_TIM14EN	8
#define RCC_WWDGEN	11
#define RCC_SPI2EN	14
#define RCC_SPI3EN	15
#define RCC_USART2EN	17
#define RCC_USART3EN	18
#define RCC_USART4EN	19
#define RCC_USART5EN	20
#define RCC_I2C1EN	21
#define RCC_I2C2EN	22
#define RCC_USBEN	23
#define RCC_CANEN	25
#define RCC_BKPEN	27
#define RCC_PWREN	28
#define RCC_DACEN	29
// BDCR - 
#define RCC_LSEON	0
#define RCC_LSERDY	1
#define RCC_LSEBYP	2
#define RCC_RTCSEL0	8
#define RCC_RTCSEL1	9
#define RCC_RTCSEN	15
#define RCC_BDRST	16
// CSR - 
#define RCC_LSION	0
#define RCC_LSIRDY	1
#define RCC_RMVF	24
#define RCC_PINRSTF	26
#define RCC_PORRSTF	27
#define RCC_SWTRSTF	28
#define RCC_IWDGRSTF	29
#define RCC_WWDGRSTF	30
#define RCC_LPWRRSTF	31
// CFGR2 - 
#define RCC_PREDIV10	0
#define RCC_PREDIV11	1
#define RCC_PREDIV12	2
#define RCC_PREDIV13	3
#define RCC_PREDIV20	4
#define RCC_PREDIV21	5
#define RCC_PREDIV22	6
#define RCC_PREDIV23	7
#define RCC_PLL2MUL0	8
#define RCC_PLL2MUL1	9
#define RCC_PLL2MUL2	10
#define RCC_PLL2MUL3	11
#define RCC_PLL3MUL0	12
#define RCC_PLL3MUL1	13
#define RCC_PLL3MUL2	14
#define RCC_PLL3MUL3	15
#define RCC_PREDIV1SRC	16
#define RCC_I2S2SRC	17
#define RCC_I2S3SRC	18

//=== GPIO регистры ===//
typedef struct{
	vu32 CRL;
	vu32 CRH;
	vu32 IDR;
	vu32 ODR;
	vu32 BSRR;
	vu32 BRR;
	vu32 LCKR;
} GPIO_TypeDef;
#define GPIOA	((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB	((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC	((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD	((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE	((GPIO_TypeDef *) GPIOE_BASE)
// GPIO
#define PIN_IO_TYPE_Input	0
#define PIN_IO_TYPE_OutputMax10M	1
#define PIN_IO_TYPE_OutputMax02M	2
#define PIN_IO_TYPE_OutputMax50M	3

#define PIN_INPUT_MODE_AIN	0
#define PIN_INPUT_MODE_FLOAT		1
#define PIN_INPUT_MODE_PULLUP	2

#define PIN_OUTPUT_MODE_GP_PP	0
#define PIN_OUTPUT_MODE_GP_OD	1
#define PIN_OUTPUT_MODE_Alt_PP	2
#define PIN_OUTPUT_MODE_Alt_OD	3

//=== AFIO регистры альтернативных функций ===//
typedef struct{
	vu32 EVCR;
	vu32 MAPR;
	vu32 EXTICR1;
	vu32 EXTICR2;
	vu32 EXTICR3;
	vu32 EXTICR4;
} AFIO_TypeDef;
#define AFIO ((AFIO_TypeDef *) AFIO_BASE)
// EVCR
#define AFIO_PIN0	0
#define AFIO_PIN1	1
#define AFIO_PIN2	2
#define AFIO_PIN3	3
#define AFIO_PORT0	4
#define AFIO_PORT1	5
#define AFIO_PORT2	6
#define AFIO_EVOE	7
// MAPR
#define AFIO_SPI1_REMAP	0
#define AFIO_I2C1_REMAP	1
#define AFIO_USART1_REMAP	2
#define AFIO_USART2_REMAP	3
#define AFIO_USART30_REMAP	4
#define AFIO_USART31_REMAP	5
#define AFIO_TIM10_REMAP	6
#define AFIO_TIM11_REMAP	7
#define AFIO_TIM20_REMAP	8
#define AFIO_TIM21_REMAP	9
#define AFIO_TIM30_REMAP	10
#define AFIO_TIM31_REMAP	11
#define AFIO_TIM4_REMAP	12
#define AFIO_CAN0_REMAP	13
#define AFIO_CAN1_REMAP	14
#define AFIO_PD01_REMAP	15
#define AFIO_TIM5CH4_REMAP	16
#define AFIO_ADC1IN_REMAP	17
#define AFIO_ADC1REG_REMAP	18
#define AFIO_ADC2IN_REMAP	19
#define AFIO_ADC2REG_REMAP	20
#define AFIO_SWJ_CFG0	24
#define AFIO_SWJ_CFG1	25
#define AFIO_SWJ_CFG2	26
// EXTICR1
#define AFIO_EXTI00	0
#define AFIO_EXTI01	1
#define AFIO_EXTI02	2
#define AFIO_EXTI03	3
#define AFIO_EXTI10	4
#define AFIO_EXTI11	5
#define AFIO_EXTI12	6
#define AFIO_EXTI13	7
#define AFIO_EXTI20	8
#define AFIO_EXTI21	9
#define AFIO_EXTI22	10
#define AFIO_EXTI23	11
#define AFIO_EXTI30	12
#define AFIO_EXTI31	13
#define AFIO_EXTI32	14
#define AFIO_EXTI33	15
// EXTICR2
#define AFIO_EXTI40	0
#define AFIO_EXTI41	1
#define AFIO_EXTI42	2
#define AFIO_EXTI43	3
#define AFIO_EXTI50	4
#define AFIO_EXTI51	5
#define AFIO_EXTI52	6
#define AFIO_EXTI53	7
#define AFIO_EXTI60	8
#define AFIO_EXTI61	9
#define AFIO_EXTI62	10
#define AFIO_EXTI63	11
#define AFIO_EXTI70	12
#define AFIO_EXTI71	13
#define AFIO_EXTI72	14
#define AFIO_EXTI73	15
// EXTICR3
#define AFIO_EXTI80	0
#define AFIO_EXTI81	1
#define AFIO_EXTI82	2
#define AFIO_EXTI83	3
#define AFIO_EXTI90	4
#define AFIO_EXTI91	5
#define AFIO_EXTI92	6
#define AFIO_EXTI93	7
#define AFIO_EXTI100	8
#define AFIO_EXTI101	9
#define AFIO_EXTI102	10
#define AFIO_EXTI103	11
#define AFIO_EXTI110	12
#define AFIO_EXTI111	13
#define AFIO_EXTI112	14
#define AFIO_EXTI113	15
// EXTICR4
#define AFIO_EXTI120	0
#define AFIO_EXTI121	1
#define AFIO_EXTI122	2
#define AFIO_EXTI123	3
#define AFIO_EXTI130	4
#define AFIO_EXTI131	5
#define AFIO_EXTI132	6
#define AFIO_EXTI133	7
#define AFIO_EXTI140	8
#define AFIO_EXTI141	9
#define AFIO_EXTI142	10
#define AFIO_EXTI143	11
#define AFIO_EXTI150	12
#define AFIO_EXTI151	13
#define AFIO_EXTI152	14
#define AFIO_EXTI153	15

//=== USART регистры ===//
typedef struct{
	vu32 SR;		// 
	vu32 DR;		// Регистр данных.
	vu32 BRR;		// Регистр скорости.
	vu32 CR1;
	vu32 CR2;
	vu32 CR3;
	vu32 GTPR;		// Регистр предделителя и защитного промежутка.
} USART_TypeDef;
#define USART1 ((USART_TypeDef *) USART1_BASE)
#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)
// SR - регистр статуса.
#define USART_PE	0
#define USART_FE	1
#define USART_NE	2
#define USART_ORE	3
#define USART_IDLE	4
#define USART_RXNE	5		// 
#define USART_TC	6
#define USART_TXE	7		// 
#define USART_LBD	8
#define USART_CTS	9
// CR1 - регистр управления 1
#define USART_SBK	0
#define USART_RWU	1
#define USART_RE	2
#define USART_TE	3
#define USART_IDLEIE	4
#define USART_RXNEIE	5		// 
#define USART_TCIE	6
#define USART_TXEIE	7		// 
#define USART_PEIE	8
#define USART_PS	9
#define USART_PCE	10
#define USART_WAKE	11
#define USART_M	12
#define USART_UE	13		// 
// CR2
#define USART_ADD0	0
#define USART_ADD1	1
#define USART_ADD2	2
#define USART_ADD3	3
#define USART_LBDL	5
#define USART_LBDIE	6
#define USART_LBCL	8
#define USART_CPHA	9
#define USART_CPOL	10
#define USART_CLKEN	11
#define USART_STOP0	12
#define USART_STOP1	13
#define USART_LINEN	14
// CR3
#define USART_EIE	0
#define USART_IREN	1
#define USART_IRLP	2
#define USART_HDSEL	3
#define USART_NACK	4
#define USART_SCEN	5
#define USART_DMAR	6
#define USART_DMAT	7
#define USART_RTSE	8
#define USART_CTSE	9
#define USART_CTSIE	10

//=== USB регистры ===//
typedef struct{
	vu32 EP0R;		// 
	vu32 EP1R;		// 
	vu32 EP2R;		// 
	vu32 EP3R;		// 
	vu32 EP4R;		// 
	vu32 EP5R;		// 
	vu32 EP6R;		// 
	vu32 EP7R;		// 
	vu32 RESERVED1;
	vu32 RESERVED2;
	vu32 RESERVED3;
	vu32 RESERVED4;
	vu32 RESERVED5;
	vu32 RESERVED6;
	vu32 RESERVED7;
	vu32 RESERVED8;
	vu32 CNTR;		// 
	vu32 ISTR;		// 
	vu32 FNR;		// 
	vu32 DADDR;		// 
	vu32 BTABLE;		// 
} USB_TypeDef;
#define USB ((USB_TypeDef *) USB_BASE)
// EP0...7R - регистр конечной точки.
#define USB_EA0	0
#define USB_EA1	1
#define USB_EA2	2
#define USB_EA3	3
#define USB_STAT_TX0	4
#define USB_STAT_TX1	5
#define USB_DTOG_TX	6
#define USB_CTR_TX	7
#define USB_EP_KIND	8
#define USB_EP_TYPE0	9
#define USB_EP_TYPE1	10
#define USB_SETUP	11
#define USB_STAT_RX0	12
#define USB_STAT_RX1	13
#define USB_DTOG_RX	14
#define USB_CTR_RX	15
// CNTR - регистр управления.
#define USB_FRES	0
#define USB_PDWN	1
#define USB_LPMODE	2
#define USB_FSUSP	3
#define USB_RESUME	4
#define USB_ESOFM	8
#define USB_SOFM	9
#define USB_RESETM	10
#define USB_SUSPM	11
#define USB_WKUPM	12
#define USB_ERRM	13
#define USB_PMAOVRM	14
#define USB_CTRM	15
// ISTR - регистр 
#define USB_EP_ID0	0
#define USB_EP_ID1	1
#define USB_EP_ID2	2
#define USB_EP_ID3	3
#define USB_DIR	4
#define USB_ESOF	8
#define USB_SOF	9
#define USB_RESET	10
#define USB_SUSP	11
#define USB_WKUP	12
#define USB_ERR	13
#define USB_PMAOVR	14
#define USB_CTR	15
// FNR - регистр 
#define USB_FN0	0
#define USB_FN1	1
#define USB_FN2	2
#define USB_FN3	3
#define USB_FN4	4
#define USB_FN5	5
#define USB_FN6	6
#define USB_FN7	7
#define USB_FN8	8
#define USB_FN9	9
#define USB_FN10	10
#define USB_LSOF0	11
#define USB_LSOF1	12
#define USB_LCK	13
#define USB_RXDM	14
#define USB_RXDP	15
// DADDR - регистр 
#define USB_EF	7

//=== TIM2-5 регистры ===//
typedef struct{
	vu32 CR1;
	vu32 CR2;
	vu32 SMCR;
	vu32 DIER;
	vu32 SR;
	vu32 EGR;
	vu32 CCMR1;
	vu32 CCMR2;
	vu32 CCER;
	vu32 CNT;
	vu32 PSC;
	vu32 ARR;
	u32 RESERVED0;
	vu32 CCR1;
	vu32 CCR2;
	vu32 CCR3;
	vu32 CCR4;
	vu32 DCR;
	vu32 DMAR;
} TIM2_5_TypeDef;
#define TIM2 ((TIM2_5_TypeDef *) TIM2_BASE)
#define TIM3 ((TIM2_5_TypeDef *) TIM3_BASE)
#define TIM4 ((TIM2_5_TypeDef *) TIM4_BASE)
#define TIM5 ((TIM2_5_TypeDef *) TIM5_BASE)
// CR1
#define TIM2_5_CKD1	9
#define TIM2_5_CKD0	8
#define TIM2_5_APRE	7
#define TIM2_5_CMS1	6
#define TIM2_5_CMS0	5
#define TIM2_5_DIR	4
#define TIM2_5_OPM	3
#define TIM2_5_URS	2
#define TIM2_5_UDIS	1
#define TIM2_5_CEN	0
// CR2
#define TIM2_5_TI1S	7
#define TIM2_5_MMS2	6
#define TIM2_5_MMS1	5
#define TIM2_5_MMS0	4
#define TIM2_5_CCDS	3
// SMCR - регистр
#define TIM2_5_ETP	15
#define TIM2_5_ECE	14
#define TIM2_5_ETPS1	13
#define TIM2_5_ETPS0	12
#define TIM2_5_ETF3	11
#define TIM2_5_ETF2	10
#define TIM2_5_ETF1	9
#define TIM2_5_ETF0	8
#define TIM2_5_MSM	7
#define TIM2_5_TS2	6
#define TIM2_5_TS1	5
#define TIM2_5_TS0	4
#define TIM2_5_SMS2	2
#define TIM2_5_SMS1	1
#define TIM2_5_SMS0	0
// DIER - регистр
#define TIM2_5_TDE	14
#define TIM2_5_CC4DE	12
#define TIM2_5_CC3DE	11
#define TIM2_5_CC2DE	10
#define TIM2_5_CC1DE	9
#define TIM2_5_UDE	8
#define TIM2_5_TIE	6
#define TIM2_5_CC4IE	4
#define TIM2_5_CC3IE	3
#define TIM2_5_CC2IE	2
#define TIM2_5_CC1IE	1
#define TIM2_5_UIE	0
// SR - регистр статуса
#define TIM2_5_CC4OF	12
#define TIM2_5_CC3OF	11
#define TIM2_5_CC2OF	10
#define TIM2_5_CC1OF	9
#define TIM2_5_TIF	6
#define TIM2_5_CC4IF	4
#define TIM2_5_CC3IF	3
#define TIM2_5_CC2IF	2
#define TIM2_5_CC1IF	1
#define TIM2_5_UIF	0
// EGR - регистр генерации событий
#define TIM2_5_TG	6
#define TIM2_5_CC4G	4
#define TIM2_5_CC3G	3
#define TIM2_5_CC2G	2
#define TIM2_5_CC1G	1
#define TIM2_5_UG	0
// CCMR1 - регистр режима захвата-сравнения 1
#define TIM2_5_OC2CE	15
#define TIM2_5_OC2M2	14
#define TIM2_5_OC2M1	13
#define TIM2_5_OC2M0	12
#define TIM2_5_IC2F3	15
#define TIM2_5_IC2F2	14
#define TIM2_5_IC2F1	13
#define TIM2_5_IC2F0	12
#define TIM2_5_OC2PE	11
#define TIM2_5_OC2FE	10
#define TIM2_5_IC2PSC1	11
#define TIM2_5_IC2PSC0	10
#define TIM2_5_CC2S1	9
#define TIM2_5_CC2S0	8
#define TIM2_5_OC1CE	7
#define TIM2_5_OC1M2	6
#define TIM2_5_OC1M1	5
#define TIM2_5_OC1M0	4
#define TIM2_5_IC1F3	7
#define TIM2_5_IC1F2	6
#define TIM2_5_IC1F1	5
#define TIM2_5_IC1F0	4
#define TIM2_5_OC1PE	3
#define TIM2_5_OC1FE	2
#define TIM2_5_IC1PSC1	3
#define TIM2_5_IC1PSC0	2
#define TIM2_5_CC1S1	1
#define TIM2_5_CC1S0	0
// CCMR2 - регистр режима захвата-сравнения 2
#define TIM2_5_OC4CE	15
#define TIM2_5_OC4M2	14
#define TIM2_5_OC4M1	13
#define TIM2_5_OC4M0	12
#define TIM2_5_IC4F3	15
#define TIM2_5_IC4F2	14
#define TIM2_5_IC4F1	13
#define TIM2_5_IC4F0	12
#define TIM2_5_OC4PE	11
#define TIM2_5_OC4FE	10
#define TIM2_5_IC4PSC1	11
#define TIM2_5_IC4PSC0	10
#define TIM2_5_CC4S1	9
#define TIM2_5_CC4S0	8
#define TIM2_5_OC3CE	7
#define TIM2_5_OC3M2	6
#define TIM2_5_OC3M1	5
#define TIM2_5_OC3M0	4
#define TIM2_5_IC3F3	7
#define TIM2_5_IC3F2	6
#define TIM2_5_IC3F1	5
#define TIM2_5_IC3F0	4
#define TIM2_5_OC3PE	3
#define TIM2_5_OC3FE	2
#define TIM2_5_IC3PSC1	3
#define TIM2_5_IC3PSC0	2
#define TIM2_5_CC3S1	1
#define TIM2_5_CC3S0	0
// CCER - регистр разрешения захвата-сравнения
#define TIM2_5_CC4P	13
#define TIM2_5_CC4E	12
#define TIM2_5_CC3P	9
#define TIM2_5_CC3E	8
#define TIM2_5_CC2P	5
#define TIM2_5_CC2E	4
#define TIM2_5_CC1P	1
#define TIM2_5_CC1E	0
// DCR - регистр управления DMA
#define TIM2_5_DBL4	12
#define TIM2_5_DBL3	11
#define TIM2_5_DBL2	10
#define TIM2_5_DBL1	9
#define TIM2_5_DBL0	8
#define TIM2_5_DBA4	4
#define TIM2_5_DBA3	3
#define TIM2_5_DBA2	2
#define TIM2_5_DBA1	1
#define TIM2_5_DBA0	0

//=== ADC регистры ===//
typedef struct{
	vu32 SR;
	vu32 CR1;
	vu32 CR2;
	vu32 SMPR1;
	vu32 SMPR2;
	vu32 JOFR1;
	vu32 JOFR2;
	vu32 JOFR3;
	vu32 JOFR4;
	vu32 HTR;
	vu32 LTR;
	vu32 SQR1;
	vu32 SQR2;
	vu32 SQR3;
	vu32 JSQR;
	vu32 JDR1;
	vu32 JDR2;
	vu32 JDR3;
	vu32 JDR4;
	vu32 DR;
} ADC_TypeDef;
#define ADC1 ((ADC_TypeDef *) ADC1_BASE)
#define ADC2 ((ADC_TypeDef *) ADC2_BASE)
// SR
#define ADC_AWD	0
#define ADC_EOC	1
#define ADC_JEOC	2
#define ADC_JSTRT	3
#define ADC_STRT	4
// CR1
#define ADC_AWDCH0	0
#define ADC_AWDCH1	1
#define ADC_AWDCH2	2
#define ADC_AWDCH3	3
#define ADC_AWDCH4	4
#define ADC_EOCIE	5
#define ADC_AWDIE	6
#define ADC_JEOCIE	7
#define ADC_SCAN	8
#define ADC_AWDSGL	9
#define ADC_JAUTO	10
#define ADC_DISCEN	11
#define ADC_JDISCEN	12
#define ADC_DISCNUM0	13
#define ADC_DISCNUM1	14
#define ADC_DISCNUM2	15
#define ADC_DUALMOD0	16
#define ADC_DUALMOD1	17
#define ADC_DUALMOD2	18
#define ADC_DUALMOD3	19
#define ADC_JAWDEN	22
#define ADC_AWDEN	23
// CR2
#define ADC_ADON	0
#define ADC_CONT	1
#define ADC_CAL	2
#define ADC_RSTCAL	3
#define ADC_DMA	8
#define ADC_ALIGN	11
#define ADC_JEXTSEL0	12
#define ADC_JEXTSEL1	13
#define ADC_JEXTSEL2	14
#define ADC_JEXTT	15
#define ADC_EXTSEL0	17
#define ADC_EXTSEL1	18
#define ADC_EXTSEL2	19
#define ADC_EXTTRIG	20
#define ADC_JSWSTART	21
#define ADC_SWSTART	22
#define ADC_TSVREFE	23
// SMPR1
#define ADC_SMP100	0
#define ADC_SMP101	1
#define ADC_SMP102	2
#define ADC_SMP110	3
#define ADC_SMP111	4
#define ADC_SMP112	5
#define ADC_SMP120	6
#define ADC_SMP121	7
#define ADC_SMP122	8
#define ADC_SMP130	9
#define ADC_SMP131	10
#define ADC_SMP132	11
#define ADC_SMP140	12
#define ADC_SMP141	13
#define ADC_SMP142	14
#define ADC_SMP150	15
#define ADC_SMP151	16
#define ADC_SMP152	17
#define ADC_SMP160	18
#define ADC_SMP161	19
#define ADC_SMP162	20
#define ADC_SMP170	21
#define ADC_SMP171	22
#define ADC_SMP172	23
// SMPR2
#define ADC_SMP00	0
#define ADC_SMP01	1
#define ADC_SMP02	2
#define ADC_SMP10	3
#define ADC_SMP11	4
#define ADC_SMP12	5
#define ADC_SMP20	6
#define ADC_SMP21	7
#define ADC_SMP22	8
#define ADC_SMP30	9
#define ADC_SMP31	10
#define ADC_SMP32	11
#define ADC_SMP40	12
#define ADC_SMP41	13
#define ADC_SMP42	14
#define ADC_SMP50	15
#define ADC_SMP51	16
#define ADC_SMP52	17
#define ADC_SMP60	18
#define ADC_SMP61	19
#define ADC_SMP62	20
#define ADC_SMP70	21
#define ADC_SMP71	22
#define ADC_SMP72	23
#define ADC_SMP80	24
#define ADC_SMP81	25
#define ADC_SMP82	26
#define ADC_SMP90	27
#define ADC_SMP91	28
#define ADC_SMP92	29

//=== DAC регистры ===//
typedef struct{
	vu32 CR;		// 0x00
	vu32 SWTRIGR;
	vu32 DHR12R1;
	vu32 DHR12L1;
	vu32 DHR8R1;		// 0x10
	vu32 DHR12R2;
	vu32 DHR12L2;
	vu32 DHR8R2;
	vu32 DHR12RD;		// 0x20
	vu32 DHR12LD;
	vu32 DHR8RD;
	vu32 DOR1;
	vu32 DOR2;		// 0x30
} DAC_TypeDef;
#define DAC ((DAC_TypeDef *) DAC_BASE)
// CR
#define DAC_EN1	0
#define DAC_BOFF1	1
#define DAC_TEN1	2
#define DAC_TSEL10	3
#define DAC_TSEL11	4
#define DAC_TSEL12	5
#define DAC_WAVE10	6
#define DAC_WAVE11	7
#define DAC_MAMP10	8
#define DAC_MAMP11	9
#define DAC_MAMP12	10
#define DAC_MAMP13	11
#define DAC_DMAEN1	12
#define DAC_EN2	16
#define DAC_BOFF2	17
#define DAC_TEN2	18
#define DAC_TSEL20	19
#define DAC_TSEL21	20
#define DAC_TSEL22	21
#define DAC_WAVE20	22
#define DAC_WAVE21	23
#define DAC_MAMP20	24
#define DAC_MAMP21	25
#define DAC_MAMP22	26
#define DAC_MAMP23	27
#define DAC_DMAEN2	28
// SWTRIGR
#define DAC_SWTRIGR1	0
#define DAC_SWTRIGR2	1

//=== SPI регистры ===//
typedef struct{
	vu32 CR1;
	//u16 RESERVED0;
	vu32 CR2;
	//u16 RESERVED1;
	vu32 SR;
	//u16 RESERVED2;
	vu32 DR;
	//u16 RESERVED3;
	vu32 CRCPR;
	vu32 RXCRCR;
	//u16 RESERVED4;
	vu32 TXCRCR;
	//u16 RESERVED5;
	vu32 I2SCFGR;
	//u16 RESERVED6;
	vu32 I2SPR;
} SPI_TypeDef;
#define SPI1	((SPI_TypeDef *) SPI1_BASE)
#define SPI2	((SPI_TypeDef *) SPI2_BASE)
// CR1
#define SPI_CPHA	0
#define SPI_CPOL	1
#define SPI_MSTR	2
#define SPI_BR0	3
#define SPI_BR1	4
#define SPI_BR2	5
#define SPI_SPE	6
#define SPI_LSBFIRST	7
#define SPI_SSI	8
#define SPI_SSM	9
#define SPI_RXONLY	10
#define SPI_DFF	11
#define SPI_CRCNEXT	12
#define SPI_CRCEN	13
#define SPI_BIDIOE	14
#define SPI_BIDIMODE	15
// CR2
#define SPI_RXDMAEN	0
#define SPI_TXDMAEN	1
#define SPI_SSOE	2
#define SPI_ERRIE	5
#define SPI_RXNEIE	6
#define SPI_TXEIE	7
// SR
#define SPI_RXNE	0
#define SPI_TXE	1
#define SPI_CHSIDE	2
#define SPI_UDR	3
#define SPI_CRCERR	4
#define SPI_MODF	5
#define SPI_OVR	6
#define SPI_BSY	7
// I2SCFGR
#define SPI_CHLEN	0
#define SPI_DATLEN0	1
#define SPI_DATLEN1	2
#define SPI_CKPOL	3
#define SPI_I2SSTD0	4
#define SPI_I2SSTD1	5
#define SPI_PCMSYNC	7
#define SPI_I2SCFG0	8
#define SPI_I2SCFG1	9
#define SPI_I2SE	10
#define SPI_I2SMOD	11

//=== USB OTG глобальные регистры ядра ===//
typedef struct{		// 
	vu32 GOTGCTL;		// 0x000
	vu32 GOTGINT;
	vu32 GAHBCFG;
	vu32 GUSBCFG;
	vu32 GRSTCTL;		// 0x010
	vu32 GINTSTS;
	vu32 GINTMSK;
	vu32 GRXSTSR;
	vu32 GRXSTSP;		// 0x020
	vu32 GRXFSIZ;
	vu32 HNPIXFSIZ;
	vu32 HNPIXSTS;
	vu32 GI2CCTL;		// 0x030
	vu32 RESERVED2;
	vu32 GCCFG;
	vu32 CID;
	vu32 RESERVED[48];
	vu32 HPTXFSIZ;
	vu32 DIEPTXF[15];
} USBGOTG_TypeDef;
#define USBGOTG ((USBGOTG_TypeDef *) USBGOTG_BASE)
// GOTGCTL
#define USBGOTG_SRQSCS	0		// RO, был запрос сессии в режиме Device.
#define USBGOTG_SRQ	1		// Запрос сессии в режиме Device.
#define USBGOTG_HNGSCS	8		// RO, был запрос HNP в режиме Device.
#define USBGOTG_HNPRQ	9		// Запрос HNP в режиме Device.
#define USBGOTG_HSHNPEN	10		// Разрешение HNP в режиме Host.
#define USBGOTG_DHNPEN	11		// Разрешение HNP в режиме Device.
#define USBGOTG_CIDSTS	16		// RO, =0 - A-Device, =1 - B-Device.
#define USBGOTG_DBCT	17		// RO
#define USBGOTG_ASVLD	18		// RO, Device приконнектился (в Host-режиме).
#define USBGOTG_BSVLD	19		// RO, Host приконнектился.
// GOTGINT
#define USBGOTG_SEDET	2		// RO, напряжение VBUS ниже нормы.
#define USBGOTG_SRSSCHG	8		// RO, 
#define USBGOTG_HNSSCHG	9		// RO, 
#define USBGOTG_HNGDET	17		// RO, 
#define USBGOTG_ADTOCHG	18		// RO, 
#define USBGOTG_DBCDNE	19		// RO, Device приконнектился (в Host-режиме).
// GAHBCFG
#define USBGOTG_GINTMSK	0		// RW, разрешение прерываний USB.
#define USBGOTG_TXFELVL	7		// RW, 
#define USBGOTG_PTXFELVL	8		// RW, TxFIFO пуст (в Host-режиме).
// GUSBCFG
#define USBGOTG_TOCAL0	0		// RW, 
#define USBGOTG_TOCAL1	1		// RW, 
#define USBGOTG_TOCAL2	2		// RW, 
#define USBGOTG_PHYSEL	7		// WO, выбор FullSpeed.
#define USBGOTG_SRPCAP	8		// RW, разрешение SRP-протокола.
#define USBGOTG_HNPCAP	9		// RW, разрешение HNP-протокола.
#define USBGOTG_TRDT0	10		// RW, длительность клока в режиме Device.
#define USBGOTG_TRDT1	11		// 
#define USBGOTG_TRDT2	12		// 
#define USBGOTG_TRDT3	13		// 
#define USBGOTG_FHMOD	29		// RW, установка режима Host.
#define USBGOTG_FDMOD	30		// RW, установка режима Device.
#define USBGOTG_CTXPKT	31		// RW, 
// GRSTCTL
#define USBGOTG_CSRST	0		// RW, 
// GINTSTS
#define USBGOTG_CMOD	0		// RO, 
#define USBGOTG_MMIS	1		// RO, 
#define USBGOTG_OTGINT	2		// RO, 
#define USBGOTG_SOF	3		// RO, 
#define USBGOTG_RXFLVL	4		// RO, 
#define USBGOTG_NPTXFE	5		// RO, 
#define USBGOTG_GINAKEFF	6		// RO, 
#define USBGOTG_GOUTNAKEFF	7		// RO, 
#define USBGOTG_ESUSP	10		// W1, 
#define USBGOTG_USBSUSP	11		// W1, 
#define USBGOTG_USBRST	12		// W1, 
#define USBGOTG_ENUMDNE	13		// W1, 
#define USBGOTG_ISOODRP	14		// W1, 
#define USBGOTG_EOPF	15		// W1, 
#define USBGOTG_IEPINT	18		// RO, 
#define USBGOTG_OEPINT	19		// RO, 
#define USBGOTG_IISOIXFR	20		// W1, 
#define USBGOTG_IPXFR	21		// W1, 
#define USBGOTG_HPRTINT	24		// RO, есть прерывания от устройства.
#define USBGOTG_HCINT	25		// RO, 
#define USBGOTG_PTXFE	26		// RO, 
#define USBGOTG_CIDSCHG	28		// W1, 
#define USBGOTG_DISCINT	29		// W1, устройство отключилось.
#define USBGOTG_SRQINT	30		// W1, 
#define USBGOTG_WKUINT	31		// W1, 
// GINTMSK
#define USBGOTG_MMISM	1		// RW, разрешение прерывания 
#define USBGOTG_OTGINT	2		// RW, разрешение прерывания OTG.
#define USBGOTG_SOFM	3		// RW, разрешение прерывания SOF.
#define USBGOTG_RXFLVLM	4		// RW, разрешение прерывания 
#define USBGOTG_NPTXFEM	5		// RW, разрешение прерывания 
#define USBGOTG_GINAKEFFM	6		// RW, разрешение прерывания 
#define USBGOTG_GONAKEFFM	7		// RW, разрешение прерывания 
#define USBGOTG_ESUSPM	10		// RW, разрешение прерывания 
#define USBGOTG_USBSUSPM	11		// RW, разрешение прерывания 
#define USBGOTG_USBRST	12		// RW, разрешение прерывания 
#define USBGOTG_ENUMDNEM	13		// RW, разрешение прерывания 
#define USBGOTG_ISOODRPM	14		// RW, разрешение прерывания 
#define USBGOTG_EOPFM	15		// RW, разрешение прерывания 
#define USBGOTG_EPMISM	17		// RW, разрешение прерывания 
#define USBGOTG_IEPINT	18		// RW, разрешение прерывания 
#define USBGOTG_OEPINT	19		// RW, разрешение прерывания 
#define USBGOTG_IISOIXFRM	20		// RW, разрешение прерывания 
#define USBGOTG_IPXFRM	21		// RW, разрешение прерывания 
#define USBGOTG_PRTIM	24		// RW, разрешение прерывания Host Port.
#define USBGOTG_HCIM	25		// RW, разрешение прерывания Host Channels.
#define USBGOTG_PTXFEM	26		// RW, разрешение прерывания 
#define USBGOTG_CIDSCHGM	28		// RW, разрешение прерывания 
#define USBGOTG_DISCIM	29		// RW, разрешение прерывания отключения Device.
#define USBGOTG_SRQIM	30		// RW, разрешение прерывания новой сессии.
#define USBGOTG_WUIM	31		// RW, разрешение прерывания 
// GCCFG
#define USBGOTG_PWRDWN	16		// RW, =1 - приемопередатчик запущен.
#define USBGOTG_VBUSASEN	18		// RW, разрешено определение A-device.
#define USBGOTG_VBUSBSEN	19		// RW, разрешено определение B-device.
#define USBGOTG_SOFOUTEN	20		// RW, импульс SOF разрешен на выводе.

//=== USB OTG регистры Host-режима ===//
typedef struct{		// 
	vu32 HCFG;		// 0x400
	vu32 HCIR;
	vu32 HFNUM;
	vu32 RESERVED1;
	vu32 HPTXSTS;		// 0x410
	vu32 HAINT;
	vu32 HAINTMSK;
	vu32 RESERVED2[9];
	vu32 HPRT;		// 0x440
	vu32 RESERVED3[48];

	vu32 HCCHAR0;		// 0x500
	vu32 RESERVED00;
	vu32 HCINT0;		// 0x508
	vu32 HCINTMSK0;		// 0x50C
	vu32 HCTSIZ0;		// 0x510
	vu32 RESERVED01[3];

	vu32 HCCHAR1;		// 0x520
	vu32 RESERVED10;
	vu32 HCINT1;		// 0x528
	vu32 HCINTMSK1;		// 0x52C
	vu32 HCTSIZ1;		// 0x530
	vu32 RESERVED11[3];

	vu32 HCCHAR2;		// 0x540
	vu32 RESERVED20;
	vu32 HCINT2;		// 0x548
	vu32 HCINTMSK2;		// 0x54C
	vu32 HCTSIZ2;		// 0x550
	vu32 RESERVED21[3];

	vu32 HCCHAR3;		// 0x560
	vu32 RESERVED30;
	vu32 HCINT3;		// 0x568
	vu32 HCINTMSK3;		// 0x56C
	vu32 HCTSIZ3;		// 0x570
	vu32 RESERVED31[3];

	vu32 HCCHAR4;		// 0x580
	vu32 RESERVED40;
	vu32 HCINT4;		// 0x588
	vu32 HCINTMSK4;		// 0x58C
	vu32 HCTSIZ4;		// 0x590
	vu32 RESERVED41[3];

	vu32 HCCHAR5;		// 0x5A0
	vu32 RESERVED50;
	vu32 HCINT5;		// 0x5A8
	vu32 HCINTMSK5;		// 0x5AC
	vu32 HCTSIZ5;		// 0x5B0
	vu32 RESERVED51[3];

	vu32 HCCHAR6;		// 0x5C0
	vu32 RESERVED60;
	vu32 HCINT6;		// 0x5C8
	vu32 HCINTMSK6;		// 0x5CC
	vu32 HCTSIZ6;		// 0x5D0
	vu32 RESERVED61[3];

	vu32 HCCHAR7;		// 0x5E0
	vu32 RESERVED70;
	vu32 HCINT7;		// 0x5E8
	vu32 HCINTMSK7;		// 0x5EC
	vu32 HCTSIZ7;		// 0x5F0
	vu32 RESERVED71[3];
} USBHOTG_TypeDef;
#define USBHOTG ((USBHOTG_TypeDef *) USBHOTG_BASE)
// HCFG
#define USBHOTG_FSLSPCS0	0		// RW, =01 - для FS.
#define USBHOTG_FSLSPCS1	1		// RW, =10 - для LS.
#define USBHOTG_FSLSS	2		// RO, 
// HPRT		// в Host-режиме.
#define USBHOTG_PCSTS	0		// RO, устройство подключилось к порту.
#define USBHOTG_PCDET	1		// W1, триггер подключения Device.
#define USBHOTG_PENA	2		// W0, отключение порта.
#define USBHOTG_PENCHNG	3		// W1, 
#define USBHOTG_POCA	4		// RO, прошло условие перегрузки.
#define USBHOTG_POCCHNG	5		// W1, снять условие перегрузки.
#define USBHOTG_PRES	6		// RW, выставить Resume.
#define USBHOTG_PSUSP	7		// RW, в режим Suspend.
#define USBHOTG_PRST	8		// RW, послать RST.
#define USBHOTG_PLSTS0	10		// RO, =01 - для FS.
#define USBHOTG_PLSTS1	11		// RO, =10 - для LS.
#define USBHOTG_PPWR	12		// RW, включение питания.
#define USBHOTG_PTCTL0	13		// RW, 
#define USBHOTG_PTCTL1	14		// RW, 
#define USBHOTG_PTCTL2	15		// RW, 
#define USBHOTG_PTCTL3	16		// RW, 
#define USBHOTG_PSPD0	17		// RO, =01 - для FS.
#define USBHOTG_PSPD1	18		// RO, =10 - для LS.

//=== USB OTG регистры Device ===//
typedef struct{		// 
	vu32 DCFG;		// 0x800
	vu32 DCTL;
	vu32 DSTS;
	vu32 RESERVED1;
	vu32 DIEPMSK;		// 0x810
	vu32 DOEPMSK;		// 0x814
	vu32 DAINT;		// 0x818
	vu32 DAINTMSK;		// 0x81C
	vu32 RESERVED2[2];
	vu32 DVBUSDIS;		// 0x828
	vu32 DVBUSPULSE;		// 0x82C
	vu32 RESERVED3;
	vu32 DIEPEMPMSK;		// 0x834
	vu32 RESERVED4[51];

	vu32 DIEPCTL0;		// 0x900
	vu32 RESERVED01;
	vu32 DIEPINT0;		// 0x908
	vu32 RESERVED02;
	vu32 DIEPTSIZ0;		// 0x910
	vu32 RESERVED03;
	vu32 DTXFSTS0;		// 0x918
	vu32 RESERVED04;

	vu32 DIEPCTL1;		// 0x920
	vu32 RESERVED11;
	vu32 DIEPINT1;		// 0x928
	vu32 RESERVED12;
	vu32 DIEPTSIZ1;		// 0x930
	vu32 RESERVED13;
	vu32 DTXFSTS1;		// 0x938
	vu32 RESERVED14;

	vu32 DIEPCTL2;		// 0x940
	vu32 RESERVED21;
	vu32 DIEPINT2;		// 0x948
	vu32 RESERVED22;
	vu32 DIEPTSIZ2;		// 0x950
	vu32 RESERVED23;
	vu32 DTXFSTS2;		// 0x958
	vu32 RESERVED24;

	vu32 DIEPCTL3;		// 0x960
	vu32 RESERVED31;
	vu32 DIEPINT3;		// 0x968
	vu32 RESERVED32;
	vu32 DIEPTSIZ3;		// 0x970
	vu32 RESERVED33;
	vu32 DTXFSTS3;		// 0x978
	vu32 RESERVED34;

	vu32 DOEPCTL0;		// 0xB00
	vu32 RESERVED40;
	vu32 DOEPINT0;		// 0xB08
	vu32 RESERVED41;
	vu32 DOEPTSIZ0;		// 0xB10
	vu32 RESERVED42[3];		// 0xB14-0xB1C

	vu32 DOEPCTL1;		// 0xB20
	vu32 RESERVED43;
	vu32 DOEPINT1;		// 0xB28
	vu32 RESERVED44;
	vu32 DOEPTSIZ1;		// 0xB30
	vu32 RESERVED45[3];		// 0xB34-0xB3C

	vu32 DOEPCTL2;		// 0xB40
	vu32 RESERVED46;
	vu32 DOEPINT2;		// 0xB48
	vu32 RESERVED47;
	vu32 DOEPTSIZ2;		// 0xB50
	vu32 RESERVED48[3];		// 0xB54-0xB5C

	vu32 DOEPCTL3;		// 0xB60
	vu32 RESERVED49;
	vu32 DOEPINT3;		// 0xB68
	vu32 RESERVED50;
	vu32 DOEPTSIZ3;		// 0xB70
	vu32 RESERVED51[3];		// 0xB74-0xB7C
} USBDOTG_TypeDef;
#define USBDOTG ((USBDOTG_TypeDef *) USBDOTG_BASE)
// DCFG
#define USBDOTG_DSPD0	0		// RW, скорость устройства.
#define USBDOTG_DSPD1	1		// RW, 
#define USBDOTG_NZLSOHSK	2		// RW, 
#define USBDOTG_DAD0	4		// RW, адрес устройства.
#define USBDOTG_DAD1	5		// RW, 
#define USBDOTG_DAD2	6		// RW, 
#define USBDOTG_DAD3	7		// RW, 
#define USBDOTG_DAD4	8		// RW, 
#define USBDOTG_DAD5	9		// RW, 
#define USBDOTG_DAD6	10		// RW, 
#define USBDOTG_PFIVL0	11		// RW, 
#define USBDOTG_PFIVL1	12		// RW, 

//=== USB OTG регистры питания ===//
typedef struct{		// 
	vu32 PCGCCTL;		// 0xE00
} USBPOTG_TypeDef;
#define USBPOTG ((USBPOTG_TypeDef *) USBPOTG_BASE)
// PCGCCTL
#define USBPOTG_STPPCLK	0		// RW, =1 - STOP PHY.
#define USBPOTG_GATEHCLK	1		// RW, 
#define USBPOTG_PHYSUSP	4		// RW, в режиме Suspend.

//=== USB OTG регистры Host-каналов ===//
typedef struct{		// 
	vu32 DFIFO0_IN;		// Смещение 0x1000
	vu32 DFIFO0_OUT;
	vu32 RESERVED[62];
} USBHCOTG_TypeDef;
#define USBHCOTG ((USBHCOTG_TypeDef *) USBHCOTG_BASE)

//=== TIM6,7 регистры ===//
typedef struct{
	vu32 CR1;
	vu32 CR2;
	vu32 Res1;
	vu32 DIER;
	vu32 SR;
	vu32 EGR;
	vu32 Res2;
	vu32 Res3;
	vu32 Res4;
	vu32 CNT;
	vu32 PSC;
	vu32 ARR;
} TIM6_7_TypeDef;
#define TIM6	((TIM6_7_TypeDef *) TIM6_BASE)
#define TIM7	((TIM6_7_TypeDef *) TIM7_BASE)

// CR1
#define TIM6_CEN	0
#define TIM6_UDIS	1
#define TIM6_URS	2
#define TIM6_OPM	3
#define TIM6_ARPE	7
// CR2
#define TIM6_MMS0	4
#define TIM6_MMS1	5
#define TIM6_MMS2	6
// DIER
#define TIM6_UIE	0
#define TIM6_UDE	8
// SR
#define TIM6_UIF	0
// EGR
#define TIM6_UG	0

//=== TIM1,8 регистры ===//
typedef struct{
	vu32 CR1;
	vu32 CR2;
	vu32 SMCR;
	vu32 DIER;
	vu32 SR;
	vu32 EGR;
	vu32 CCMR1;
	vu32 CCMR2;
	vu32 CCER;
	vu32 CNT;
	vu32 PSC;
	vu32 ARR;
	vu32 RCR;
	vu32 CCR1;
	vu32 CCR2;
	vu32 CCR3;
	vu32 CCR4;
	vu32 BDTR;
	vu32 DCR;
	vu32 DMAR;
} TIM1_TypeDef;
#define TIM1	((TIM1_TypeDef *) TIM1_BASE)
#define TIM8	((TIM1_TypeDef *) TIM8_BASE)
// CR1
#define TIM1_CEN	0
#define TIM1_UDIS	1
#define TIM1_URS	2
#define TIM1_OPM	3
#define TIM1_DIR	4
#define TIM1_CMS0	5
#define TIM1_CMS1	6
#define TIM1_ARPE	7
#define TIM1_CKD0	8
#define TIM1_CKD1	9
// CR2
#define TIM1_CCPC	0
#define TIM1_CCUS	2
#define TIM1_CCDS	3
#define TIM1_MMS0	4
#define TIM1_MMS1	5
#define TIM1_MMS2	6
#define TIM1_TI1S	7
#define TIM1_OIS1	8
#define TIM1_OIS1N	9
#define TIM1_OIS2	10
#define TIM1_OIS2N	11
#define TIM1_OIS3	12
#define TIM1_OIS3N	13
#define TIM1_OIS4	14
// SMCR
#define TIM1_SMS0	0
#define TIM1_SMS1	1
#define TIM1_SMS2	2
#define TIM1_TS0	4
#define TIM1_TS1	5
#define TIM1_TS2	6
#define TIM1_MSM	7
#define TIM1_ETF0	8
#define TIM1_ETF1	9
#define TIM1_ETF2	10
#define TIM1_ETF3	11
#define TIM1_ETPS0	12
#define TIM1_ETPS1	13
#define TIM1_ECE	14
#define TIM1_ETP	15
// DIER
#define TIM1_UIE	0
#define TIM1_CC1IE	1
#define TIM1_CC2IE	2
#define TIM1_CC3IE	3
#define TIM1_CC4IE	4
#define TIM1_COMIE	5
#define TIM1_TIE	6
#define TIM1_BIE	7
#define TIM1_UDE	8
#define TIM1_CC1DE	9
#define TIM1_CC2DE	10
#define TIM1_CC3DE	11
#define TIM1_CC4DE	12
#define TIM1_COMDE	13
#define TIM1_TDE	14
// SR
#define TIM1_UIF	0
#define TIM1_CC1IF	1
#define TIM1_CC2IF	2
#define TIM1_CC3IF	3
#define TIM1_CC4IF	4
#define TIM1_COMIF	5
#define TIM1_TIF	6
#define TIM1_BIF	7
#define TIM1_CC1OF	9
#define TIM1_CC2OF	10
#define TIM1_CC3OF	11
#define TIM1_CC4OF	12
// EGR
#define TIM1_UG	0
#define TIM1_CC1G	1
#define TIM1_CC2G	2
#define TIM1_CC3G	3
#define TIM1_CC4G	4
#define TIM1_COMG	5
#define TIM1_TG	6
#define TIM1_BG	7
// CCMR1
#define TIM1_CC1S0	0
#define TIM1_CC1S1	1
#define TIM1_OC1FE	2
#define TIM1_OC1PE	3
#define TIM1_OC1M0	4
#define TIM1_OC1M1	5
#define TIM1_OC1M2	6
#define TIM1_OC1CE	7
#define TIM1_CC2S0	8
#define TIM1_CC2S1	9
#define TIM1_OC2FE	10
#define TIM1_OC2PE	11
#define TIM1_OC2M0	12
#define TIM1_OC2M1	13
#define TIM1_OC2M2	14
#define TIM1_OC2CE	15
// CCMR2
#define TIM1_CC3S0	0
#define TIM1_CC3S1	1
#define TIM1_OC3FE	2
#define TIM1_OC3PE	3
#define TIM1_OC3M0	4
#define TIM1_OC3M1	5
#define TIM1_OC3M2	6
#define TIM1_OC3CE	7
#define TIM1_CC4S0	8
#define TIM1_CC4S1	9
#define TIM1_OC4FE	10
#define TIM1_OC4PE	11
#define TIM1_OC4M0	12
#define TIM1_OC4M1	13
#define TIM1_OC4M2	14
#define TIM1_OC4CE	15
// CCER
#define TIM1_CC1E	0
#define TIM1_CC1P	1
#define TIM1_CC1NE	2
#define TIM1_CC1NP	3
#define TIM1_CC2E	4
#define TIM1_CC2P	5
#define TIM1_CC2NE	6
#define TIM1_CC2NP	7
#define TIM1_CC3E	8
#define TIM1_CC3P	9
#define TIM1_CC3NE	10
#define TIM1_CC3NP	11
#define TIM1_CC4E	12
#define TIM1_CC4P	13
// BDTR
#define TIM1_DTG0		0
#define TIM1_DTG1		1
#define TIM1_DTG2		2
#define TIM1_DTG3		3
#define TIM1_DTG4		4
#define TIM1_DTG5		5
#define TIM1_DTG6		6
#define TIM1_DTG7		7
#define TIM1_LOCK0	8
#define TIM1_LOCK1	9
#define TIM1_OSSI	10
#define TIM1_OSSR	11
#define TIM1_BKE	12
#define TIM1_BKP	13
#define TIM1_AOE	14
#define TIM1_MOE	15

//=== I2C ===//
typedef struct{
	vu16 CR1;
	u16 RESERVED0;
	vu16 CR2;
	u16 RESERVED1;
	vu16 OAR1;
	u16 RESERVED2;
	vu16 OAR2;
	u16 RESERVED3;
	vu16 DR;
	u16 RESERVED4;
	vu16 SR1;
	u16 RESERVED5;
	vu16 SR2;
	u16 RESERVED6;
	vu16 CCR;
	u16 RESERVED7;
	vu16 TRISE;		// Регистр режима перепада.
	u16 RESERVED8;
} I2C_TypeDef;
#define I2C1	((I2C_TypeDef *) I2C1_BASE)
#define I2C2	((I2C_TypeDef *) I2C2_BASE)
// CR1 - 
#define I2C_PE	0		// 
#define I2C_SMBUS	1		// 
#define I2C_SMBTYPE	3		// 
#define I2C_ENARP	4		// 
#define I2C_ENPEC	5		// 
#define I2C_ENGC	6		// 
#define I2C_NOSTR	7		// 
#define I2C_START	8		// 
#define I2C_STOP	9		// 
#define I2C_ACK	10		// 
#define I2C_POS	11		// 
#define I2C_PEC	12		// 
#define I2C_ALERT	13		// 
#define I2C_SWRST	15		// 
// CR2 - 
#define I2C_FREC0	0		// 
#define I2C_FREC1	1		// 
#define I2C_FREC2	2		// 
#define I2C_FREC3	3		// 
#define I2C_FREC4	4		// 
#define I2C_FREC5	5		// 
#define I2C_ITERREN	8		// 
#define I2C_ITEVTEN	9		// 
#define I2C_ITBUFEN	10		// 
#define I2C_DMAEN	11		// 
#define I2C_LAST	12		// 
// OAR1 - регистр одиночного адреса 1.
#define I2C_ADDMODE	15		// Режим адресации ведомого.
// OAR2 - регистр одиночного адреса 2.
#define I2C_ENDUAL	0		// Режим двойной адресации.
// SR1 - регистр статуса 1.
#define I2C_SB	0		// 
#define I2C_ADDR	1		// 
#define I2C_BTF	2		// 
#define I2C_ADD10	3		// 
#define I2C_STOPF	4		// 
#define I2C_RxEN	6		// 
#define I2C_TxE	7		// 
#define I2C_BERR	8		// 
#define I2C_ARLO	9		// 
#define I2C_AF	10		// 
#define I2C_OVR	11		// 
#define I2C_PECERR	12		// 
#define I2C_TIMEOUT	14		// 
#define I2C_SMBALERT	15		// 
// SR2 - регистр статуса 2.
#define I2C_MSL	0		// 
#define I2C_BUSY	1		// 
#define I2C_TRA	2		// 
#define I2C_GENCALL	4		// 
#define I2C_SMBDEFAULT	5		// 
#define I2C_SMBHOST	6		// 
#define I2C_DUALF	7		// 
// CCR - регистр управления тактированием.
#define I2C_DUTY	14		// 
#define I2C_F_S	15		// Выбор режима мастера

//=== SysTick регистры ===//
typedef struct{
	vu32 CTRL;		// Регистр управления.
	vu32 LOAD;		// Регистр перезагрузки.
	vu32 VAL;		// Текущее значение.
	vu32 CALIB;		// Регистр калибровки.
} SysTick_TypeDef;
#define STK ((SysTick_TypeDef *) SysTick_BASE)
// CTRL - регистр управления
#define STK_ENABLE	0		// Разрешение счетчика.
#define STK_TICKINT	1		// Разрешение прерывания от таймера.
#define STK_CLKSOURCE	2		// Выбор источника =0 - AHB/8, =1 - AHB.
#define STK_COUNTFLAG	16		// Флаг прерывания от таймера.
// LOAD - регистр перезагрузки, загружать N-1.
// CALIB - регистр калибровки
#define STK_NOREF	31		// 
#define STK_SKEW	30		// 

//=== NVIC регистры ===//
typedef struct{
	vu32 Enable[3];		// Разрешение источников.
	u32 RESERVED0[29];
	vu32 Disable[3];		// Запрещение источников.
	u32 RSERVED1[29];
	vu32 Set[3];		// 
	u32 RESERVED2[29];
	vu32 Clear[3];		// 
	u32 RESERVED3[29];
	vu32 Active[3];		// Чтение активного прерывания.
	u32 RESERVED4[61];
	vu32 Priority[12];		// 
} NVIC_TypeDef;
#define NVIC ((NVIC_TypeDef *) NVIC_BASE)
// Enable[0] - регистр 0 разрешения источников прерываний
#define NVIC_WWDG	0
#define NVIC_PVD	1
#define NVIC_TAMPER	2
#define NVIC_RTC	3
#define NVIC_FLASH	4
#define NVIC_RCC	5
#define NVIC_EXTI0	6
#define NVIC_EXTI1	7
#define NVIC_EXTI2	8
#define NVIC_EXTI3	9
#define NVIC_EXTI4	10
#define NVIC_DMA_Ch1	11
#define NVIC_DMA_Ch2	12
#define NVIC_DMA_Ch3	13
#define NVIC_DMA_Ch4	14
#define NVIC_DMA_Ch5	15
#define NVIC_DMA_Ch6	16
#define NVIC_DMA_Ch7	17
#define NVIC_ADC	18
#define NVIC_CAN1_TX	19
#define NVIC_CAN1_RX0	20
#define NVIC_CAN1_RX1	21
#define NVIC_CAN1_RCE	22
#define NVIC_EXTI9_5	23
#define NVIC_TIM1_BRK	24
#define NVIC_TIM1_UP	25
#define NVIC_TIM1_TRG	26
#define NVIC_TIM1_CC	27
#define NVIC_TIM2	28		// 
#define NVIC_TIM3	29
#define NVIC_TIM4	30
#define NVIC_I2C1_EV	31
// Enable[1] - регистр 1 разрешения источников прерываний
#define NVIC_I2C1_ER	0
#define NVIC_I2C2_EV	1
#define NVIC_I2C2_ER	2
#define NVIC_SPI1	3
#define NVIC_SPI2	4
#define NVIC_USART1	5		// 
#define NVIC_USART2	6
#define NVIC_USART3	7
#define NVIC_EXTI15_10	8
#define NVIC_RTCAlarm	9
#define NVIC_USB_Wake	10
#define NVIC_TIM5	18
#define NVIC_SPI3	19
#define NVIC_UART4	20
#define NVIC_UART5	21
#define NVIC_TIM6	22
#define NVIC_TIM7	23
#define NVIC_DMA2_Ch1	24
#define NVIC_DMA2_Ch2	25
#define NVIC_DMA2_Ch3	26
#define NVIC_DMA2_Ch4	27
#define NVIC_DMA2_Ch5	28
#define NVIC_ETH	29
#define NVIC_ETH_WKUP	30
#define NVIC_CAN2_TX	31
// Enable[2] - регистр 2 разрешения источников прерываний
#define NVIC_CAN2_RX0	0
#define NVIC_CAN2_RX1	1
#define NVIC_CAN2_SCE	2
#define NVIC_OTG_FS	3

// Приоритеты прерываний.
//Priority[0]=RTC_IRQHandler,TAMPER_IRQHandler,PVD_IRQHandler,WWDG_IRQHandler,
//Priority[1]=EXTI1_IRQHandler,EXTI0_IRQHandler,RCC_IRQHandler,FLASH_IRQHandler,
//Priority[2]=DMA1_Channel1_IRQHandler,EXTI4_IRQHandler,EXTI3_IRQHandler,EXTI2_IRQHandler,
//Priority[3]=DMA1_Channel5_IRQHandler,DMA1_Channel4_IRQHandler,DMA1_Channel3_IRQHandler,DMA1_Channel2_IRQHandler,
//Priority[4]=Reserv,ADC1_IRQHandler,DMA1_Channel7_IRQHandler,DMA1_Channel6_IRQHandler,
//Priority[5]=Reserv
//Priority[6]=TIM1_TRG_COM_TIM17_IRQHandler,TIM1_UP_TIM16_IRQHandler,TIM1_BRK_TIM15_IRQHandler,EXTI9_5_IRQHandler,
//Priority[7]=TIM4_IRQHandler,TIM3_IRQHandler,TIM2_IRQHandler,TIM1_CC_IRQHandler,
//Priority[8]=I2C2_ER_IRQHandler,I2C2_EV_IRQHandler,I2C1_ER_IRQHandler,I2C1_EV_IRQHandler,
//Priority[9]=USART2_IRQHandler,USART1_IRQHandler,SPI2_IRQHandler,SPI1_IRQHandler,
//Priority[10]=CEC_IRQHandler,RTCAlarm_IRQHandler,EXTI15_10_IRQHandler,USART3_IRQHandler,
//Priority[11]= , ,TIM7_IRQHandler,TIM6_DAC_IRQHandler,


//=== SCB регистры ===//
typedef struct{
	vu32 CPUID;
	vu32 ICSR;
	vu32 VTOR;		// Смещение таблицы векторов.
	vu32 AIRCR;
	vu32 SCR;
	vu32 CCR;		// Регистр управления и конфигурации.
	vu32 SHPR1;
	vu32 SHPR2;
	vu32 SHPR3;
	vu32 SHCSR;
	vu32 CFSR;
	vu32 HFSR;
	vu32 MMFAR;
	vu32 BFAR;
} SCB_TypeDef;
#define SCB	((SCB_TypeDef *) SCB_BASE)		// Блок системного управления.
// ICSR - регистр управления и состояния прерываний.
#define SCB_RETOBASE	11		// 
// VTOR - регистр смещения таблицы векторов.
#define SCB_TBLBASE	29		// 
// AIRCR
#define SCB_VECTRESET	0
#define SCB_VECTCLRACTIVE	1
#define SCB_SYSRESETREQ	2
#define SCB_PRIGROUP0	8
#define SCB_PRIGROUP1	9
#define SCB_PRIGROUP2	10
#define SCB_ENDIANESS	15
// SCR
#define SCB_SLEEPONEXIT	1
#define SCB_SLEEPDEEP	2
#define SCB_SEVONPEND	4
// CCR
#define SCB_NONBASE	0
#define SCB_USERSET	1
#define SCB_UNALIGN	3
#define SCB_DIV	4
#define SCB_BFHF	8
#define SCB_STKALIGN	9

//=== Процедуры обработчиков прерываний ===//
void NMIException(void);
void HardFaultException(void);
void MemManageException(void);
void BusFaultException(void);
void UsageFaultException(void);
void DebugMonitor(void);
void SVCHandler(void);
void PendSVC(void);
void SysTickHandler(void);
void WWDG_IRQHandler(void);		// IRQ0 - 0000_0040
void PVD_IRQHandler(void);		// 
void TAMPER_IRQHandler(void);		// 
void RTC_IRQHandler(void);		// 
void FLASH_IRQHandler(void);		// 
void RCC_IRQHandler(void);		// 
void EXTI0_IRQHandler(void);		// IRQ6
void EXTI1_IRQHandler(void);		// IRQ7
void EXTI2_IRQHandler(void);		// IRQ8
void EXTI3_IRQHandler(void);		// IRQ9
void EXTI4_IRQHandler(void);		// IRQ10
void DMA1Channel1_IRQHandler(void);		// 
void DMA1Channel2_IRQHandler(void);		// 
void DMA1Channel3_IRQHandler(void);		// 
void DMA1Channel4_IRQHandler(void);		// 
void DMA1Channel5_IRQHandler(void);		// 
void DMA1Channel6_IRQHandler(void);		// 
void DMA1Channel7_IRQHandler(void);		// 
void ADC_IRQHandler(void);		// IRQ18
void USB_HP_CAN_TX_IRQHandler(void);		// IRQ19
void USB_LP_CAN_RX0_IRQHandler(void);		// IRQ20
void CAN_RX1_IRQHandler(void);		// IRQ21
void CAN_SCE_IRQHandler(void);		// IRQ22
void EXTI9_5_IRQHandler(void);		// IRQ23
void TIM1_BRK_IRQHandler(void);		// IRQ24
void TIM1_UP_IRQHandler(void);		// IRQ25
void TIM1_TRG_CCUP_IRQHandler(void);		// IRQ26
void TIM1_CC_IRQHandler(void);		// IRQ27
void TIM2_IRQHandler(void);		// IRQ28
void TIM3_IRQHandler(void);		// IRQ29
void TIM4_IRQHandler(void);		// IRQ30
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);
void SPI1_IRQHandler(void);		// IRQ35 (3)
void SPI2_IRQHandler(void);
void USART1_IRQHandler(void);		// IRQ37 (5)
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void RTCAlarm_IRQHandler(void);
void USBWakeUp_IRQHandler(void);		// IRQ42 (10)

void TIM5_IRQHandler(void);
void SPI3_IRQHandler(void);
void USART4_IRQHandler(void);
void USART5_IRQHandler(void);
void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void);
void DMA2Channel1_IRQHandler(void);
void DMA2Channel2_IRQHandler(void);
void DMA2Channel3_IRQHandler(void);
void DMA2Channel4_IRQHandler(void);
void DMA2Channel5_IRQHandler(void);
void ETH_IRQHandler(void);
void ETH_WKUP_IRQHandler(void);
void CAN2_TX_IRQHandler(void);
void CAN2_RX0_IRQHandler(void);
void CAN2_RX1_IRQHandler(void);
void CAN2_SCE_IRQHandler(void);
void OTG_FS_IRQHandler(void);

#endif
