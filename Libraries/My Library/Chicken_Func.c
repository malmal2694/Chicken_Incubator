
#include "stm32f10x_i2c.h"
#include "RCC.h"
#include "GPIO.h"
#include "IWDG.h"
#include "LCD.h"
#include "TIMER.h"
#include "USART.h"
#include "sht2x.h"
#include "AT24C02.h"
#include "DS3231.h"
#include "Chicken_Func.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NUMBER_EGG 6
#define CLOCK_FREQUENCY 18000000 //clock MCU is 18 MHz
#define PERIOD_SETTER 0
#define PERIOD_HATCHER 1

#define TIMER_CHANNEL_FAN 2// timer1 channel2
#define TIMER_CHANNEL_HEATER 3// timer1 channel3

#define WAIT_MONITORING 7 // every 7 second execute procedure Monitoring
#define WAIT_HEATER 10 // every 10 second execute procedure ControlTempHeater

// gloal variable
uint8_t LengthTimeStartIncubator = 0;// for save length time start incubator
uint16_t SaveSecond = 0;

void Chicken_Init()
{
// set clock 18 MHz for MCU
	PLL_SRC_Sel(2);
	PLL_MUL(2);
	Src_Sys_Clk(3);
	AHB_Div(4);
	APB1_APB2_Div(1, 1);

// set Clocks Peripherals MCU
	SetPeriphAPB2(APB2_TIM1);
	SetPeriphAPB1(APB1_TIM2);
	SetPeriphAPB1(APB1_I2C1);
	SetPeriphAPB2(APB2_USART1);
	SetPeriphAPB2(APB2_IOPB);
	SetPeriphAPB2(APB2_IOPA);
	SetPeriphAPB2(APB2_AFIO);

// changes pins Peripherals
	AFIO->MAPR |= (1 << 1); // pins for I2C1 (SCL/PB8, SDA/PB9)
	AFIO->MAPR |= (1 << 2); // pins for USART1  (TX/PB6, RX/PB7)

// Initialize TIMER1, TIMER2, IWDG, TIMER2
	Tim1_PWM_Enable(2, 1); //enable TIMER1 CH2(FAN)
	Tim1_PWM_Enable(3, 1); //enable TIMER1 CH3(HEATER)
	TIM1->ARR = 60000;// set frequency Timer1 = 400Hz
	Tim2Enable(1, 1, 4);// Enable Tim2 CH1 None event for pin
	TIM2->PSC = 18000;// every 1 second reload Register CNT
	TIM2->ARR = 1000;// every 1 second reload Register CNT
	NVIC_EnableIRQ(TIM2_IRQn);// enable interrupt time 2
	IWDG_Init(256); // Enable IWDG any 26214.4 ms reset MCU
	IWDG_Reset();

// set Pins As Output
	TimPinOutInit(PORTA, PIN9); // Enable PIN for TIMER1, CH 2(FAN)
	TimPinOutInit(PORTA, PIN10); // Enable PIN for TIMER1, CH 3(HEATER)
	Init_PIN(PORTB,PIN6,Config_Out_50MHz,Alter_Out_PP); // set output for USART1 Tx
	Init_PIN(PORTB, PIN8, Config_Out_50MHz, Alter_Out_PP); // configuration out pin for I2C1 SCL
	Init_PIN(PORTB, PIN9, Config_Out_50MHz, Alter_Out_PP); // Configuration out pin for I2C1 SDA

// initialize USART1
	USART_InitTypeDef USART1_Config;
	USART1_Config.USART_BaudRate = 4800;
	USART1_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_Config.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART1_Config.USART_Parity = USART_Parity_No;
	USART1_Config.USART_StopBits = USART_StopBits_1;
	USART1_Config.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART1_Config);
	USART_Cmd(USART1, ENABLE);// enable usart1

// initialize I2C1
	I2C_Cmd(I2C1, ENABLE);
	I2C1_Init.I2C_Ack = I2C_Ack_Enable;
	I2C1_Init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C1_Init.I2C_ClockSpeed = 70000;
	I2C1_Init.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C1_Init.I2C_Mode = I2C_Mode_I2C;
	I2C1_Init.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C1_Init);
	I2C_Cmd(I2C1, ENABLE);

// Initialize LCD Character
	LCD_PIN.PIN_BIT0 = PIN0;
	LCD_PIN.PORT_BIT0 = PORTB;
	LCD_PIN.PIN_BIT1 = PIN7;
	LCD_PIN.PORT_BIT1 = PORTA;
	LCD_PIN.PIN_BIT2 = PIN6;
	LCD_PIN.PORT_BIT2 = PORTA;
	LCD_PIN.PIN_BIT3 = PIN5;
	LCD_PIN.PORT_BIT3 =PORTA;
	LCD_PIN.PIN_BIT4 = PIN4;
	LCD_PIN.PORT_BIT4 = PORTA;
	LCD_PIN.PIN_BIT5 = PIN3;
	LCD_PIN.PORT_BIT5 = PORTA;
	LCD_PIN.PIN_BIT6 = PIN2;
	LCD_PIN.PORT_BIT6 = PORTA;
	LCD_PIN.PIN_BIT7 = PIN1;
	LCD_PIN.PORT_BIT7 = PORTA;
	LCD_PIN.PIN_E = PIN1;
	LCD_PIN.PORT_E = PORTB;
	LCD_PIN.PIN_RS = PIN11;
	LCD_PIN.PORT_RS = PORTB;
	LCD_PIN.PIN_RW = PIN10;
	LCD_PIN.PORT_RW = PORTB;

	LCD_8BIT_Init(&LCD_PIN);

	Chicken_EggInfo();
};


void Chicken_MainMenu()
{
	unsigned char CharReceive = 0;

	USART_Printf(USART1, "welcome to menu for configuration chicken device\n");
	USART_Printf(USART1, "you should enter number\n\n");
	USART_Printf(USART1, "1. select type egg\n");
	USART_Printf(USART1, "2. configuration date\n");
	USART_Printf(USART1, "3. start incubation\n");
	USART_Printf(USART1, "4. exit from menu\n");
	IWDG_Reset();

	CharReceive = USART_GetChar(USART1);// receive number 1 to 4
	if(CharReceive == '1'){// execute menu select type egg
		IWDG_Reset();
		Chicken_MenuEggSelect();
	}
	else if(CharReceive == '2'){// execute menu configuration date
		IWDG_Reset();
		Chicken_MenuConfigDate();
	}
	else if(CharReceive == '3'){
		IWDG_Reset();
		Chicken_MenuStartIncubator();// execute menu start incubator

	}
	else if(CharReceive == '4'){
		IWDG_Reset();
	}
	else{

	};

};
void Chicken_MenuEggSelect()
{
	USART_Printf(USART1, "\n\nPlease select egg");
	USART_Printf(USART1, "\n\n1. hen");
	USART_Printf(USART1, "\n2. duck");
	USART_Printf(USART1, "\n3. goose");
	USART_Printf(USART1, "\n4. quail");
	USART_Printf(USART1, "\n5. Quail baht White");
	USART_Printf(USART1, "\n6. turkey");

	unsigned char EggType = 0;
	char USART_StringReceive[5];

	USART_Scanf(USART1, &USART_StringReceive, '.');// receive number for egg type

	if( (EggType = atoi(USART_StringReceive)) <=  NUMBER_EGG){// convert string to integer
		AT24C02_Write(I2C1, 0xA0, 9, EggType);// write egg type(example: hen)
		Chicken_Delay(12);// wait 12ms
		IWDG_Reset();
	};

	Chicken_SelectEgg();// set structure MainEggInfo = EggInfo(example: hen, duck)
};
void Chicken_MenuConfigDate()
{
	char date[4];

	USART_Printf(USART1, "\nPlease Enter Year: ");
	USART_Scanf(USART1, &date, '.');// get year
	DS3231_WriteDate.Year = atoi(date);// convert string to int
	IWDG_Reset();

	USART_Printf(USART1, "\nPlease Enter Month: ");
	USART_Scanf(USART1, &date, '.');// get Month
	DS3231_WriteDate.Month = atoi(date);// convert string to int
	IWDG_Reset();

	USART1_Printf("\nPlease Enter Date: ");
	USART_Scanf(USART1, &date, '.');// get Date range 1-31
	DS3231_WriteDate.Date = atoi(date);// convert string to int
	IWDG_Reset();

	USART1_Printf("\nPlease Enter Day: ");
	USART_Scanf(USART1, &date, '.');// get day range 1-7
	DS3231_WriteDate.Day = atoi(date);// convert string to int
	IWDG_Reset();

	USART1_Printf("\nPlease Enter Hour: ");
	USART_Scanf(USART1, &date, '.');// get Hour
	DS3231_WriteDate.Hour = atoi(date);// convert string to int
	IWDG_Reset();

	USART1_Printf("\nPlease Enter Minutes: ");
	USART_Scanf(USART1, &date, '.');// get Minutes
	DS3231_WriteDate.Minutes = atoi(date);// convert string to int
	IWDG_Reset();

	USART1_Printf("\nPlease Enter Seconds: ");
	USART_Scanf(USART1, &date, '.');// get Seconds
	DS3231_WriteDate.Seconds = atoi(date);// convert string to int
	IWDG_Reset();

	DS3231_WriteDateTime(I2C1, &DS3231_WriteDate);// set date and time
	IWDG_Reset();
};
void Chicken_MenuStartIncubator()
{
	USART_Printf(USART1, "\nDo you Want to start Incubator\n\n");
	USART_Printf(USART1, "1.YES\n");
	USART_Printf(USART1, "2.NO\n");

	if(USART_GetChar(USART1) == '1'){
		IWDG_Reset();
		unsigned char ReceiveRandomPast = AT24C02_Read(I2C1, 0xA0, 0x0A);
		unsigned char RandomNumberNow = 0;

		do{
			srand(ReceiveRandomPast);
			RandomNumberNow = rand() % 255;// create random number
			}while(RandomNumberNow == ReceiveRandomPast);// if ReceiveRandomPast != RandomNumberNow exit from loop

		AT24C02_Write(I2C1, 0xA0, 0x0A, RandomNumberNow);
		Chicken_Delay(12);// wait 12ms

		DS3231_ReadDateTime(I2C1, &TimeStartIncubator);// receive date and time start incubator
		AT24C02_Write(I2C1, 0xA0, 5, TimeStartIncubator.Year);
		Chicken_Delay(12);// wait 12ms
		AT24C02_Write(I2C1, 0xA0, 6, TimeStartIncubator.Month);
		Chicken_Delay(12);// wait 12ms
		AT24C02_Write(I2C1, 0xA0, 7, TimeStartIncubator.Day);
		Chicken_Delay(12);// wait 12ms
		AT24C02_Write(I2C1, 0xA0, 8, TimeStartIncubator.Hour);
		Chicken_Delay(12);// wait 12ms

		AT24C02_Write(I2C1, 0xA0, 0x0B, 1);// address byte 11 = 0 (length time incubator)
		LengthTimeStartIncubator = 1;// for save length time start incubator

		Chicken_Delay(12);// wait 12ms
		IWDG_Reset();

		struct DS3231_DateTime NextDay;// structure for save next day
		Chicken_CalculateNextDay(&TimeStartIncubator, &NextDay);// calculate next day

		DS3231_WriteAlarm1.Seconds = NextDay.Seconds;
		DS3231_WriteAlarm1.Minutes = NextDay.Minutes;
		DS3231_WriteAlarm1.Hour = NextDay.Hour;
		DS3231_WriteAlarm1.Day = NextDay.Day;
		DS3231_WriteAlarm1.Date = NextDay.Date;
		DS3231_SetAlarm1(I2C1, &DS3231_WriteAlarm1);// set ALARM1 for next day
	}
};


void Chicken_Monitoring(float *temp, float *humidity, struct DS3231_DateTime *TimeStartIncubator, char SelectDisplay)
{
	switch(SelectDisplay){
	case 1:
		Chicken_MonitoringHumiTemp(temp, humidity);// display humidity and temperature
		IWDG_Reset();
		break;
	case 2:
		Chicken_MonitoringTimeNow();
		IWDG_Reset();
		break;
	case 3:
		Chicken_MonitoringTimeStartIncubator(TimeStartIncubator);// display time start incubator
		IWDG_Reset();
		break;
	case 4:
		Chicken_MonitoringTimeStopIncubator();// display time stop incubator
		IWDG_Reset();
		break;
	case 5:
		Chicken_MonitoringTypePeriod();
		IWDG_Reset();
		break;
	}
};
void Chicken_MonitoringHumiTemp(float *temp, float *humidity)
{
	char tempStr[6];
	char humidityStr[6];

	ftoa(*temp, tempStr, 2);// convert temperature(float) to string
	ftoa(*humidity, humidityStr, 2);// convert humidity(float) to string

	LCD_CLS(&LCD_PIN);
	LCD_Home(&LCD_PIN);
	LCD_Printf("temp: ", &LCD_PIN);
	LCD_Printf(tempStr, &LCD_PIN);// display temperature

	LCD_XY(0, 2, &LCD_PIN);// go to x = 0, y = 2
	LCD_Printf("humi: ", &LCD_PIN);
	LCD_Printf(humidityStr, &LCD_PIN);// display humidity
	LCD_PutChar('%', &LCD_PIN);
	IWDG_Reset();
};
void Chicken_MonitoringTimeNow()
{
	char buffer[10];// array for convert int to string
	char timeString[15];// variable for display date (example: 95/12/01 22:55)

	LCD_CLS(&LCD_PIN);
	LCD_Home(&LCD_PIN);
	LCD_Printf("time now: ", &LCD_PIN);

	DS3231_ReadDateTime(I2C1, &DS3231_ReadDate);// read date and time

	itoa(DS3231_ReadDate.Year, buffer, 10);// convert year to string (10 = decimal)
	strcat(timeString, buffer);

	strcat(timeString, "/");

	itoa(DS3231_ReadDate.Month, buffer, 10);// convert Month to string
	strcat(timeString, buffer);

	strcat(timeString, "/");

	itoa(DS3231_ReadDate.Date, buffer, 10);// convert Date(range 1-31) to string
	strcat(timeString, buffer);

	strcat(timeString, " "); // add character space to time

	itoa(DS3231_ReadDate.Hour, buffer, 10);// convert hour to string
	strcat(timeString, buffer);

	strcat(timeString, ":");

	itoa(DS3231_ReadDate.Minutes, buffer, 10);// convert Minutes to string
	strcat(timeString, buffer);

	LCD_XY(0, 2, &LCD_PIN);// go to x=0, y=2
	LCD_Printf(timeString, &LCD_PIN);// display time(example 95/02/011 10:58)
	IWDG_Reset();
};
void Chicken_MonitoringTimeStartIncubator(struct DS3231_DateTime *TimeStartIncubator)
{
	char TimeStartString[15];
	char buffer[10];// array for convert int to string

	LCD_CLS(&LCD_PIN);
	LCD_Home(&LCD_PIN);
	LCD_Printf("Start Incubator:", &LCD_PIN);

	itoa(TimeStartIncubator->Year, buffer, 10);// convert year to string
	strcat(TimeStartString, buffer);// collect array TimeStartString and buffer

	strcat(TimeStartString, "/");// collect array TimeStartString and slash character(/)

	itoa(TimeStartIncubator->Month, buffer, 10);// convert Month to string
	strcat(TimeStartString, buffer);// collect array TimeStartString and buffer

	strcat(TimeStartString, "/");// collect array TimeStartString and slash character(/)

	itoa(TimeStartIncubator->Date, buffer, 10);// convert date(1-31) to string
	strcat(TimeStartString, buffer);// collect array TimeStartString and buffer

	strcat(TimeStartString, " ");// collect array TimeStartString and space character

	itoa(TimeStartIncubator->Hour, buffer, 10);// convert hour to string
	strcat(TimeStartString, buffer);// collect arrays TimeStartString and buffer

	strcat(TimeStartString, ":");// collect array TimeStartString and character (:)

	itoa(TimeStartIncubator->Minutes, buffer, 10);// convert Minutes to sting
	strcat(TimeStartString, buffer);// collect arrays TimeStartString and buffer

	LCD_XY(0, 2, &LCD_PIN);// go to x(0), y(2)
	LCD_Printf(TimeStartString, &LCD_PIN);// display variable TimeStartString (Time start Incubator)
};
void Chicken_MonitoringTimeStopIncubator()
{
	struct DS3231_DateTime TimeStopIncubator;
	TimeStopIncubator = TimeStartIncubator;

	for(int i = 1; i <= MainEggInfo.AllTime; i++)
		Chicken_CalculateNextDay(&TimeStopIncubator, &TimeStopIncubator);// calculate stop incubator

	char TimeStopString[15];
	char buffer[10];// array for convert int to string

	LCD_CLS(&LCD_PIN);
	LCD_Home(&LCD_PIN);
	LCD_Printf("Stop Incubator:", &LCD_PIN);

	itoa(TimeStopIncubator.Year, buffer, 10);// convert year to string
	strcat(TimeStopString, buffer);// collect array TimeStopString and buffer

	strcat(TimeStopString, "/");// collect array TimeStopString and slash character(/)

	itoa(TimeStopIncubator.Month, buffer, 10);// convert Month to string
	strcat(TimeStopString, buffer);// collect array TimeStopString and buffer

	strcat(TimeStopString, "/");// collect array TimeStopString and slash character(/)

	itoa(TimeStopIncubator.Date, buffer, 10);// convert date(1-31) to string
	strcat(TimeStopString, buffer);// collect array TimeStopString and buffer

	strcat(TimeStopString, " ");// collect array TimeStopString and space character

	itoa(TimeStopIncubator.Hour, buffer, 10);// convert hour to string
	strcat(TimeStopString, buffer);// collect arrays TimeStopString and buffer

	strcat(TimeStopString, ":");// collect array TimeStopString and character (:)

	itoa(TimeStopIncubator.Minutes, buffer, 10);// convert Minutes to sting
	strcat(TimeStopString, buffer);// collect arrays TimeStopString and buffer

	LCD_XY(0, 2, &LCD_PIN);// go to x(0), y(2)
	LCD_Printf(TimeStopString, &LCD_PIN);// display variable TimeStartString (Time start Incubator)
	IWDG_Reset();
};
void Chicken_MonitoringTypePeriod()
{
	LCD_CLS(&LCD_PIN);
	LCD_Home(&LCD_PIN);
	LCD_Printf("type period is:", &LCD_PIN);
	LCD_XY(0, 2, &LCD_PIN);// go to x=0, y=2 from LCD

	if(Chicken_CalculateTypePeriod(LengthTimeStartIncubator) == PERIOD_SETTER)
		LCD_Printf("Setter", &LCD_PIN);
	else if(Chicken_CalculateTypePeriod(LengthTimeStartIncubator == PERIOD_HATCHER))
		LCD_Printf("Hatcher", &LCD_PIN);
};


void Chicken_ControlTempFan(float *Temp, uint8_t *LengthTimeStartIncubator)
{
	float TempDiffer = (*Temp - MainEggInfo.TempIncubator) * (float)15;// calculate temperature difference

	switch (Chicken_CalculateTypePeriod(*LengthTimeStartIncubator))// calculate type period
	{
		case PERIOD_SETTER:// type time is setter
			if((*Temp > MainEggInfo.TempIncubator) && (TempDiffer >= (float)1.5))// if temperature now > Temperature setter(incubator)
				PWM_SetCCR(TIM1, TIMER_CHANNEL_FAN, TempDiffer + 25);// set PWM FAN = TempDiffer + 25
			break;

		case PERIOD_HATCHER:// type time is hatcher
			if((*Temp > MainEggInfo.TempHatcher) && (TempDiffer >= (float)1.5))// if temperature now > Temperature setter(incubator)
				PWM_SetCCR(TIM1, TIMER_CHANNEL_FAN, TempDiffer + 25);// set PWM FAN = TempDiffer + 25
			break;
	}
};
void Chicken_ControlTempHeater(float *Temp, uint8_t *LengthTimeStartIncubator)
{
	switch (Chicken_CalculateTypePeriod(*LengthTimeStartIncubator))// calculate type period
	{
		case PERIOD_SETTER:// type time is setter
			PWM_SetCCR(TIM1, TIMER_CHANNEL_HEATER,  ((MainEggInfo.TempIncubator - *Temp) * 3) + PWM_GetCCR(TIM1, TIMER_CHANNEL_HEATER));// set CCR value => (TempMain - TempNow * 3) + CCR value in the past
			break;

		case PERIOD_HATCHER:// type time is hatcher
			PWM_SetCCR(TIM1, TIMER_CHANNEL_HEATER, ((MainEggInfo.TempHatcher - *Temp) * 3) + PWM_GetCCR(TIM1, TIMER_CHANNEL_HEATER));
			break;
	}
};
void Chicken_CalculateNextDay(struct DS3231_DateTime *TimeNow, struct DS3231_DateTime *NextDay)
{
	*NextDay = *TimeNow;
	NextDay->Date++;//increase day for calculate next day(date range is 1-31)
	NextDay->Day++;// day range is 1-7

	if(NextDay->Day > 7)
		NextDay->Day = 1;// (if day after increase > 7) day = 1

	if(NextDay->Month >= 1 && NextDay->Month <= 6 && NextDay->Date == 32)// if month between 1 & 6 and date(1-31) == 32, date = 1 and month + 1
	{
		NextDay->Date = 1;
		NextDay->Month++;
	}
	else if(NextDay->Month > 6 && NextDay->Month <= 11 && NextDay->Date == 31)// if month between 7 & 11 and date(1-31) == 31, date = 1 and month + 1
	{
		NextDay->Date = 1;
		NextDay->Month++;
	}
	else if(NextDay->Month == 12)
	{
		if( ((NextDay->Year % 4) == 3) && NextDay->Date == 31)// leap year
		{
			NextDay->Year++;// increase year
			NextDay->Month = 1;// month = 1
			NextDay->Date = 1;// date(1-31) = 1
		}
		else if( ((NextDay->Year % 4) != 3) && NextDay->Date == 30)// no leap year
		{
			NextDay->Year++;// increase year
			NextDay->Month = 1;// month = 1
			NextDay->Date = 1;// date(1-31) = 1
		};
	};
};
void Chicken_SetAlarmNextDay()
{
	DS3231_GetAlarm1(I2C1, &DS3231_ReadAlarm1);// read time alarm
	DS3231_ReadDateTime(I2C1, &DS3231_ReadDate);// read date and time

	struct DS3231_DateTime NextDay;
	Chicken_CalculateNextDay(&DS3231_ReadDate, &NextDay);// set NextDay = calculate next day

	DS3231_WriteAlarm1.Seconds = DS3231_ReadAlarm1.Seconds;
	DS3231_WriteAlarm1.Minutes = DS3231_ReadAlarm1.Minutes;
	DS3231_WriteAlarm1.Hour = DS3231_ReadAlarm1.Hour;
	DS3231_WriteAlarm1.Day = NextDay.Day;
	DS3231_WriteAlarm1.Date = NextDay.Date;
	DS3231_SetAlarm1(I2C1, &DS3231_WriteAlarm1);// set alarm for next day
	DS3231_ClearFlag(I2C1, DS3231_FLAG_A1F);// clear flag alarm1

	LengthTimeStartIncubator++;// Increments of one
	AT24C02_Write(I2C1, 0xA0, 0x0B, LengthTimeStartIncubator);// save length time start incubator
	Chicken_Delay(12);// wait 12ms

	while(AT24C02_Read(I2C1, 0xA0, 0x0B) != LengthTimeStartIncubator);// If EEPROM and LengthTimeStartIncubator were unequal to be set again EEPROM
	{
		AT24C02_Write(I2C1, 0xA0, 0x0B, LengthTimeStartIncubator);// save length time start incubator
		Chicken_Delay(12);// wait 12ms
		IWDG_Reset();
	}

};
uint8_t Chicken_CalculateTypePeriod(uint8_t LengthTimeStartIncubator)
{
	if((LengthTimeStartIncubator > 0) && (LengthTimeStartIncubator <= MainEggInfo.TimeIncubator))// type period is setter
		return PERIOD_SETTER;
	else if((LengthTimeStartIncubator > MainEggInfo.TimeIncubator) && (LengthTimeStartIncubator <= MainEggInfo.AllTime))// type period is hatcher
		return PERIOD_HATCHER;
};


void USART_SendChar(USART_TypeDef* USARTx, uint16_t character)
{
	USART_ClearFlag(USARTx, USART_FLAG_TC);// clear flag Transmission Complete flag(TC)
	USART_SendData(USARTx, character);// send data from variable character
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_TC));// wait send data
};
uint16_t USART_GetChar(USART_TypeDef* USARTx)
{
	USART_ClearFlag(USARTx, USART_FLAG_RXNE);// clear flag RXNE
	while(!USART_GetFlagStatus(USARTx, USART_FLAG_RXNE));// wait receive data
	return USART_ReceiveData(USARTx);// receive data & return
};
void USART_Printf(USART_TypeDef* USARTx, unsigned char string[])// for use this function : USART_Printf(USARTx, name_array); don't use [] or and operator(&)
{
	unsigned char length = strlen(string);// calculate length array string
	for(int i = 0; i < length; i++){
		USART_SendChar(USARTx, string[i]);// send character
	}
};
void USART_Scanf(USART_TypeDef* USARTx, unsigned char *string, unsigned char CharEnd){
	unsigned char CharReceive = 0;
	int i = 0;

	while( ( CharReceive = USART_GetChar(USARTx) ) != CharEnd){
		string[i] = CharReceive;
		i++;
	}
	string[i] = '\0';
};


void Chicken_SelectEgg()
{
	switch (AT24C02_Read(I2C1, 0xA0, 9)) {// read type egg
		case 1:
			MainEggInfo = HenInfo; //select egg hen
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Hen", &LCD_PIN);// send detail to LCD
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;

		case 2:
			MainEggInfo = DuckInfo; //select egg duck
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Duck", &LCD_PIN);// send detail to LCD
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;

		case 3:
			MainEggInfo = GooseInfo; //select egg goose
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Goose", &LCD_PIN);// send detail to LCD
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;

		case 4:
			MainEggInfo = QuailInfo; //select egg Quail
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Quail", &LCD_PIN);// send detail to lcd
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;

		case 5:
			MainEggInfo = QuailBHInfo; //select egg Quail baht white
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Quail Baht white", &LCD_PIN);// send detail to lcd
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;

		case 6:
			MainEggInfo = TurkeyInfo; //select egg turkey
			LCD_CLS(&LCD_PIN);
			LCD_Home(&LCD_PIN);
			LCD_Printf("type egg: Turkey", &LCD_PIN);// send detail to lcd
			IWDG_Reset();
			Chicken_Delay(10000);// wait 10 seconds
			IWDG_Reset();
			break;
	};

};
void Chicken_EggInfo()
{
// add info Hen
	HenInfo.AllTime = 21;
	HenInfo.HumidityHatcher = 70;
	HenInfo.HumidityIncubator = 37.5;
	HenInfo.HumiditySaved = 65;
	HenInfo.TempHatcher = 37.2;
	HenInfo.TempIncubator = 37.5;
	HenInfo.TempSaved = 14;
	HenInfo.TimeIncubator = 18;
	HenInfo.TimeSaved = 7;

// add info Duck
	DuckInfo.AllTime = 28;
	DuckInfo.HumidityHatcher = 75;
	DuckInfo.HumidityIncubator = 60;
	DuckInfo.HumiditySaved = 0;
	DuckInfo.TempHatcher = 0;
	DuckInfo.TempIncubator = 37.5;
	DuckInfo.TempSaved = 0;
	DuckInfo.TimeIncubator = 25;
	DuckInfo.TimeSaved = 0;

// add info Goose
	GooseInfo.AllTime = 30;
	GooseInfo.HumidityHatcher = 75;
	GooseInfo.HumidityIncubator = 55;
	GooseInfo.HumiditySaved = 70;
	GooseInfo.TempHatcher = 37.5;
	GooseInfo.TempIncubator = 37.7;
	GooseInfo.TempSaved = 14;
	GooseInfo.TimeIncubator = 4;
	GooseInfo.TimeSaved = 5;

// add info Quail
	QuailInfo.AllTime = 18;
	QuailInfo.HumidityHatcher = 75;
	QuailInfo.HumidityIncubator = 45;
	QuailInfo.HumiditySaved = 70;
	QuailInfo.TempHatcher = 37;
	QuailInfo.TempIncubator = 37.5;
	QuailInfo.TempSaved = 14;
	QuailInfo.TimeIncubator = 15;
	QuailInfo.TimeSaved = 9;

// add info Quail baht White
	QuailBHInfo.AllTime = 23;
	QuailBHInfo.HumidityHatcher = 75;
	QuailBHInfo.HumidityIncubator = 45;
	QuailBHInfo.HumiditySaved = 70;
	QuailBHInfo.TempHatcher = 37;
	QuailBHInfo.TempIncubator = 37.5;
	QuailBHInfo.TempSaved = 14;
	QuailBHInfo.TimeIncubator = 20;
	QuailBHInfo.TimeSaved = 9;

// add info Turkey
	TurkeyInfo.AllTime = 28;
	TurkeyInfo.HumidityHatcher = 75;
	TurkeyInfo.HumidityIncubator = 55;
	TurkeyInfo.HumiditySaved = 0;
	TurkeyInfo.TempHatcher = 37;
	TurkeyInfo.TempIncubator = 37.5;
	TurkeyInfo.TempSaved = 0;
	TurkeyInfo.TimeIncubator = 25;
	TurkeyInfo.TimeSaved = 0;
}
void Chicken_Core()
{
	Chicken_Init();// initialize chicken device

	Chicken_SelectEgg();// set structure MainEggInfo = EggInfo(example: hen, duck)

	float HumiVal = 0, TempVal = 0;// declaration variables for save temperature and humidity
	char SelectTypeMonitoring = 0;
	uint8_t DelayMonitoring = 0, DelayHeater = 0;

	TimeStartIncubator.Year = AT24C02_Read(I2C1, 0xA0, 5);// read year start incubator
	TimeStartIncubator.Month = AT24C02_Read(I2C1, 0xA0, 6);// read month start incubator
	TimeStartIncubator.Day = AT24C02_Read(I2C1, 0xA0, 7);// read day(1-7) start incubator
	TimeStartIncubator.Hour = AT24C02_Read(I2C1, 0xA0, 8);// read hour start incubator

	LengthTimeStartIncubator = AT24C02_Read(I2C1, 0xA0, 11);// read length time start incubator

	while(1)
	{
		if(USART_ReceiveData(USART1) == 'c')
		{
			unsigned char string[6];
			USART_Printf(USART1, "Please Enter Command: ");
			USART_Scanf(USART1, string, '.');// wait receive string "init"

			if(strcmp(string, "init") == 0)// if string received == "init" , execute procedure MainMenu
				Chicken_MainMenu();
		}

		if(DS3231_ReadFlag(I2C1, DS3231_FLAG_A1F) != 0x00)// if flag alarm1(A1F) == enable, execute procedure SetAlarmNextDay
			Chicken_SetAlarmNextDay();

		TempVal = SHT_ReadTemp(I2C1);// read temperature
		HumiVal = SHT_ReadHumidity(I2C1);// read humidity

		if(SaveSecond >= 86400)// 86400 seconds = 24 Hour
			SaveSecond = 0;// if saveSecond >= 86400, SaveSecond = 0

		if(((DelayMonitoring * WAIT_MONITORING) + WAIT_MONITORING) >= SaveSecond)// every 7 second execute Monitoring Procedure
		{
			DelayMonitoring++;// increase variable DelayMonitoring
			if(SelectTypeMonitoring >= 5)
				SelectTypeMonitoring = 0;// if SelectTypeMonitoring >= 5, set = 0
			Chicken_Monitoring(&TempVal, &HumiVal, &TimeStartIncubator, ++SelectTypeMonitoring);// execute procedure monitoring
		};

		Chicken_ControlTempFan(&TempVal, &LengthTimeStartIncubator);// control temperature with fan

		if(((DelayHeater * WAIT_HEATER) + WAIT_HEATER) >= SaveSecond)// every 10 second execute ControlTempHeater Procedure
		{
			DelayHeater++;// increase variable DelayMonitoring
			Chicken_ControlTempHeater(&TempVal, &LengthTimeStartIncubator);// control temperature with Heater
		};
	};
};
void Chicken_Delay(__uint16_t Time_ms)
{
	while(Time_ms--)
		for (__uint16_t i = 0; i <= (CLOCK_FREQUENCY / 10000); i++);// wait 1ms
};
void TIM2_IRQHandler(){
	SaveSecond++;// increase variables
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
};

// reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}



