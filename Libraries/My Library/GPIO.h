/****** names ports **********/
#define PORTA 1
#define PORTB 2
#define PORTC 3
#define PORTD 4
#define PORTE 5



/******** names pins *********/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15

/*******  input/output *********/
#define Config_IN 0
#define Config_Out_10MHz 1
#define Config_Out_2MHz 2
#define Config_Out_50MHz 3

/********* mode in input and output *********/
#define Mode_AIN 0
#define Mode_IN_FLOATING 1
#define Mode_IPU 2
#define Mode_IPD 2

#define Out_PP 0
#define Out_OD 1
#define Alter_Out_PP 2
#define Alter_Out_OD 3

/****** end define ************/



#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED


void Init_PIN(char Port,char PIN,char Config_IO,char Mode);

void Set_PINA(char PIN);
void Set_PINB(char PIN);
void Set_PINC(char PIN);
void Set_PIND(char PIN);
void Set_PINE(char PIN);
void Set_PIN(char PORT,char PIN);

void Reset_PINA(char PIN);
void Reset_PINB(char PIN);
void Reset_PINC(char PIN);
void Reset_PIND(char PIN);
void Reset_PINE(char PIN);
void Reset_PIN(char PORT,char PIN);


#endif
