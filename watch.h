#ifndef _watch_h
#define _watch_h
#include <cortexm3_macro.h>
#include <../vars.h>

	/*
	   a
   ----
 f| 	 |b
	|__g_|
 e|    |c
	|		 |
  -----
		 d
	*/

#define a Peripheral_BB(GPIOA->ODR, 1) //pa1
#define b Peripheral_BB(GPIOA->ODR, 2) //pa2
#define c Peripheral_BB(GPIOA->ODR, 3) //pa3
#define d Peripheral_BB(GPIOA->ODR, 4) //pa4
#define e Peripheral_BB(GPIOA->ODR, 5) //pa5
#define f Peripheral_BB(GPIOA->ODR, 6) //pa6
#define g Peripheral_BB(GPIOA->ODR, 7) //pa7

#define dp24_d Peripheral_BB(GPIOB->ODR, 0) //pb0

#define DIG1 Peripheral_BB(GPIOB->ODR, 7) //pb7
#define DIG2 Peripheral_BB(GPIOB->ODR, 1) //pb1
#define DIG3 Peripheral_BB(GPIOB->ODR, 10) //pb10
#define DIG4 Peripheral_BB(GPIOB->ODR, 11) //pb11
#define pb5 Peripheral_BB(GPIOA->ODR, 0) //pb5

extern vu8 nwp;
extern vu8 ttp;
extern vu8 tpol;
extern vu16 blink;

extern vu8 TTime;
extern vu8 TTemp;
extern vu8 THum;
extern vu8 TPres;
extern vu8 Tco2;

void OutAll(vu8 seg1, vu8 seg2, vu8 seg3, vu8 seg4);
void OutSection(vu8 i);
void Blink(vu8 i);
void Working(void);
void Checknwp(void);
void CheckPoint(u8 seg, u8 who);

#endif
