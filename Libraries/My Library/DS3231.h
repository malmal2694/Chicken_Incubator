#include "stm32f10x.h"

#define DS3231_FLAG_A1F (1 << 0)
#define DS3231_FLAG_A2F (1 << 1)
#pragma once

struct DS3231_DateTime{
	char Seconds;
	char Minutes;
	char Hour;
	char Day;// Range 1-7
	char Date;// Range 1-31
	char Month;
	char Year;// Range 0-99
};

struct DS3231_Alarm1{
	char Seconds;
	char Minutes;
	char Hour;
	char Day;// Range 1-7
	char Date;// Range 1-31
};

struct DS3231_Alarm2{
	char Minutes;
	char Hour;
	char Day;// Range 1-7
	char Date;// Range 1-31
};

struct DS3231_DateTime DS3231_WriteDate;// structure for write date
struct DS3231_DateTime DS3231_ReadDate;// structure for read date

struct DS3231_Alarm1 DS3231_WriteAlarm1;// structure for write Alarm1
struct DS3231_Alarm1 DS3231_ReadAlarm1;// structure for read Alarm1

struct DS3231_Alarm2 DS3231_WriteAlarm2;// structure for write Alarm2
struct DS3231_Alarm2 DS3231_ReadAlarm2;// structure for read Alarm2

#ifndef MY_LIBRARY_DS3231_H_
#define MY_LIBRARY_DS3231_H_

void DS3231_WriteDateTime(I2C_TypeDef* I2Cx, struct DS3231_DateTime *DS3231_Date);
void DS3231_ReadDateTime(I2C_TypeDef* I2Cx, struct DS3231_DateTime *DS3231_Date);

void DS3231_SetAlarm1(I2C_TypeDef* I2Cx, struct DS3231_Alarm1 *DS3231_WriteAlarm1);
void DS3231_SetAlarm2(I2C_TypeDef* I2Cx, struct DS3231_Alarm2 *DS3231_WriteAlarm2);

void DS3231_GetAlarm1(I2C_TypeDef* I2Cx, struct DS3231_Alarm1 *DS3231_ReadAlarm1);
void DS3231_GetAlarm2(I2C_TypeDef* I2Cx, struct DS3231_Alarm2 *DS3231_ReadAlarm20);

uint8_t DS3231_ReadFlag(I2C_TypeDef* I2Cx, uint8_t DS3231_FLAG);
void DS3231_ClearFlag(I2C_TypeDef* I2Cx, uint8_t DS3231_FLAG);

void DS3231_GoToAddress(I2C_TypeDef* I2Cx, uint8_t AddressByte);

void DS3231_SendData(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t DS3231_ReceiveData(I2C_TypeDef* I2Cx);

unsigned char DS3231_NumtoNumDS(unsigned char value);
unsigned char DS3231_NumDStoNum(unsigned char value);

#endif /* MY_LIBRARY_DS3231_H_ */
