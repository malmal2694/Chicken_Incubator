
#include "stm32f10x.h"
#define PIN_SET 1
#define PIN_RESET 2
#define PIN_TOGGLE 3
#define PIN_NONE 4

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

void TimPinOutInit(int PortTim,int PinTim); // init Pin For Timer As Ouput
void Tim1_PWM_Enable(char CH,int Value_CCR); // enable PWMx in Timer1
void Tim2_PWM_Enable(char CH,int Value_CCR); // enable PWMx in Timer3
void Tim3_PWM_Enable(char CH,int Value_CCR); // enable PWMx in Timer3
void Tim4_PWM_Enable(char CH,int Value_CCR); // enable PWMx in Timer4
void Tim1Enable(char CH,int Value_CCR,char MODE_IO); // Enable Timer1
void Tim2Enable(char CH,int Value_CCR,char MODE_IO); // Enable Timer2
void Tim3Enable(char CH,int Value_CCR,char MODE_IO); // Enable Timer3
void Tim4Enable(char CH,int Value_CCR,char MODE_IO); // Enable Timer4
void PWM_SetCCR(TIM_TypeDef* TIMx, char CCRx, float CCRxVal);
float PWM_GetCCR(TIM_TypeDef* TIMx, char CCRx);

#endif
