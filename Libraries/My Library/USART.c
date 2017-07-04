#include "stm32f10x.h"
#include "GPIO.h"
#include "USART.h"
#include <string.h>


/*void delay(int Time){
	unsigned int i,time;
    for(i = 0; i <= Time; i++);
};*/

/******** Functions USART Init *************/
void USART1Init(char length,char Parity,char stop,char Clock){
	USART1->CR1 |= (1 << 13); // usart enable
	while( ( (USART1->CR1) & (1 << 13) ) != (1 << 13) ); // wait usart enable
	USART1->CR1 |= (1 << 3) | (1 << 2); // Rx And Tx Enable
	if(length == 8){
		USART1->CR1 &= ~(1 << 12); // word length == 8
	}
	else if(length == 9){
		USART1->CR1 |= (1 << 12); // word length == 9
	}
	else
		while(1);

	if(Parity == 1){
		USART1->CR1 &= ~(1 << 10); // Parity Disable
	}
	else if(Parity == 2){
		USART1->CR1 |= (1 << 10); // Parity Enable & Even Parity
	}
	else if(Parity == 3){
		USART1->CR1 |= (1 << 10) | (1 << 9); // Parity Enable & Odd Parity
	}
	else
		while(1);

	if(stop == 1){
		USART1->CR2 &= ~(3 << 12); // stop Bit == 1
		USART1->CR2 |= (1 << 12); // stop Bit == 0.5 Stop Bit
	}
	else if(stop == 2){
		USART1->CR2 &= ~(3 << 12); // stop Bit == 1 Stop Bit
	}
	else if(stop == 3){
		USART1->CR2 |= (3 << 12); // stop Bit == 1.5 Stop Bit

	}
	else if(stop == 4){
		USART1->CR2 &= ~(3 << 12); // stop Bit == 0
		USART1->CR2 |= (2 << 12); // stop Bit == 2 Stop Bit
	}
	else
		while(1);

	if(Clock == 1){
		USART1->CR2 &= ~(1 << 11); // Clock Disable
	}
	else if(Clock == 2){
		USART1->CR2 |= (1 << 11); // Clock Enable
	}
	else
		while(1);

}

void USART2Init(char length,char Parity,char stop,char Clock){
	USART2->CR1 |= (1 << 13); // usart enable
	USART2->CR1 |= (1 << 3) | (1 << 2); // Rx And Tx Enable
	if(length == 8){
		USART2->CR1 &= ~(1 << 12); // word length == 8
	}
	else if(length == 9){
		USART2->CR1 |= (1 << 12); // word length == 9
	}
	else
		while(1);

	if(Parity == 1){
		USART2->CR1 &= ~(1 << 10); // Parity Disable
	}
	else if(Parity == 2){
		USART2->CR1 |= (1 << 10); // Parity Enable & Even Parity
	}
	else if(Parity == 3){
		USART2->CR1 |= (1 << 10) | (1 << 9); // Parity Enable & Odd Parity
	}
	else
		while(1);

	if(stop == 1){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0
		USART2->CR2 |= (1 << 12); // stop Bit == 0.5 Stop Bit
	}
	else if(stop == 2){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0.5 Stop Bit
	}
	else if(stop == 3){
		USART2->CR2 |= (3 << 12); // stop Bit == 1.5 Stop Bit

	}
	else if(stop == 4){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0
		USART2->CR2 |= (2 << 12); // stop Bit == 2 Stop Bit
	}
	else
		while(1);

	if(Clock == 1){
		USART2->CR2 &= ~(1 << 11); // Clock Disable
	}
	else if(Clock == 2){
		USART2->CR2 |= (1 << 11); // Clock Enable
	}
	else
		while(1);

}

void USART3Init(char length,char Parity,char stop,char Clock){
	USART3->CR1 |= (1 << 13); // usart enable
	USART3->CR1 |= (1 << 3) | (1 << 2); // Rx And Tx Enable
	if(length == 8){
		USART2->CR1 &= ~(1 << 12); // word length == 8
	}
	else if(length == 9){
		USART2->CR1 |= (1 << 12); // word length == 9
	}
	else
		while(1);

	if(Parity == 1){
		USART2->CR1 &= ~(1 << 10); // Parity Disable
	}
	else if(Parity == 2){
		USART2->CR1 |= (1 << 10); // Parity Enable & Even Parity
	}
	else if(Parity == 3){
		USART2->CR1 |= (1 << 10) | (1 << 9); // Parity Enable & Odd Parity
	}
	else
		while(1);

	if(stop == 1){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0
		USART2->CR2 |= (1 << 12); // stop Bit == 0.5 Stop Bit
	}
	else if(stop == 2){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0.5 Stop Bit
	}
	else if(stop == 3){
		USART2->CR2 |= (3 << 12); // stop Bit == 1.5 Stop Bit

	}
	else if(stop == 4){
		USART2->CR2 &= ~(3 << 12); // stop Bit == 0
		USART2->CR2 |= (2 << 12); // stop Bit == 2 Stop Bit
	}
	else
		while(1);

	if(Clock == 1){
		USART2->CR2 &= ~(1 << 11); // Clock Disable
	}
	else if(Clock == 2){
		USART2->CR2 |= (1 << 11); // Clock Enable
	}
	else
		while(1);

};

/**************** functions send character ******************/
void USART1_SendChar(char Char){
	USART1->DR = Char;
	while( ( (USART1->SR) & (1 << 6) ) != (1 << 6) ); // wait if Bits TC == 0
	USART1->SR &= ~(1 << 6); // set TC == 0
};

void USART2_SendChar(char Char){
	USART2->DR = Char;
	while( ( (USART2->SR) & (1 << 6) ) != (1 << 6) ); // if Bits TC == 0
	USART2->SR &= ~(1 << 6); // set TC == 0
};

void USART3_SendChar(char Char){
	USART3->DR = Char;
	while( ( (USART3->SR) & (1 << 6) ) != (1 << 6) ); // if Bits TC == 0
	USART3->SR &= ~(1 << 6); // set TC == 0
};

/************** functions printf *********************/
void USART1_Printf(char s[]){
	char i = strlen(s); // variable i == number length string
	char c;
	for(c = 0;c <= i;c++){
		USART1_SendChar(s[c]); // send character
	}
};

void USART2_Printf(char s[]){
	char i = strlen(s); // variable i == number length string
	char c;
	for(c = 0;c <= i;c++){
		USART2_SendChar(s[c]); // send character
	}
};

void USART3_Printf(char s[]){
	char i = strlen(s); // variable i == number length string
	char c;
	for(c = 0;c <= i;c++){
		USART3_SendChar(s[c]); // send character
	}
};

/**************** functions for receive a character **********/
void USART1_getChar(char *character) {
	while (!(((USART1->SR) & (1 << 5)) == (1 << 5))); // while receive a character
	*character = USART1->DR; // set variable string = register (DR)
};

void USART2_getChar(char *character) {
	while (!(((USART2->SR) & (1 << 5)) == (1 << 5))); // while receive a character
	*character = USART2->DR; // set variable string = register (DR)
};

void USART3_getChar(char *character) {
	while (!(((USART3->SR) & (1 << 5)) == (1 << 5))); // while receive a character
	*character = USART3->DR; // set variable string = register (DR)
};

/**************** function for receive text *****************/
void USART1_scanf(char *string, char charEnd) {// variable *string is a pointer And Calling function : USART1_sanf(nameArray); need not operator *(star)
	unsigned char i = 0; // declare variable
	while( ( !( (USART1->DR) == charEnd) ) ){
		while (!( ( (USART1->SR) & (1 << 5) ) == (1 << 5) ) ); // while receive a character
		string[i++] = USART1->DR; // set variable string = register (DR)
	};
};

void USART2_scanf(char *string, char charEnd) {// variable *string is a pointer And Calling function : USART1_sanf(nameArray); need not operator *(star)
	unsigned char i = 0; // declare variable
	while( ( !( (USART2->DR) == charEnd) ) ){
		while (!( ( (USART2->SR) & (1 << 5) ) == (1 << 5) ) ); // while receive a character
		string[i++] = USART2->DR; // set variable string = register (DR)
	};
};

void USART3_scanf(char *string, char charEnd) {// variable *string is a pointer And Calling function : USART1_sanf(nameArray); need not operator *(star)
	unsigned char i = 0; // declare variable
	while( ( !( (USART3->DR) == charEnd) ) ){
		while (!( ( (USART3->SR) & (1 << 5) ) == (1 << 5) ) ); // while receive a character
		string[i++] = USART3->DR; // set variable string = register (DR)
	};
};

