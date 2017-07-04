
struct PIN_LCD{ // init ports lcd
	char PIN_BIT0;
	char PORT_BIT0;
	char PIN_BIT1;
	char PORT_BIT1;
	char PIN_BIT2;
	char PORT_BIT2;
	char PIN_BIT3;
	char PORT_BIT3;
	char PIN_BIT4;
	char PORT_BIT4;
	char PIN_BIT5;
	char PORT_BIT5;
	char PIN_BIT6;
	char PORT_BIT6;
	char PIN_BIT7;
	char PORT_BIT7;
	char PORT_RS;
	char PIN_RS;
	char PORT_RW;
	char PIN_RW;
	char PORT_E;
	char PIN_E;
	
};

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

void LCD_8BIT_Init(struct PIN_LCD *PIN_LCD);
void Set_PIN_LCD(struct PIN_LCD *PIN_LCD,char Value);
void Reset_PIN_LCD(struct PIN_LCD *PIN_LCD,char Value);
void LCD_Command(unsigned char Command,struct PIN_LCD *PIN_LCD);
void LCD_PutChar(char Character,struct PIN_LCD *PIN_LCD);
void LCD_Printf(char s[], struct PIN_LCD *PIN_LCD);

void LCD_CLS(struct PIN_LCD *PIN_LCD);
void LCD_Home(struct PIN_LCD *PIN_LCD);
void LCD_XY(char x, char y, struct PIN_LCD *PIN_LCD);

#endif
