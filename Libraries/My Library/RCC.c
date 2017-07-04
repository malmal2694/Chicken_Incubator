#include "RCC.h"
#include "stm32f10x.h"

// Global Variables
char Src_SYS ;




void PLL_ON(void){
		RCC->CFGR &= ~(3 << 0); 
		RCC->CFGR |= Src_SYS; //system clock switch(Bit SW In Register CFGR) = Pvar Src_SYS
		RCC->CR |= (1 << 24); //PLL ON
		while( ((RCC->CR & (1 << 25) ) == 1) && ( ( RCC->CFGR & 12 ) != (Src_SYS << 2) ) ); //wait for start  
};

void PLL_OFF(void){
		Src_SYS = RCC->CFGR & (3);
		RCC->CFGR |= (3 << 0); //system clock switch = not allowed
		RCC->CR &= ~(1 << 24); // pll off
		while( ((RCC->CR & (1 << 25) ) == 0) && ((RCC->CFGR & 12)== 12) ); //wait for OFF PLL & SW
};

void PLL_MUL(char N2_16){
		if( (N2_16 >= 2) && (N2_16 <= 16) ){
				PLL_OFF(); //PLL Disable
				RCC->CFGR &= ~(0xf << 18); //PLLMUL = 0
				RCC->CFGR |= ( (N2_16 - 2) << 18 ); //set PLL Multiplication
				PLL_ON(); //PLL Enable
		}
};

void PLL_PREDIV1(char PLL_DivN1_16){    // this is function is Fulty
		PLL_OFF(); // PLL Disable
		RCC->CFGR &= ~(1 << 17); // PLLXTPRE(In Register CFGR) = 0
		//RCC->CFGR2 &= ~0xf; // set PREDIV1(In Register CFGR2) = 0
		//RCC->CFGR2 |= (PLL_DivN1_16 - 1) << 0; // set value PREDIV1(PLL Divader)
		PLL_ON(); // PLL Enable
};

void PLL_SRC_Sel(char Sourse ){
		while( (Sourse != 1) && (Sourse != 2) ); //sourse = 1 OR 2;
		PLL_OFF(); // PLL Disable
		RCC->CFGR &= ~(1 << 16); // Bit PLLSRC = 0;
		RCC->CFGR |= ( (Sourse - 1) << 16); // Set Bit PLLSRC = Sourse
		PLL_ON(); // PLL Enable
		while( ( RCC->CFGR & (1 << 16) ) != ( (Sourse - 1) << 16 ) ); //wait Set Bit PLLSRC = Sourse;
};

void Src_Sys_Clk(char SysClk){
		while( (SysClk < 1) || (SysClk > 3) ); // SysClk = 1-2-3
		RCC->CFGR &= ~(3 << 0); // Set Bit SW(in register CFGR) = 0
		RCC->CFGR |= ( (SysClk - 1) << 0 ); // Set Bit SW = SysClk
		while( ( RCC->CFGR & ( 3 << 2) ) != ( ( SysClk - 1) << 2 ) ); // Check Bit SW = SysClk
};

void AHB_Div(int Division){
		while(Division != 1 && Division != 2 && Division != 4 && Division != 8 && Division != 16 && Division != 64 && Division != 128 && Division != 256 && Division != 512 );  // Division = 1 Until =512
		switch (Division){
			
				case 1: RCC->CFGR &= ~(0xf << 4); // Set Bit HPRE[3:0](In Register CFGR) = 0
				RCC->CFGR |= (0 << 4); // set Bit HPRE = Division
				while( (RCC->CFGR & (0xf << 4) ) != ( 0 << 4 ) ); // check set HPRE = Division
				break;
				
				case 2: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (8 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 8 << 4 ) );
				break;
				
				case 4: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (9 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 9 << 4 ) );
				break;
				
				case 8: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (10 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 10 << 4 ) );
				break;
				
				case 16: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (11 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 11 << 4 ) );
				break;
				
				case 64: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (12 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 12 << 4 ) );
				break;
				
				case 128: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (13 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 13 << 4 ) );
				break;
				
				case 256: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (14 << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 14 << 4 ) );
				break;
				
				case 512: RCC->CFGR &= ~(0xf << 4);
				RCC->CFGR |= (0xf << 4);
				while( (RCC->CFGR & (0xf << 4) ) != ( 0xf << 4 ) );
				break;
		}
		
};

void APB1_APB2_Div(char APB1_Div,char APB2_Div){
		switch (APB1_Div){
				case 1: RCC->CFGR &= ~(7 << 8); // set Bit APB1(in register CFGR) = 0
				RCC->CFGR |= (0 << 8); // set Bit APB1 = APB1_Div
				while( (RCC->CFGR & (7 << 8) ) != ( 0 << 8 ) ); // check set Bit APB1 = APB1_Div
				break;	

				case 2: RCC->CFGR &= ~(7 << 8);
				RCC->CFGR |= (4 << 8);
				while( (RCC->CFGR & (7 << 8) ) != ( 4 << 8 ) );
				break;				

				case 4: RCC->CFGR &= ~(7 << 8);
				RCC->CFGR |= (5 << 8);
				while( (RCC->CFGR & (7 << 8) ) != ( 5 << 8 ) );
				break;				

				case 8: RCC->CFGR &= ~(7 << 8);
				RCC->CFGR |= (6 << 8);
				while( (RCC->CFGR & (7 << 8) ) != ( 6 << 8 ) );
				break;				

				case 16: RCC->CFGR &= ~(7 << 8);
				RCC->CFGR |= (7 << 8);
				while( (RCC->CFGR & (7 << 8) ) != ( 7 << 8 ) );
				break;	
				
				default : 
				while(1);
		} // end loop APB1
			
		
		switch (APB2_Div){
				case 1: RCC->CFGR &= ~(7 << 11); // set Bit APB2(in register CFGR) = 0
				RCC->CFGR |= (0 << 11); // set Bit APB2 = APB2_Div
				while( (RCC->CFGR & (7 << 11) ) != ( 0 << 11 ) ); // check set Bit APB2 = APB2_Div
				break;	

				case 2: RCC->CFGR &= ~(7 << 11);
				RCC->CFGR |= (4 << 11);
				while( (RCC->CFGR & (7 << 11) ) != ( 4 << 11 ) );
				break;				

				case 4: RCC->CFGR &= ~(7 << 11);
				RCC->CFGR |= (5 << 11);
				while( (RCC->CFGR & (7 << 11) ) != ( 5 << 11 ) );
				break;				

				case 8: RCC->CFGR &= ~(7 << 11);
				RCC->CFGR |= (6 << 11);
				while( (RCC->CFGR & (7 << 11) ) != ( 6 << 11 ) );
				break;				

				case 16: RCC->CFGR &= ~(7 << 11);
				RCC->CFGR |= (7 << 11);
				while( (RCC->CFGR & (7 << 11) ) != ( 7 << 11 ) );
				break;	
				
				default : 
				while(1);
		}; // end loop APB2
};

void SetPeriphAPB2(unsigned long int bit){ 
		RCC->APB2ENR |= bit;
		while( ( (RCC->APB2ENR) & bit ) != bit ); 
};

void SetPeriphAPB1(unsigned long int bit){ 
		RCC->APB1ENR |= bit;
		while( ( (RCC->APB1ENR) & bit ) != bit ); 
};

void HSEDivForPLL(char Div){
	while( (Div < 1) || (Div > 2) );
	Div--;
	RCC->CFGR &= ~(1 << 17);
	RCC->CFGR |=  Div<< 17;
	while( ( (RCC->CFGR) & ( Div << 17 ) ) != (Div << 17 ) );
};
