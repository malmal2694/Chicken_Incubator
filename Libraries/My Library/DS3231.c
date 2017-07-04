#include "DS3231.h"
#include "stm32f10x_i2c.h"

void DS3231_WriteDateTime(I2C_TypeDef* I2Cx, struct DS3231_DateTime *DS3231_Date)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);// send Address DS3231(0xD0)
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	DS3231_SendData(I2Cx, 0x00);// send WORD ADDRESS 0
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Seconds));// send second
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Minutes));// send Minutes
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Hour));// send Hour
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Day));// send Day
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Date));// send Date
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Month));// send Month
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_Date->Year));// send Year

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop
};
void DS3231_ReadDateTime(I2C_TypeDef* I2Cx, struct DS3231_DateTime *DS3231_Date)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	DS3231_GoToAddress(I2Cx, 0x00);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));// wait send address ds3231

	DS3231_Date->Seconds = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive seconds
	DS3231_Date->Minutes = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Month
	DS3231_Date->Hour = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Hour
	DS3231_Date->Day = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Day
	DS3231_Date->Date = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Date
	DS3231_Date->Month = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Month
	DS3231_Date->Year = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Year

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);// create Not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop condition

	I2C_AcknowledgeConfig(I2Cx, ENABLE);// Enable acknowledge
};

void DS3231_SetAlarm1(I2C_TypeDef* I2Cx, struct DS3231_Alarm1 *DS3231_WriteAlarm1)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	DS3231_SendData(I2Cx, 0x07);// send WORD ADDRESS 7
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm1->Seconds));// send second
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm1->Minutes));// send Minutes
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm1->Hour));// send Hour
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm1->Day));// send Day
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm1->Date));// send Date

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop

	// Enable Interrupt for ALARM 1
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	I2C_SendData(I2Cx, 0x0E);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send word address 0x0E

	I2C_SendData(I2Cx, 0x1D);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send byte

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop
};
void DS3231_SetAlarm2(I2C_TypeDef* I2Cx, struct DS3231_Alarm2 *DS3231_WriteAlarm2)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	DS3231_SendData(I2Cx, 0x0B);// send WORD ADDRESS 7
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm2->Minutes));// send Minutes
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm2->Hour));// send Hour
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm2->Day));// send Day
	DS3231_SendData(I2Cx, DS3231_NumtoNumDS(DS3231_WriteAlarm2->Date));// send Date

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop

	// Enable Interrupt for ALARM 2
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	I2C_SendData(I2Cx, 0x0E);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send word address 7

	I2C_SendData(I2Cx, 0x1E);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send address

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop
};

void DS3231_GetAlarm1(I2C_TypeDef* I2Cx, struct DS3231_Alarm1 *DS3231_ReadAlarm1)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	DS3231_GoToAddress(I2Cx, 0x07);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));// wait send address

	DS3231_ReadAlarm1->Seconds = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive seconds
	DS3231_ReadAlarm1->Minutes = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Month
	DS3231_ReadAlarm1->Hour = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Hour
	DS3231_ReadAlarm1->Day = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Day
	DS3231_ReadAlarm1->Date = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Date

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);// generate not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);// generate stop condition
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop

	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge
};
void DS3231_GetAlarm2(I2C_TypeDef* I2Cx, struct DS3231_Alarm2 *DS3231_ReadAlarm2)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	DS3231_GoToAddress(I2Cx, 0x0B);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));// wait send address

	DS3231_ReadAlarm2->Minutes = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Month
	DS3231_ReadAlarm2->Hour = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Hour
	DS3231_ReadAlarm2->Day = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Day
	DS3231_ReadAlarm2->Date = DS3231_NumDStoNum(DS3231_ReceiveData(I2Cx));// receive Date

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);// generate not acknowledge
	I2C_AcknowledgeConfig(I2Cx, DISABLE);// disable acknowledge

	I2C_GenerateSTOP(I2Cx, ENABLE);// generate stop condition
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop

	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge
};

uint8_t DS3231_ReadFlag(I2C_TypeDef* I2Cx, uint8_t DS3231_FLAG)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	DS3231_GoToAddress(I2Cx, 0x0F);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));// wait send address ds3231

	uint8_t calculate = DS3231_ReceiveData(I2Cx) & DS3231_FLAG;// read Flag status

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2Cx, DISABLE);

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop condition

	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	return calculate;
};
void DS3231_ClearFlag(I2C_TypeDef* I2Cx, uint8_t DS3231_FLAG)
{
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
	I2C_AcknowledgeConfig(I2Cx, ENABLE);// enable acknowledge

	DS3231_GoToAddress(I2Cx, 0x0F);

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait Generate Start condition

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address ds3231

	I2C_SendData(I2Cx, 0x0F);// send world address 7
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send word address 7

	I2C_SendData(I2Cx, !DS3231_FLAG);// send FLAG bit for clear bit
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send address

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop
};

void DS3231_GoToAddress(I2C_TypeDef* I2Cx, uint8_t AddressByte)
{
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));// wait generate start

	I2C_Send7bitAddress(I2Cx, 0xD0, I2C_Direction_Transmitter);// send Address DS3231(0xD0)
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));// wait send address

	DS3231_SendData(I2Cx, AddressByte);// send WORD ADDRESS

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));// wait generate stop
};

void DS3231_SendData(I2C_TypeDef* I2Cx, uint8_t data)
{
	I2C_SendData(I2Cx, data);// send a byte
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));// wait send a byte
};
uint8_t DS3231_ReceiveData(I2C_TypeDef* I2Cx)
{
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));// wait receive a byte
	return I2C_ReceiveData(I2Cx);
};

unsigned char DS3231_NumtoNumDS(unsigned char value)
{
	unsigned char ReturnValue = 0;
	unsigned char DivideRemain = value;
	unsigned char NumDSList[8] = {80, 40, 20, 10, 8, 4, 2, 1};
	char i = 0;

	for(i = 0; i <= 7; i++)
	{
		if(DivideRemain >= NumDSList[i])
		{
			DivideRemain %= NumDSList[i];
			ReturnValue += pow(2, 8 - (i + 1));
		}
	}
	return ReturnValue;
};
unsigned char DS3231_NumDStoNum(unsigned char value)
{
	unsigned char ReturnValue = 0;
	unsigned char DivideRemain = value;
	unsigned char NumDSList[8] = {80, 40, 20, 10, 8, 4, 2, 1};
	unsigned char power = 0;
	char i = 0;

	for(i = 0; i <= 7; i++)
	{
		power = pow(2, 8 - (i + 1));

		if(DivideRemain >= power)
		{
			DivideRemain %= power;
			ReturnValue += NumDSList[i];
		}
	}
	return ReturnValue;
}
