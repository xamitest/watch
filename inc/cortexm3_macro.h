//cortexm3_macro.h
#ifndef _macro_h
#define _macro_h
#define __IEEE_LITTLE_ENDIAN
//#pragma asm		
#define NOP() "mov r0, r0";	
#define CLI()	"cpsid i";		// Глобальный запрет прерываний.
#define SEI()	"cpsie i";		// Глобальное разрешение прерываний.
//#pragma endasm	// Аналог NOP(). 
	

#define WDR()	(IWDG->KR=0xAAAA)	 	// Перезагрузка IWDG.
#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

typedef volatile signed int vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef const unsigned int uc32;
typedef const unsigned short uc16;
typedef const unsigned char uc8;

typedef volatile unsigned int vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;

typedef volatile unsigned int const vuc32;
typedef volatile unsigned short const vuc16;
typedef volatile unsigned char const vuc8;

typedef enum {FALSE=0, TRUE= !FALSE} bool;

typedef enum {RESET=0, SET= !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE=0, ENABLE= !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) ((STATE==DISABLE) || (STATE==ENABLE))

typedef enum {ERROR=0, SUCCESS= !ERROR} ErrorStatus;

typedef double	Flo64;    // Double precision floating point
typedef double	* pFlo64;
typedef float	Flo32;    // Single precision floating point
typedef float	* pFlo32;
typedef signed long long Int64S;   // Signed 64 bit quantity
typedef signed long long  * pInt64S;
typedef unsigned long long Int64U;   // Unsigned 64 bit quantity
typedef unsigned long long  * pInt64U;
typedef signed int Int32S;   // Signed 32 bit quantity
typedef signed int * pInt32S;
typedef unsigned int Int32U;   // Unsigned 32 bit quantity
typedef unsigned int * pInt32U;
typedef signed short Int16S;   // Signed 16 bit quantity
typedef signed short * pInt16S;
typedef unsigned short Int16U;   // Unsigned 16 bit quantity
typedef unsigned short * pInt16U;
typedef signed char Int8S;    // Signed 8 bit quantity
typedef signed char * pInt8S;
typedef unsigned char Int8U;    // Unsigned 8 bit quantity
typedef unsigned char * pInt8U;
typedef unsigned char Boolean;  // Boolean
typedef unsigned char * pBoolean;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define _2BL(a)	(Int8U)(a),(Int8U)(a>>8)
#define _2BB(a)	(Int8U)(a>>8),(Int8U)(a),
#define _3BL(a)	(Int8U)(a),(Int8U)(a>>8),(Int8U)(a>>16)
#define _3BB(a)	(Int8U)(a>>16),(Int8U)(a>>8),(Int8U)(a)
#define _4BL(a)	(Int8U)(a),(Int8U)(a>>8),(Int8U)(a>>16),(Int8U)(a>>24)
#define _4BB(a)	(Int8U)(a>>24),(Int8U)(a>>16),(Int8U)(a>>8),(Int8U)(a)

typedef void * (*CommUserFpnt_t)(void *);
typedef void   (*VoidFpnt_t)(void);

#define U8_MAX	((u8)255)
#define S8_MAX	((s8)127)
#define S8_MIN	((s8)-128)
#define U16_MAX	((u16)65535u)
#define S16_MAX	((s16)32767)
#define S16_MIN	((s16)-32768)
#define U32_MAX	((u32)4294967295uL)
#define S32_MAX	((s32)2147483647)
#define S32_MIN	((s32)2147483648uL)

#define LongToBin(n) (((n>>21) & 0x80) | \
                      ((n>>18) & 0x40) | \
                      ((n>>15) & 0x20) | \
                      ((n>>12) & 0x10) | \
                      ((n>>9) & 0x08) | \
                      ((n>>6) & 0x04) | \
                      ((n>>3) & 0x02) | \
                      ((n) & 0x01))

#define __BIN(n) LongToBin(0x##n##l)

#define BIN8(n)	__BIN(n)
#define BIN(n)	__BIN(n)
#define BIN16(b1,b2)	((__BIN(b1)<< 8)+ __BIN(b2))
#define BIN32(b1,b2,b3,b4) ((((u32_t)__BIN(b1))<<24ul)+(((u32_t)__BIN(b2))<<16ul)+ \
                            (((u32_t)__BIN(b3))<<8ul)+(u32_t)__BIN(b4))

#ifndef BIT
//#define BIT(x)	(1<<(x)ul)
#define BIT(x)	(1<<(x))
#endif

void __WFI(void);
void __WFE(void);
void __SEV(void);
void __ISB(void);
void __DSB(void);
void __DMB(void);
void __SVC(void);
u32 __MRS_CONTROL(void);
void __MSR_CONTROL(u32 Control);
void __SETPRIMASK(void);
void __RESETPRIMASK(void);
void __SETFAULTMASK(void);
void __RESETFAULTMASK(void);
void __BASEPRICONFIG(u32 NewPriority);
u32 __GetBASEPRI(void);

#endif
