
#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

void ADC_ON(char ADC_Channel_Number); // enable Chaneles ADC 
void ADC1_Init(void); // Init ADC1
void ADC2_Init(void); // Init ADC2
void ADC1_Injected_Init(); // init Injected ADC1
void ADC2_Injected_Init(); // init Injected ADC2
void ADC1_Regular_Init(); // init Regular ADC1
void ADC2_Regular_Init(); // init Regular ADC2
void ADC1_Start_Regular(char Channel_Number); // start ADC1 in mode Regular
void ADC2_Start_Regular(char Channel_Number); // start ADC2 in mode Regular

#endif