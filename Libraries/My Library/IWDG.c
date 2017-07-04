
#include "stm32f10x.h"
#include "IWDG.h"

void IWDG_Init(int Prescaler){
	RCC->CSR |= (1 << 0); // LSI ON
	while( ( (RCC->CSR) & (1 << 1) ) == 0 ); // wait ON LSI
	IWDG->KR = 0xCCCC; // Enable IWDG
	IWDG->KR = 0x5555; // Enable Register Access
	
	if(Prescaler == 4)
		
		IWDG->PR = 0; // frequency LSI / 4
	else if(Prescaler == 8)
		IWDG->PR = 1; // frequency LSI / 8
	
	else if(Prescaler == 16)
		IWDG->PR = 2; // frequency LSI / 16
	
	else if(Prescaler == 32)
		IWDG->PR = 3; // frequency LSI / 32
	
	else if(Prescaler == 64)
		IWDG->PR = 4; // frequency LSI / 64
	
	else if(Prescaler == 128)
		IWDG->PR = 5; // frequency LSI / 128
	
	else if(Prescaler == 256)
		IWDG->PR = 6; // frequency LSI / 256
	
	else
		while(1);

};

void IWDG_Reset(){
	IWDG->KR = 0xAAAA;
}