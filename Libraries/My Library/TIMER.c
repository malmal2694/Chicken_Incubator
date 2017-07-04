#include "TIMER.h"
#include "GPIO.h"
#include "stm32f10x.h"
#include "RCC.h"


void TimPinOutInit(int Port,int Pin){
	Init_PIN(Port,Pin,Config_Out_50MHz,Alter_Out_PP);
};

void Tim1_PWM_Enable(char CH,int CCR){	
	if(CH == 1){
		TIM1->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM1->CCMR1 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM1->CCMR1 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM1->CCER |= (1 << 0); // Capture/Compare 1 output enable
		TIM1->BDTR |= (1 << 15) | (1 << 14); // Main output enable And Automatic output enable
		TIM1->CCR1 = CCR; // set Valude Register CCR1
	}

	else if(CH == 2){
		TIM1->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM1->CCMR1 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM1->CCMR1 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM1->CCER |= (1 << 4); // Capture/Compare 2 output enable
		TIM1->BDTR |= (1 << 15) | (1 << 14); // Main output enable And Automatic output enable
		TIM1->CCR2 = CCR; // set Valude Register CCR2
	}

	else if(CH == 3){
		TIM1->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM1->CCMR2 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM1->CCMR2 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM1->CCER |= (1 << 8); // Capture/Compare 3 output enable
		TIM1->BDTR |= (1 << 15) | (1 << 14); // Main output enable And Automatic output enable
		TIM1->CCR3 = CCR; // set Valude Register CCR3
	}

	else if(CH == 4){
		TIM1->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM1->CCMR2 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM1->CCMR2 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM1->CCER |= (1 << 12); // Capture/Compare 4 output enable
		TIM1->BDTR |= (1 << 15) | (1 << 14); // Main output enable And Automatic output enable
		TIM1->CCR4 = CCR; // set Valude Register CCR4
	}
	
	else while(1); // number Channel > 4
};

void Tim2_PWM_Enable(char CH,int CCR){	
	if(CH == 1){
		TIM2->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM2->CCMR1 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM2->CCMR1 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM2->CCER |= (1 << 0); // Capture/Compare 1 output enable
		TIM2->CCR1 = CCR; // set Valude Register CCR1
	}

	else if(CH == 2){
		TIM2->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM2->CCMR1 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM2->CCMR1 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM2->CCER |= (1 << 4); // Capture/Compare 2 output enable
		TIM2->CCR2 = CCR; // set Valude Register CCR2
	}

	else if(CH == 3){
		TIM2->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM2->CCMR2 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM2->CCMR2 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM2->CCER |= (1 << 8); // Capture/Compare 3 output enable
		TIM2->CCR3 = CCR; // set Valude Register CCR3
	}

	else if(CH == 4){
		TIM2->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM2->CCMR2 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM2->CCMR2 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM2->CCER |= (1 << 12); // Capture/Compare 4 output enable
		TIM2->CCR4 = CCR; // set Valude Register CCR4
	}
	
	else while(1); // number Channel > 4
};

void Tim3_PWM_Enable(char CH,int CCR){	
	if(CH == 1){
		TIM3->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM3->CCMR1 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM3->CCMR1 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM3->CCER |= (1 << 0); // Capture/Compare 1 output enable
		TIM3->CCR1 = CCR; // set Valude Register CCR1
	}

	else if(CH == 2){
		TIM3->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM3->CCMR1 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM3->CCMR1 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM3->CCER |= (1 << 4); // Capture/Compare 2 output enable
		TIM3->CCR2 = CCR; // set Valude Register CCR2
	}

	else if(CH == 3){
		TIM3->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM3->CCMR2 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM3->CCMR2 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM3->CCER |= (1 << 8); // Capture/Compare 3 output enable
		TIM3->CCR3 = CCR; // set Valude Register CCR3
	}

	else if(CH == 4){
		TIM3->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM3->CCMR2 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM3->CCMR2 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM3->CCER |= (1 << 12); // Capture/Compare 4 output enable
		TIM3->CCR4 = CCR; // set Valude Register CCR4
	}
	
	else while(1); // number Channel > 4
};

void Tim4_PWM_Enable(char CH,int CCR){	
	if(CH == 1){
		TIM4->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM4->CCMR1 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM4->CCMR1 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM4->CCER |= (1 << 0); // Capture/Compare 1 output enable
		TIM4->CCR1 = CCR; // set Valude Register CCR1
	}

	else if(CH == 2){
		TIM4->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM4->CCMR1 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM4->CCMR1 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM4->CCER |= (1 << 4); // Capture/Compare 2 output enable
		TIM4->CCR2 = CCR; // set Valude Register CCR2
	}

	else if(CH == 3){
		TIM4->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM4->CCMR2 &= ~( (7 << 4) | (1 << 3) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM4->CCMR2 |= (6 << 4) | (1 << 3); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM4->CCER |= (1 << 8); // Capture/Compare 3 output enable
		TIM4->CCR3 = CCR; // set Valude Register CCR3
	}

	else if(CH == 4){
		TIM4->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
		TIM4->CCMR2 &= ~( (7 << 12) | (1 << 11) ); // set type PWM Mode1 And Output Compare 1 preload == 0
		TIM4->CCMR2 |= (6 << 12) | (1 << 11); // set type PWM Mode1 And Output Compare 1 preload enable
		TIM4->CCER |= (1 << 12); // Capture/Compare 4 output enable
		TIM4->CCR4 = CCR; // set Valude Register CCR4
	}
	
	else while(1); // number Channel > 4
};


/********function TIMER1 Enable *************/
void Tim1Enable(char CH,int CCR,char MODE_IO){
	TIM1->BDTR |= (1 << 15) | (1 << 14); // Main output enable And Automatic output enable
	TIM1->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
	
	if(CH == 1){ // channel == 1
		TIM1->CCR1 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM1->CCMR1 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM1->CCER |= (1 << 0); // enable output Bit CC1E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM1->CCMR1 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM1->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM1->CCMR1 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM1->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM1->CCMR1 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM1->CCER &= ~(1); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 2){ // channel == 2
		TIM1->CCR2 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM1->CCMR1 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM1->CCER |= (1 << 4); // enable output Bit CC2E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM1->CCMR1 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM1->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM1->CCMR1 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM1->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM1->CCMR1 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM1->CCER &= ~(16); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 3){ // channel == 3
		TIM1->CCR3 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM1->CCMR2 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM1->CCER |= (1 << 8); // enable output Bit CC3E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM1->CCMR2 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM1->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM1->CCMR2 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM1->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM1->CCMR2 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM1->CCER &= ~(1 << 8); // disable output Bit CC1E
			break;
		}
	}	
	else if(CH == 4){ // channel == 4
		TIM1->CCR4 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM1->CCMR2 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM1->CCER |= (1 << 12); // enable output Bit CC4E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM1->CCMR2 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM1->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM1->CCMR2 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM1->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM1->CCMR2 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM1->CCER &= ~(1 << 12); // disable output Bit CC4E
			break;
		}
	}	

};


/********function TIMER2 Enable *************/
void Tim2Enable(char CH,int CCR,char MODE_IO){
	TIM2->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
	
	if(CH == 1){ // channel == 1
		TIM2->CCR1 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM2->CCMR1 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM2->CCER |= (1 << 0); // enable output Bit CC1E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM2->CCMR1 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM2->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM2->CCMR1 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM2->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM2->CCMR1 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM2->CCER &= ~(1); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 2){ // channel == 2
		TIM2->CCR2 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM2->CCMR1 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM2->CCER |= (1 << 4); // enable output Bit CC2E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM2->CCMR1 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM2->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM2->CCMR1 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM2->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM2->CCMR1 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM2->CCER &= ~(16); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 3){ // channel == 3
		TIM2->CCR3 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM2->CCMR2 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM2->CCER |= (1 << 8); // enable output Bit CC3E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM2->CCMR2 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM2->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM2->CCMR2 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM2->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM2->CCMR2 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM2->CCER &= ~(1 << 8); // disable output Bit CC1E
			break;
		}
	}	
	else if(CH == 4){ // channel == 4
		TIM2->CCR4 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM2->CCMR2 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM2->CCER |= (1 << 12); // enable output Bit CC4E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM2->CCMR2 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM2->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM2->CCMR2 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM2->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM2->CCMR2 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM2->CCER &= ~(1 << 12); // disable output Bit CC4E
			break;
		}
	}	

}


/********function TIMER3 Enable *************/
void Tim3Enable(char CH,int CCR,char MODE_IO){
	TIM3->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
	
	if(CH == 1){ // channel == 1
		TIM3->CCR1 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM3->CCMR1 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM3->CCER |= (1 << 0); // enable output Bit CC1E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM3->CCMR1 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM3->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM3->CCMR1 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM3->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM3->CCMR1 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM3->CCER &= ~(1); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 2){ // channel == 2
		TIM3->CCR2 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM3->CCMR1 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM3->CCER |= (1 << 4); // enable output Bit CC2E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM3->CCMR1 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM3->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM3->CCMR1 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM3->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM3->CCMR1 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM3->CCER &= ~(16); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 3){ // channel == 3
		TIM3->CCR3 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM3->CCMR2 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM3->CCER |= (1 << 8); // enable output Bit CC3E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM3->CCMR2 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM3->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM3->CCMR2 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM3->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM3->CCMR2 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM3->CCER &= ~(1 << 8); // disable output Bit CC1E
			break;
		}
	}	
	else if(CH == 4){ // channel == 4
		TIM3->CCR4 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM3->CCMR2 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM3->CCER |= (1 << 12); // enable output Bit CC4E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM3->CCMR2 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM3->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM3->CCMR2 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM3->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM3->CCMR2 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM3->CCER &= ~(1 << 12); // disable output Bit CC4E
			break;
		}
	}	

}


/********function TIMER4 Enable *************/
void Tim4Enable(char CH,int CCR,char MODE_IO){
	TIM4->CR1 |= (1 << 0) | (1 << 7); // set counter And Bit ARPE
	
	if(CH == 1){ // channel == 1
		TIM4->CCR1 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM4->CCMR1 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM4->CCER |= (1 << 0); // enable output Bit CC1E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM4->CCMR1 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM4->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM4->CCMR1 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM4->CCER |= (1 << 0); // enable output Bit CC1E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM4->CCMR1 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM4->CCER &= ~(1); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 2){ // channel == 2
		TIM4->CCR2 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM4->CCMR1 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM4->CCER |= (1 << 4); // enable output Bit CC2E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM4->CCMR1 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM4->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM4->CCMR1 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM4->CCER |= (1 << 4); // enable output Bit CC2E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM4->CCMR1 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM4->CCER &= ~(16); // disable output Bit CC1E
			break;
		}
	}
	else if(CH == 3){ // channel == 3
		TIM4->CCR3 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM4->CCMR2 |= (1 << 4); // MODE Output TIMER = SET PIN
			TIM4->CCER |= (1 << 8); // enable output Bit CC3E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM4->CCMR2 |= (2 << 4); // MODE Output TIMER = RESET PIN
			TIM4->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM4->CCMR2 |= (3 << 4); // MODE Output TIMER = TOGGLE PIN
			TIM4->CCER |= (1 << 8); // enable output Bit CC3E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM4->CCMR2 |= (2 << 4); // MODE Output TIMER = None envent In Output TIMER
			TIM4->CCER &= ~(1 << 8); // disable output Bit CC1E
			break;
		}
	}	
	else if(CH == 4){ // channel == 4
		TIM4->CCR4 = CCR; // set value CCRx
		switch (MODE_IO){
			case 1 : // MODE Output == SET PIN TIMER
			TIM4->CCMR2 |= (1 << 12); // MODE Output TIMER = SET PIN
			TIM4->CCER |= (1 << 12); // enable output Bit CC4E
			break;
			
			case 2 : // MODE Output == RESET PIN TIMER
			TIM4->CCMR2 |= (2 << 12); // MODE Output TIMER = RESET PIN
			TIM4->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 3 : // MODE Output == TOGGLE PIN TIMER
			TIM4->CCMR2 |= (3 << 12); // MODE Output TIMER = TOGGLE PIN
			TIM4->CCER |= (1 << 12); // enable output Bit CC4E
			break;

			case 4 : // MODE Output == None envent In Output TIMER
			TIM4->CCMR2 |= (2 << 12); // MODE Output TIMER = None envent In Output TIMER
			TIM4->CCER &= ~(1 << 12); // disable output Bit CC4E
			break;
		}
	}	

}

void PWM_SetCCR(TIM_TypeDef* TIMx, char CCRx, float CCRxVal)
{
	if(CCRx == 1){
		TIMx->CCR1 = ( (CCRxVal * TIMx->ARR) / 100 ) +1;// set value CCR1
	}
	else if(CCRx == 2){
		TIMx->CCR2 = ( (CCRxVal * TIMx->ARR) / 100 ) +1;// set value CCR2
	}
	else if(CCRx == 3){
		TIMx->CCR3 = ( (CCRxVal * TIMx->ARR) / 100 ) +1;// set value CCR3
	}
	else if(CCRx == 4){
		TIMx->CCR4 = ( (CCRxVal * TIMx->ARR) / 100 ) +1;// set value CCR4
	};
};
float PWM_GetCCR(TIM_TypeDef* TIMx, char CCRx)
{
	if(CCRx == 1)
		return (100 * TIMx->CCR1) / TIMx->ARR;// return PWM value(percent)

	else if(CCRx == 2)
		return (100 * TIMx->CCR1) / TIMx->ARR;// return PWM value(percent)

	else if(CCRx == 3)
		return (100 * TIMx->CCR1) / TIMx->ARR;// return PWM value(percent)

	else if(CCRx == 4)
		return (100 * TIMx->CCR1) / TIMx->ARR;// return PWM value(percent)

};

