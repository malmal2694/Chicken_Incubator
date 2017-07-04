

// Declare Bits in Register RCC_APB2ENR
#define APB2_USART1 (1 << 14)
#define APB2_SPI1 (1 << 12)
#define APB2_TIM1 (1 << 11)
#define APB2_ADC2 (1 << 10)
#define APB2_ADC1 (1 << 9)
#define APB2_ADC3 (1 << 15)
#define APB2_IOPE 64
#define APB2_IOPC 16
#define APB2_IOPB 8
#define APB2_IOPA 4
#define APB2_IOPD 32
#define APB2_AFIO 1

// Declare Bits in Register RCC_APB1ENR
#define APB1_POWER (1 << 28)
#define APB1_BACKUP (1 << 27)
#define APB1_CAN2 (1 << 26)
#define APB1_CAN1 (1 << 25)
#define APB1_I2C2 (1 << 22)
#define APB1_I2C1 (1 << 21)
#define APB1_UART5 (1 << 20)
#define APB1_UART4 (1 << 19)
#define APB1_UART3 (1 << 18)
#define APB1_UART2 (1 << 17)
#define APB1_SPI3 (1 << 15)
#define APB1_SPI2 (1 << 14)
#define APB1_WWDG (1 << 11)
#define APB1_TIM7 (1 << 5)
#define APB1_TIM6 (1 << 4)
#define APB1_TIM5 (1 << 3)
#define APB1_TIM4 (1 << 2)
#define APB1_TIM3 (1 << 1)
#define APB1_TIM2 (1 << 0)

#ifndef RCC_H_INCLUDED
#define RCC_H_INCLUDED

void PLL_ON();
void PLL_OFF();
void PLL_MUL(char N2UPto_N16);
void PLL_PREDIV1(char);
void PLL_SRC_Sel(char N1HSIDiv2_N2HSE);
void Src_Sys_Clk(char N1HSI_N2HSE_N3PLL);
void AHB_Div(int N1_2_4_8_16_64_128_256_512);
void APB1_APB2_Div(char APB1_Div,char APB2_Div);
void SetPeriphAPB2(unsigned long int bit);
void SetPeriphAPB1(unsigned long int bit);
void HSEDivForPLL(char N1HSE_N1HSEDiv2);

#endif
