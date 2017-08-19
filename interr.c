#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h>
#include "vars.h"
#include "watch.h"

void SysTick_Handler(void){
	STK->CTRL &= ~BIT(STK_COUNTFLAG);		// Снять флаг прерывания.
	vu8 i;
	if(CntTimeRxD<20){
		CntTimeRxD++;		// RXD0.
	}
	else{
			if(chList[chCOM].ptrIN >2){		//
					if(chList[chCOM].chState & chEnaData) {chList[chCOM].chState |= chPakInOFlow;} 	// 
					for(i=0;i<chList[chCOM].ptrIN;i++) {chList[chCOM].PakIN[i]=chList[chCOM].buffIN[i];} // 
					chList[chCOM].PakINLen=chList[chCOM].ptrIN;
					chList[chCOM].chState |=chEnaData;
					chList[chCOM].ptrIN=0;
					}
	}
	
	if(++Cnt10mSec>10){ // 10 мсек
		Cnt10mSec=0;
		FlTime |=BIT(1);
	}
	if(++Cnt100mSec>100){ // 100 мсек
		Cnt100mSec=0;
		Cnt1Sec++;
		FlTime |=BIT(2);
	}
	if(Cnt1Sec>10){ // 1 сек
		Cnt1Sec=0;
		Cnt1Min++;
		FlTime |=BIT(3);
	}
	if(Cnt1Min>60){ // 1 мин
		Cnt1Min=0;
		FlTime |=BIT(4);
	}
// PacketCycle();
	Working();
}

void USART1_IRQHandler(void){
vu8 dd, i;
vu16 status;
status=USART1->SR;
	if(status & BIT(USART_RXNE)){		// принят байт
		USART1->SR &= ~BIT(USART_RXNE);	// На всякий случай.
		if(CntTimeRxD>=20){
			chList[chCOM].ptrIN=0;		// Новый пакет, на начало.
		}
		dd=USART1->DR;
		CntTimeRxD=0; 
		if(chList[chCOM].ptrIN>=255) chList[chCOM].ptrIN=255;
		chList[chCOM].buffIN[chList[chCOM].ptrIN++]=dd;		// DD записали в буф.
	}
	else if(status & BIT(USART_TXE)){		// Буфер передачи пуст.
	  if((COM_mode & BIT(5))==0){   // Уходит не последний байт.
      if(chList[chCOM].ptrOUT < (255)) chList[chCOM].ptrOUT++;
			else{
					COM_mode |=BIT(5);		// В конце выдачи последнего байта разрешим прием.
					chList[chCOM].chState &= ~chSend;		// Закончилась передача в СОМ.
			}
      if(chList[chCOM].ptrOUT>=chList[chCOM].buffOUTLen){		// Байт был последний.
        COM_mode |=BIT(5);    // В конце выдачи последнего байта разрешим прием.
        chList[chCOM].chState &= ~chSend;		// Закончилась передача в СОМ1.
      }
      else{
        i=chList[chCOM].ptrOUT;
        USART1->DR=chList[chCOM].buffOUT[i];		// Выдаём очередной байт.
      }
	  }else if (status & BIT(USART_TC)){
      USART1->SR &= ~BIT(USART_TC);    // Снять флаг.
      COM_mode &= ~BIT(5);
      USART1->CR1 &= ~BIT(USART_TXEIE);   // Запрещено прерывание передачи в COM1.
      USART1->CR1 |=BIT(USART_RXNEIE);    // Разрешено прерывание приема COM1.
	  }
		if(status & BIT(USART_ORE)){ // Переполнение приема.  | BIT(USART_FE) | BIT(USART_NF))
			dd=USART1->SR;
			dd=USART1->DR;
		}
}
}

//=== Прерывания SPI2 ===//
void SPI2_IRQHandler(void){
vu8 data;
  if(SPI2->SR & BIT(SPI_TXE)){            // Буфер передачи пуст.
    data=SPI2->DR;          // Пришло. Этим также очищается флаг RXNE.
    BufFromSPI[PtrByteSPI]=data;            // Пришло.
    if(PtrByteSPI<CntByteSPI){              // Принят/послан не последний байт.
      SPI2->DR=Buf2SPI[PtrByteSPI];           // Передаем. Этим также очищается флаг TXE.
      PtrByteSPI++;
    }
    else{           // Принят/послан последний байт.
      ResetCS();           // Снять /CS.
      ResetSPIIE();           // Запретить прерывание.
      SPI_mode &= ~BIT(7);            // Освобождаем канал.
    }
  }
}