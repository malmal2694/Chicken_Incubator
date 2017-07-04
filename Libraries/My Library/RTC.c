
#include "stm32f10x.h"
#include "RTC.h"

void RTC_Init(uint16_t Div){
	PWR->CR |= (1 << 8); // Bit 8 : Disable backup domain write protection
	RCC->BDCR |= (1 << 8); // set sourse clock : LSE
	while( ( (RCC->BDCR) & (3 << 8) ) != (1 << 8) ); // wait set sourse clock RTC == LSE
	RCC->BDCR |= (1 << 16); // Backup domain software reset
	RCC->BDCR |= (1 << 0); // LSE ON
	while( ( (RCC->BDCR) & (1 << 1) ) != (1 << 1) ); // LSE Ready
	RCC->BDCR |= (1 << 15); // RTC Enable
	while( ( (RCC->BDCR) & (1 << 15) ) != (1 << 15) ); // wait RTC ON

	while( ( (RTC->CRL) & (1 << 5) ) != (1 << 5) ); // wait set Bit RTOFF
	RTC->CRL |= (1 << 4); // set bit CNF
	RTC->PRLL = Div; // set Prescaler == Div variable
	RTC->CRL &= ~(1 << 4); // reset bit CNF
	while( ( (RTC->CRL) & (1 << 5) ) != (1 << 5) ); // wait set Bit RTOFF
}