
#include "stm32f10x_i2c.h"
#include "DS3231.h"

#define DISPLAY_TEMP_HUMIDITY 1
#define DISPLAY_TIME_NOW 2
#define DISPLAY_TIME_START_INCUBATOR 3
#define DISPLAY_TIME_STOP_INCUBATOR 4
#define DISPLAY_TYPE_PERIOD 5

struct Egg_Info{
	float TempIncubator;
	float TempHatcher;

	char HumidityIncubator;
	char HumidityHatcher;

	char TimeIncubator;
	char AllTime;

	char TempSaved;
	char TimeSaved;
	char HumiditySaved;
};

struct Egg_Info HenInfo;
struct Egg_Info DuckInfo;
struct Egg_Info GooseInfo;
struct Egg_Info QuailInfo;
struct Egg_Info QuailBHInfo;
struct Egg_Info TurkeyInfo;
struct Egg_Info MainEggInfo;

struct DS3231_DateTime TimeStartIncubator;// declare structure for save time start incubator
struct PIN_LCD LCD_PIN; // declare structure LCD Initialize
I2C_InitTypeDef I2C1_Init; // declare structure I2C1 Initialize


#ifndef MY_LIBRARY_CHICKEN_FUNC_H_
#define MY_LIBRARY_CHICKEN_FUNC_H_


void Chicken_Init();

void Chicken_MainMenu();
void Chicken_MenuEggSelect();
void Chicken_MenuConfigDate();
void Chicken_MenuStartIncubator();

void Chicken_Monitoring(float *temp, float *humidity, struct DS3231_DateTime *TimeStartIncubator, char SelectDisplay);
void Chicken_MonitoringHumiTemp(float *temp, float *humidity);
void Chicken_MonitoringTimeNow();
void Chicken_MonitoringTimeStartIncubator(struct DS3231_DateTime *TimeStartIncubator);
void Chicken_MonitoringTypePeriod();
void Chicken_MonitoringTimeStopIncubator();

void Chicken_ControlTempFan(float *Temp, uint8_t *LengthTimeStartIncubator);
void Chicken_ControlTempHeater(float *Temp, uint8_t *LengthTimeStartIncubator);
void Chicken_CalculateNextDay(struct DS3231_DateTime *TimeNow, struct DS3231_DateTime *NextDay);
void Chicken_EggInfo();
uint8_t Chicken_CalculateTypePeriod(uint8_t LengthTimeStartIncubator);

void USART_SendChar(USART_TypeDef* USARTx, uint16_t character);
uint16_t USART_GetChar(USART_TypeDef* USARTx);
void USART_Printf(USART_TypeDef* USARTx, unsigned char string[]);
void USART_Scanf(USART_TypeDef* USARTx, unsigned char *string, unsigned char CharEnd);

void Chicken_SelectEgg();
void Chicken_Core();
void Chicken_Delay(__uint16_t Time_ms);
void ftoa(float n, char *res, int afterpoint);

#endif /* MY_LIBRARY_CHICKEN_FUNC_H_ */
