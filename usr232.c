#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h> // Medium density 64 Kb kB flash
#include "usr232.h"
#include "vars.h"
#include "string.h"

vu16 SostUSR;
vu16 ComTimeUSR;
vu8 ErrCountUSR;

#define SET_HTTP_SERVER 1 		//Set HTTP server address and port 
#define SET_HTTP_CONNECTION 2 //Set HTTP Connection area
#define SET_HEADER 4 					//Set HTTP protocol header path
#define SEND_HTTP_REQUEST 8		//Send HTTP request
#define AT_MODE 16						//Enter to AT mode


vu8 POST[1024];
vu8 Data[256];

const u8 POST_Header[]=	"POST /update HTTP/1.1\r\n"
												"Host: api.thingspeak.com\r\n"
												"Connection: close\r\n"
												"X-THINGSPEAKAPIKEY: FJI8D3NGA4GRF9HO\r\n"
												"Content-Type: application/x-www-form-urlencoded\r\n"
												"Content-Length: ";//40\r\n"
												//"\r\n"
												//"&field1=10&field2=10&field3=10&field4=10\r\n";
vu8 POST_Len;
vu16 Data_Len;

u8 FillBuff(void){
	vu8 i,j,x;
	vu8 field1[]="&field1="; //Temp
	vu8 field2[]="&field2="; //Humm
	vu8 field3[]="&field3="; //Pres
	vu8 field4[]="&field4="; //CO2
	float temp;
	for (POST_Len=0; POST_Len<sizeof(POST_Header)-1;POST_Len++){
		POST[POST_Len]=POST_Header[POST_Len];
	}

	Data_Len=0;
	for (i=0;i<sizeof(field1)-1;i++) {Data[i]=field1[i];} // Temp
	Data_Len+=i;
	temp=temperature/10.0;
	j=sprintf(&Data[Data_Len],"%.1f",temp);
	//j=itoa((int)temperature, &Data[Data_Len]);
	Data_Len+=j;
	
	for (i=0;i<sizeof(field2)-1;i++) {Data[i+Data_Len]=field2[i];} // Humm
	Data_Len+=i;
	//j=sprintf((char*)&Data[Data_Len],"%u",(int)humidity);
	j=itoa((int)humidity, &Data[Data_Len]);
	Data_Len+=j;	
	
	for (i=0;i<sizeof(field3)-1;i++) {Data[i+Data_Len]=field3[i];} // Pres
	Data_Len+=i;
	temp=press_f/133.0;
	j=sprintf(&Data[Data_Len],"%.2f",temp);
	//j=itoa((int)pressure, &Data[Data_Len]);
	Data_Len+=j;	
	
	for (i=0;i<sizeof(field4)-1;i++) {Data[i+Data_Len]=field4[i];} // CO2
	Data_Len+=i;
	//j=sprintf((char*)&Data[Data_Len],"%u",(int)CO2);
	j=itoa((int)CO2, &Data[Data_Len]);
	Data_Len+=j;	
	
	j=itoa((int)Data_Len, &POST[POST_Len]);
	POST_Len+=j;
	
	POST[POST_Len++]=0x0d;
	POST[POST_Len++]=0x0a;
	POST[POST_Len++]=0x0d;
	POST[POST_Len++]=0x0a;
	
	for (i=0;i<Data_Len;i++) {POST[i+POST_Len]=Data[i];}
	POST_Len+=i;
	POST[POST_Len++]=0x0d;
	POST[POST_Len++]=0x0a;

return (POST_Len);
}

void initUSR232(void){
	RCC->APB1ENR |= BIT(RCC_USART2EN);
	
	GPIOA->CRL &= ~(0x0F00); //clear PA.2 configuration-bit 
  GPIOA->CRL   |= (0x0B  << 8); //Tx (PA9) - alt. out push-pull

  GPIOA->CRL &= ~(0xF000); //clear PA.3 configuration-bit 
  GPIOA->CRL   |= BIT(14); //Rx (PA10) - floating
	
	USART2->CR1 &= ~BIT(USART_UE); // выключим
	USART2->BRR =(APBCLK+BAUDRATEusr232/2)/BAUDRATEusr232; // (fck + baudrate /2 ) / baudrate. baudrate =9600;
	USART2->CR1 &= ~BIT(USART_PCE);		// none parity.
				// установка количества стоп битов.
	USART2->CR2 &= ~BIT(USART_STOP0);
	USART2->CR2 &= ~BIT(USART_STOP1);
	USART2->CR1 |= BIT(USART_TE) | BIT(USART_RE) | BIT(USART_UE); 	// включим
	USART2->CR1 |= BIT(USART_RXNEIE);

	vu8 i = USART2->DR;
}

/*void SendtoServer(u8 i){
u8 Ch;
Ch=chUSR;
	switch(SostUSR) {
		
		case (AT_MODE):
			if (i==1) {
				SostUSR = SET_HTTP_SERVER; ErrCountUSR=0;ComTimeUSR=0;}
			 else {
				SostUSR=0;
			 }
			break;
		case (SET_HTTP_SERVER):
			if (i==1) {
				SostUSR = SET_HTTP_CONNECTION; ErrCountUSR=0; ComTimeUSR=0;}
			else {
				SendPacket(Ch, sizeof(HTTPURL)-1, HTTPURL);
				ComTimeUSR=20;
			}
			break;
		case (SET_HTTP_CONNECTION):
			if (i==1) {
				SostUSR = SET_HEADER; ErrCountUSR=0; ComTimeUSR=0;}
			else {
				SendPacket(Ch, sizeof(HTTPCN)-1, HTTPCN);
				ComTimeUSR=20;
			}
			break;
		case (SET_HEADER):
			if (i==1) {
				SostUSR = SEND_HTTP_REQUEST; ErrCountUSR=0; ComTimeUSR=90;}
			else {
				SendPacket(Ch, FillBuff(), HTTPPH);
				ComTimeUSR=20;
			}
			break;
		case (SEND_HTTP_REQUEST):
			if (i==1) {
				SostUSR = SET_HEADER; ErrCountUSR=0; ComTimeUSR=20;}
			else {
				SendPacket(Ch, sizeof(HTTPDT)-1, HTTPDT);
				ComTimeUSR=30;
			}
			break;
		default: 
			SendPacket(Ch, sizeof(inAT_MODE)-1, inAT_MODE);
			ComTimeUSR=90;
			SostUSR = AT_MODE;
			break;
	}
	
}
u8 CheckOK(vu8* buf){
	char strok[]="+ok";
	char str200ok[]="200 OK";
	if (SostUSR == AT_MODE && buf[0]==0x61) {
		vu8 a = 0x61;
		SendPacket(chUSR, 1, &a);
		ErrCountUSR=0;
		ComTimeUSR=20;
		return 0;
	}else if(SostUSR == AT_MODE && strstr((char*)buf, "+++")){
		return 1;	
	}else if (SostUSR != SEND_HTTP_REQUEST && strstr((char*)buf, strok)){
		return 1;
	}else if (SostUSR == SEND_HTTP_REQUEST && strstr((char*)buf, str200ok)){
		return 1;
	}
	return 0;
}*/
