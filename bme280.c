#include <cortexm3_macro.h>
#include <stm32/stm32f10x.h>
#include "vars.h"

vs16 dig_P2;
vs16 dig_P3;
vs16 dig_P4;
vs16 dig_P5;
vs16 dig_P6;
vs16 dig_P7;
vs16 dig_P8;
vs16 dig_P9;

vu16 dig_T1;
vs16 dig_T2;
vs16 dig_T3;
vu16 dig_P1;

vu8  dig_H1;
vs16 dig_H2;
vu8  dig_H3;
vs16 dig_H4;
vs16 dig_H5;
vs8  dig_H6;

void bmp280Convert(long* temperature, long* pressure, long* humidity)
{
  unsigned long adc_P, adc_H, adc_T;
  adc_T = Read24(BMP280_REG_RESULT_TEMPRERATURE);
  adc_P = Read24(BMP280_REG_RESULT_PRESSURE);

  double var1, var2, p, t_fine;
  var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
  var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0 - ((double) dig_T1)/8192.0)) * ((double)dig_T3);
  t_fine = (var1 + var2);
  *temperature = (vs32) (t_fine*10 / 5120.0);
	
	adc_H = (Read8(BME280_REGISTER_HUMIDDATA)<<8) | Read8(BME280_REGISTER_HUMIDDATA + 1);
			
	vs32 v_x1_u32r;

	v_x1_u32r = (t_fine - ((vs32)76800));
	v_x1_u32r = (((((adc_H << 14) - (((vs32)dig_H4) << 20) -
									(((vs32)dig_H5) * v_x1_u32r)) + ((vs32)16384)) >> 15) *
							 (((((((v_x1_u32r * ((vs32)dig_H6)) >> 10) *
										(((v_x1_u32r * ((vs32)dig_H3)) >> 11) + ((vs32)32768))) >> 10) +
									((vs32)2097152)) * ((vs32)dig_H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
														 ((vs32)dig_H1)) >> 4));

	v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
	v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	float h = (v_x1_u32r>>12);
	*humidity  = (h / 1024.0);

  var1 = ((double)t_fine/2.0) - 64000.0;
  var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
  var2 = var2 + var1 * ((double)dig_P5) * 2.0;
  var2 = (var2/4.0)+(((double)dig_P4) * 65536.0);
  var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
  var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
  if (var1 == 0.0)
  {
    return; // avoid exception caused by division by zero
  }
  p = 1048576.0 - (double)adc_P;
  p = (p - (var2 / 4096.0)) * 6250.0 / var1;
  var1 = ((double)dig_P9) * p * p / 2147483648.0;
  var2 = p * ((double)dig_P8) / 32768.0;
  p = (p + (var1 + var2 + ((double)dig_P7)) / 16.0);

  *pressure = ((long)p);
}
//----------------------------------------

void BMP280_Init(void)
{
	vu16 chid;
	chid = Read8(0xD0);//Chip ID
	
  dig_T1 = Read16(0x88);//dig_T1
  dig_T2 = Read16(0x8A);//dig_T2
  dig_T3 = Read16(0x8C);//dig_T3
  dig_P1 = Read16(0x8E);//dig_P1
  dig_P2 = Read16(0x90);//dig_P2
  dig_P3 = Read16(0x92);//dig_P3
  dig_P4 = Read16(0x94);//dig_P4
  dig_P5 = Read16(0x96);//dig_P5
  dig_P6 = Read16(0x98);//dig_P6
  dig_P7 = Read16(0x9A);//dig_P7
  dig_P8 = Read16(0x9C);//dig_P8
  dig_P9 = Read16(0x9E);//dig_P9
	
	dig_H1 = Read8(BME280_REGISTER_DIG_H1);
	dig_H2 = Read16(BME280_REGISTER_DIG_H2);
	dig_H3 = Read8(BME280_REGISTER_DIG_H3);
	dig_H4 = (Read8(BME280_REGISTER_DIG_H4) << 4) | (Read8(BME280_REGISTER_DIG_H4+1) & 0xF);
	dig_H5 = (Read8(BME280_REGISTER_DIG_H5+1) << 4) | (Read8(BME280_REGISTER_DIG_H5) >> 4);
	dig_H6 = (vs8)Read8(BME280_REGISTER_DIG_H6);
	
	Write8(BME280_REGISTER_CONTROLHUMID, 5);
  Write8(BMP280_REG_CONFIG, BMP280_CONFIG);
  Write8(BMP280_REG_CONTROL, BMP280_MEAS);

}