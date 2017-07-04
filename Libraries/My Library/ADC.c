
#include "stm32f10x.h"
#include "ADC.h"
#include "RCC.h"

void ADC_ON(char ADC_CH){
	while( ( ADC_CH != 1 ) && ( ADC_CH != 2 ) ); // check ADC_CH == 1 OR 2
	if(ADC_CH == 1){
		ADC1->CR2 |= 1; // enable ADC1
	}
	else{
		ADC2->CR2 |= 1; // enable ADC2
	}
};

void ADC1_Init(void){
	ADC_ON(1); // enable ADC1
	ADC1->CR2 |= (1 << 3); // Reset Calibration ADC1
	while( ( ( (ADC1->CR2) & (1 << 3) ) != 0 ) ); // Calibration initialized
	ADC1->CR2 |= (1 << 2); // Enable Calibration
	while( ( ( (ADC1->CR2) & (1 << 2) ) != 0 ) ); // Calibration Completed
};

void ADC2_Init(void){
	ADC_ON(2); // enable ADC1
	ADC2->CR2 |= (1 << 3); // Reset Calibration ADC1
	while( ( ( (ADC2->CR2) & (1 << 3) ) != 0 ) ); // Calibration initialized
	ADC2->CR2 |= (1 << 2); // Enable Calibration
	while( ( ( (ADC2->CR2) & (1 << 2) ) != 0 ) ); // Calibration Completed
};

void ADC1_Injected_Init(){
	ADC1->CR2 |= (1 << 15); // External trigger == Enable
	ADC1->CR2 |= (7 << 12); // External event select == JSWSTART(In Register CR2)
	ADC1->CR1 |= (1 << 12); // Discontinuous mode on injected channels. Bit JDISCEN(In Register CR1) == Enable	
};

void ADC2_Injected_Init(){
	ADC2->CR2 |= (1 << 15); // External trigger == Enable
	ADC2->CR2 |= (7 << 12); // External event select == JSWSTART(In Register CR2)
	ADC2->CR1 |= (1 << 12); // Discontinuous mode on injected channels. Bit JDISCEN(In Register CR1) == Enable	
};

void ADC1_Regular_Init(){
	ADC1->CR2 |= (1 << 20); // External trigger == Enable
	ADC1->CR2 |= (7 << 17); // External event select == SWSTART(In Register CR2)
	ADC1->CR1 |= (1 << 1); // Discontinuous mode on injected channels. Bit DISCEN(In Register CR1) == Enable	
};

void ADC2_Regular_Init(){
	ADC2->CR2 |= (1 << 20); // External trigger == Enable
	ADC2->CR2 |= (7 << 17); // External event select == SWSTART(In Register CR2)
	ADC2->CR1 |= (1 << 11); // Discontinuous mode on injected channels. Bit DISCEN(In Register CR1) == Enable	
};

void ADC1_Start_Regular(char CH){
	ADC1->SQR3 |= (CH << 0); // enter channel ADC1 for convert
	while( ( (ADC1->SQR3) & 31) != CH); // write channel ADC1 for convert(In Register SQR3)
	ADC1->CR2 |= (1 << 22); // start conversion
};

void ADC2_Start_Regular(char CH){
	ADC2->SQR3 |= (CH << 0); // enter channel ADC1 for convert
	while( ( (ADC2->SQR3) & 31) != CH); // write channel ADC1 for convert(In Register SQR3)
	ADC2->CR2 |= (1 << 22); // start conversion
};
