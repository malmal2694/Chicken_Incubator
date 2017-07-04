#define BIT8 8
#define BIT9 9

#define STOP0_5 1
#define STOP1 2
#define STOP1_5 3
#define STOP2 4

#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

void USART1Init(char length_Bit,char parity_N1Disable_N2Even_N3Odd,char stop_Bit,char ClockSyncronization_N1Disable_N2Enable);
void USART2Init(char length_Bit,char parity_N1Disable_N2Even_N3Odd,char stop_Bit,char ClockSyncronization_N1Disable_N2Enable);
void USART3Init(char length_Bit,char parity_N1Disable_N2Even_N3Odd,char stop_Bit,char ClockSyncronization_N1Disable_N2Enable);

void USART1_SendChar(char CHARACTER);
void USART2_SendChar(char CHARACTER);
void USART3_SendChar(char CHARACTER);

void USART1_Printf(char string[]);
void USART2_Printf(char string[]);
void USART3_Printf(char string[]);

void USART1_getChar(char *character);
void USART2_getChar(char *character);
void USART2_getChar(char *character);

void USART1_scanf(char *string, char charEnd);
void USART2_scanf(char *string, char charEnd);
void USART3_scanf(char *string, char charEnd);


#endif
