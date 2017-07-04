#include "LCD.h"
#include "GPIO.h"
#include <string.h>

#define OP Out_PP
#define D1 2// 2ms (6000)
#define D2 300000//60000
#define D3 10// 10ms (30000)
#define D4 4000000 //4000
#define LCD_FREQ 18000000// 18MHz

void LCD_Delay(__uint16_t Time_ms){
	while(Time_ms--)
		for (__uint16_t i = 0; i <= (LCD_FREQ / 10000); i++);// wait 1ms
};

/********* function for lcd 8bit initilize **************/
void LCD_8BIT_Init(struct PIN_LCD *PIN_LCD){
	Init_PIN(PIN_LCD->PORT_BIT0,PIN_LCD->PIN_BIT0,Config_Out_50MHz,OP); // set pin bit 0
	Init_PIN(PIN_LCD->PORT_BIT1,PIN_LCD->PIN_BIT1,Config_Out_50MHz,OP); // set pin bit 1
	Init_PIN(PIN_LCD->PORT_BIT2,PIN_LCD->PIN_BIT2,Config_Out_50MHz,OP); // set pin bit 2
	Init_PIN(PIN_LCD->PORT_BIT3,PIN_LCD->PIN_BIT3,Config_Out_50MHz,OP); // set pin bit 3
	Init_PIN(PIN_LCD->PORT_BIT4,PIN_LCD->PIN_BIT4,Config_Out_50MHz,OP); // set pin bit 4
	Init_PIN(PIN_LCD->PORT_BIT5,PIN_LCD->PIN_BIT5,Config_Out_50MHz,OP); // set pin bit 5
	Init_PIN(PIN_LCD->PORT_BIT6,PIN_LCD->PIN_BIT6,Config_Out_50MHz,OP); // set pin bit 6
	Init_PIN(PIN_LCD->PORT_BIT7,PIN_LCD->PIN_BIT7,Config_Out_50MHz,OP); // set pin bit 7
	Init_PIN(PIN_LCD->PORT_RS,PIN_LCD->PIN_RS,Config_Out_50MHz,OP); // set pin bit RS
	Init_PIN(PIN_LCD->PORT_E,PIN_LCD->PIN_E,Config_Out_50MHz,OP); // set pin bit E
	Init_PIN(PIN_LCD->PORT_RW,PIN_LCD->PIN_RW,Config_Out_50MHz,OP); // set pin bit RW
		
	LCD_Command(0x38,PIN_LCD); // send command to lcd for init lcd 8 bit
	LCD_Command(0x0F,PIN_LCD); // send command to lcd for Display ON
	LCD_Command(0x01,PIN_LCD); // send command to lcd for clear Display
	LCD_Command(0x0E,PIN_LCD); // send command to lcd for clear Display
	LCD_Command(192,PIN_LCD); // cursor go to row 1 & column 1 // 0x80
};

/************ send command to lcd *************/
void LCD_Command(unsigned char Command,struct PIN_LCD *PIN_LCD){
	Set_PIN_LCD(PIN_LCD,Command); // set Pins value
	Reset_PIN(PIN_LCD->PORT_RW,PIN_LCD->PIN_RW); // reset Pin RW
	Reset_PIN(PIN_LCD->PORT_RS,PIN_LCD->PIN_RS); // reset Pin RS
	Set_PIN(PIN_LCD->PORT_E,PIN_LCD->PIN_E); // set Pin Enable LCD
	LCD_Delay(D1);// wait 2ms
	Reset_PIN(PIN_LCD->PORT_E,PIN_LCD->PIN_E); // Reset Pin Enable LCD
	LCD_Delay(D1);// wait 2ms
	Reset_PIN_LCD(PIN_LCD,Command); // reset Pins data
};

/************ send Character to lcd *************/
void LCD_PutChar(char Char,struct PIN_LCD *PIN_LCD){
	Set_PIN_LCD(PIN_LCD,Char); // set pins data
	Set_PIN(PIN_LCD->PORT_RS,PIN_LCD->PIN_RS); // set pin RS
	Reset_PIN(PIN_LCD->PORT_RW,PIN_LCD->PIN_RW); // reset pin RW
	Set_PIN(PIN_LCD->PORT_E,PIN_LCD->PIN_E); // set pin E
	LCD_Delay(D1);// wait 2ms
	Reset_PIN(PIN_LCD->PORT_E,PIN_LCD->PIN_E); // reset pin Enable lcd
	LCD_Delay(D3);// wait 10ms
	Reset_PIN_LCD(PIN_LCD,Char); // reset pins data
};

/**************** Send String to LCD character *****************/
void LCD_Printf(char s[], struct PIN_LCD *PIN_LCD){
	char i = strlen(s); // variable i == number length string
	char c;
	for(c = 0;c < i;c++){
		LCD_PutChar(s[c], PIN_LCD); // send character
	}
};

/************** command Ready for LCD character **************/
void LCD_CLS(struct PIN_LCD *PIN_LCD){
	LCD_Command(0x01, PIN_LCD); // clear LCD character
};

void LCD_Home(struct PIN_LCD *PIN_LCD){
	LCD_Command(0x02, PIN_LCD); // return Home
};

void LCD_XY(char x, char y, struct PIN_LCD *PIN_LCD){
	if( (y == 1) && ( (x >= 0) && (x <= 16) ) ){
		LCD_Command( (128 | x) , PIN_LCD);
	}
	else if(y == 2 && ( (x >= 0 && x <= 16) ) ){
		LCD_Command( (128 | (x + 64) ) , PIN_LCD);
	}
};
void Set_PIN_LCD(struct PIN_LCD *PIN_LCD,char Value){
	if( (Value - 128) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT7,PIN_LCD->PIN_BIT7); // while (value -128) >=0 set PIN
	Value = Value - 128;
	};
	
	if( (Value - 64) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT6,PIN_LCD->PIN_BIT6); // while (value -64) >=0 set PIN
	Value = Value - 64;
	};
	
	if( (Value - 32) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT5,PIN_LCD->PIN_BIT5); // while (value -32) >=0 set PIN
	Value = Value - 32;
	};
	
	if( (Value - 16) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT4,PIN_LCD->PIN_BIT4); // while (value -16) >=0 set PIN
	Value = Value - 16;
	};
	
	if( (Value - 8) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT3,PIN_LCD->PIN_BIT3); // while (value -8) >=0 set PIN
	Value = Value - 8;
	};
	
	if( (Value - 4) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT2,PIN_LCD->PIN_BIT2); // while (value -4) >=0 set PIN
	Value = Value - 4;
	};
	
	if( (Value - 2) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT1,PIN_LCD->PIN_BIT1); // while (value -2) >=0 set PIN
	Value = Value - 2;
	};
	
	if( (Value - 1) >= 0){
	Set_PIN(PIN_LCD->PORT_BIT0,PIN_LCD->PIN_BIT0); // while (value -1) >=0 set PIN
	Value = Value - 1;
	};
	
};


void Reset_PIN_LCD(struct PIN_LCD *PIN_LCD,char Value){
	if( (Value - 128) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT7,PIN_LCD->PIN_BIT7); // while (value -128) >=0 reset PIN
	Value = Value - 128;
	};
	
	if( (Value - 64) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT6,PIN_LCD->PIN_BIT6); // while (value -64) >=0 reset PIN
	Value = Value - 64;
	};
	
	if( (Value - 32) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT5,PIN_LCD->PIN_BIT5); // while (value -32) >=0 reset PIN
	Value = Value - 32;
	};
	
	if( (Value - 16) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT4,PIN_LCD->PIN_BIT4); // while (value -16) >=0 reset PIN
	Value = Value - 16;
	};
	
	if( (Value - 8) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT3,PIN_LCD->PIN_BIT3); // while (value -8) >=0 reset PIN
	Value = Value - 8;
	};
	
	if( (Value - 4) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT2,PIN_LCD->PIN_BIT2); // while (value -4) >=0 reset PIN
	Value = Value - 4;
	};
	
	if( (Value - 2) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT1,PIN_LCD->PIN_BIT1); // while (value -2) >=0 reset PIN
	Value = Value - 2;
	};
	
	if( (Value - 1) >= 0){
	Reset_PIN(PIN_LCD->PORT_BIT0,PIN_LCD->PIN_BIT0); // while (value -1) >=0 reset PIN
	Value = Value - 1;
	};
	
};
