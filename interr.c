#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h>
#include "vars.h"
#include "watch.h"

void SysTick_Handler(void){
	STK->CTRL &= ~BIT(STK_COUNTFLAG);		// ����� ���� ����������.
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
	if(CntTimeRxUSR<100){
		CntTimeRxUSR++;		//
	}
	else{
			if(chList[chUSR].ptrIN >=1){		//
					if(chList[chUSR].chState & chEnaData) {chList[chUSR].chState |= chPakInOFlow;} 	// 
					for(i=0;i<chList[chUSR].ptrIN;i++) {chList[chUSR].PakIN[i]=chList[chUSR].buffIN[i];} // 
					chList[chUSR].PakINLen=chList[chUSR].ptrIN;
					chList[chUSR].chState |=chEnaData;
					chList[chUSR].ptrIN=0;
					}
	}
	if(++Cnt10mSec>10){ // 10 ����
		Cnt10mSec=0;
		FlTime |=BIT(1);		
	}
	if(++Cnt100mSec>100){ // 100 ����
		Cnt100mSec=0;
		Cnt1Sec++;
		FlTime |=BIT(2);
		*DustLed ^=1;
	}
	if(Cnt1Sec>10){ // 1 ���
		Cnt1Sec=0;
		Cnt1Min++;
		FlTime |=BIT(3);
	}
	if(Cnt1Min>60){ // 1 ���
		Cnt1Min=0;
		FlTime |=BIT(4);
	}
// PacketCycle();
	if (hourDec>=23 || hourDec<=6) {
		Working(); // ���������� �������
	}
	Working();
}

void USART1_IRQHandler(void){
vu8 dd, i;
vu16 status;
status=USART1->SR;
	if(status & BIT(USART_RXNE)){		// ������ ����
		USART1->SR &= ~BIT(USART_RXNE);	// �� ������ ������.
		if(CntTimeRxD>=20){
			chList[chCOM].ptrIN=0;		// ����� �����, �� ������.
		}
		dd=USART1->DR;
		CntTimeRxD=0; 
		if(chList[chCOM].ptrIN>=255) chList[chCOM].ptrIN=255;
		chList[chCOM].buffIN[chList[chCOM].ptrIN++]=dd;		// DD �������� � ���.
	}
	else if(status & BIT(USART_TXE)){		// ����� �������� ����.
	  if((COM_mode & BIT(5))==0){   // ������ �� ��������� ����.
      if(chList[chCOM].ptrOUT < (255)) chList[chCOM].ptrOUT++;
			else{
					COM_mode |=BIT(5);		// � ����� ������ ���������� ����� �������� �����.
					chList[chCOM].chState &= ~chSend;		// ����������� �������� � ���.
			}
      if(chList[chCOM].ptrOUT>=chList[chCOM].buffOUTLen){		// ���� ��� ���������.
        COM_mode |=BIT(5);    // � ����� ������ ���������� ����� �������� �����.
        chList[chCOM].chState &= ~chSend;		// ����������� �������� � ���1.
      }
      else{
        i=chList[chCOM].ptrOUT;
        USART1->DR=chList[chCOM].buffOUT[i];		// ����� ��������� ����.
      }
	  }else if (status & BIT(USART_TC)){
      USART1->SR &= ~BIT(USART_TC);    // ����� ����.
      COM_mode &= ~BIT(5);
      USART1->CR1 &= ~BIT(USART_TXEIE);   // ��������� ���������� �������� � COM1.
      USART1->CR1 |=BIT(USART_RXNEIE);    // ��������� ���������� ������ COM1.
	  }
		if(status & BIT(USART_ORE)){ // ������������ ������.  | BIT(USART_FE) | BIT(USART_NF))
			dd=USART1->SR;
			dd=USART1->DR;
		}
}
}

void USART2_IRQHandler(void){
vu8 dd, i;
vu16 status;
status=USART2->SR;
	if(status & BIT(USART_RXNE)){		// ������ ����
		USART2->SR &= ~BIT(USART_RXNE);	// �� ������ ������.
		if(CntTimeRxUSR>=100){
			chList[chUSR].ptrIN=0;		// ����� �����, �� ������.
		}
		dd=USART2->DR;
		CntTimeRxUSR=0; 
		if(chList[chUSR].ptrIN>=255) chList[chUSR].ptrIN=255;
		chList[chUSR].buffIN[chList[chUSR].ptrIN++]=dd;		// DD �������� � ���.
	}
	else if(status & BIT(USART_TXE)){		// ����� �������� ����.
	  if((USR_mode & BIT(5))==0){   // ������ �� ��������� ����.
      if(chList[chUSR].ptrOUT < (255)) chList[chUSR].ptrOUT++;
			else{
					USR_mode |=BIT(5);		// � ����� ������ ���������� ����� �������� �����.
					chList[chUSR].chState &= ~chSend;		// ����������� �������� � ���.
			}
      if(chList[chUSR].ptrOUT>=chList[chUSR].buffOUTLen){		// ���� ��� ���������.
        USR_mode |=BIT(5);    // � ����� ������ ���������� ����� �������� �����.
        chList[chUSR].chState &= ~chSend;		// ����������� �������� � ���1.
      }
      else{
        i=chList[chUSR].ptrOUT;
        USART2->DR=chList[chUSR].buffOUT[i];		// ����� ��������� ����.
      }
	  }else if (status & BIT(USART_TC)){
      USART2->SR &= ~BIT(USART_TC);    // ����� ����.
      USR_mode &= ~BIT(5);
      USART2->CR1 &= ~BIT(USART_TXEIE);   // ��������� ���������� �������� � COM1.
      USART2->CR1 |=BIT(USART_RXNEIE);    // ��������� ���������� ������ COM1.
	  }
		if(status & BIT(USART_ORE)){ // ������������ ������.  | BIT(USART_FE) | BIT(USART_NF))
			dd=USART2->SR;
			dd=USART2->DR;
		}
}
}

//=== ���������� SPI2 ===//
void SPI2_IRQHandler(void){
vu8 data;
  if(SPI2->SR & BIT(SPI_TXE)){            // ����� �������� ����.
    data=SPI2->DR;          // ������. ���� ����� ��������� ���� RXNE.
    BufFromSPI[PtrByteSPI]=data;            // ������.
    if(PtrByteSPI<CntByteSPI){              // ������/������ �� ��������� ����.
      SPI2->DR=Buf2SPI[PtrByteSPI];           // ��������. ���� ����� ��������� ���� TXE.
      PtrByteSPI++;
    }
    else{           // ������/������ ��������� ����.
      ResetCS();           // ����� /CS.
      ResetSPIIE();           // ��������� ����������.
      SPI_mode &= ~BIT(7);            // ����������� �����.
    }
  }
}
void ADC_IRQHandler(void){
u32 reg;
	reg=ADC1->SR;
}
void ADC1_2_IRQHandler(void){
ADC1->SR&=~0x1F;
Pill=0x0FFF & (ADC1->DR);
}