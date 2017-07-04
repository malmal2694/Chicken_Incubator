#include "GPIO.h"
#include "stm32f10x.h"



void Init_PIN(char Port,char PIN,char Config_IO,char Mode){
        switch (Port){
			case 1: //PORT is A
				while( ( (Config_IO < 0) || (Config_IO > 3) ) || ( (Mode <0) || (Mode > 3) ) ); // check Config_IO And Mode Not INvalid 
				if( (PIN >= 0) && (PIN <= 7) ){ // Number Pin Between 0 And 7
					GPIOA->CRL &=  ~( 3 << (PIN * 4) ); // Config Bit Mode(In Register CRL) == 0
					GPIOA->CRL &= ~( 3  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode == 0
					GPIOA->CRL |= ( Config_IO << (PIN * 4)  ); // Config Bit Mode(In Register CRL) 
					GPIOA->CRL |= ( Mode  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode 
					while( ( ( GPIOA->CRL & ( 3 << (PIN * 4) ) ) != ( Config_IO << (PIN * 4) ) )  ||  ( ( GPIOA->CRL & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( PIN * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRL)
				}
				else if( (PIN >= 8) && (PIN <= 15) ){ // Number Pin Between 8 And 15
					GPIOA->CRH &=  ~( 3 << ( ( PIN - 8 ) * 4) ); // Config Bit Mode(In Register CRH) == 0
					GPIOA->CRH &= ~( 3  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode == 0
					GPIOA->CRH |= ( Config_IO << ( (PIN - 8) * 4)  ); // Config Bit Mode(In Register CRH) 
					GPIOA->CRH |= ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode 
					while( ( ( GPIOA->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << ( ( PIN - 8 ) * 4) ) )  ||  ( ( GPIOA->CRH & ( 3  << ( ( ( PIN - 8 ) * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRH)                                             
				}
				else{
				    while(1);
				};
				break;
				
			case 2: //PORT is B
				while( ( (Config_IO < 0) || (Config_IO > 3) ) || ( (Mode <0) || (Mode > 3) ) ); // check Config_IO And Mode Not INvalid
				if( (PIN >= 0) && (PIN <= 7) ){ // Number Pin Between 0 And 7
					GPIOB->CRL &=  ~( 3 << (PIN * 4) ); // Config Bit Mode(In Register CRL) == 0
					GPIOB->CRL &= ~( 3  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode == 0
					GPIOB->CRL |= ( Config_IO << (PIN * 4)  ); // Config Bit Mode(In Register CRL) 
					GPIOB->CRL |= ( Mode  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode
					while( ( ( GPIOB->CRL & ( 3 << (PIN * 4) ) ) != ( Config_IO << (PIN * 4) ) )  ||  ( ( GPIOB->CRL & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( PIN * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRL)					
				}
				else if( (PIN >= 8) && (PIN <= 15) ){ // Number Pin Between 8 And 15
					GPIOB->CRH &=  ~( 3 << ( ( PIN - 8 ) * 4) ); // Config Bit Mode(In Register CRH) == 0
					GPIOB->CRH &= ~( 3  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode == 0
					GPIOB->CRH |= ( Config_IO << ( (PIN - 8) * 4)  ); // Config Bit Mode(In Register CRH) 
					GPIOB->CRH |= ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode 
					while( ( ( GPIOB->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << ( ( PIN - 8 ) * 4) ) )  ||  ( ( GPIOB->CRH & ( 3  << ( ( ( PIN - 8 ) * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRH)             					
				}
				else{
				    while(1);
				};
				break;
				
			case 3: //PORT is C
				while( ( (Config_IO < 0) || (Config_IO > 3) ) || ( (Mode <0) || (Mode > 3) ) ); // check Config_IO And Mode Not INvalid
				if( (PIN >= 0) && (PIN <= 7) ){ // Number Pin Between 0 And 7
					GPIOC->CRL &=  ~( 3 << (PIN * 4) ); // Config Bit Mode(In Register CRL) == 0
					GPIOC->CRL &= ~( 3  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode == 0
					GPIOC->CRL |= ( Config_IO << (PIN * 4)  ); // Config Bit Mode(In Register CRL) 
					GPIOC->CRL |= ( Mode  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode 
					while( ( ( GPIOC->CRL & ( 3 << (PIN * 4) ) ) != ( Config_IO << (PIN * 4) ) )  ||  ( ( GPIOC->CRL & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( PIN * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRL)
				}
				else if( (PIN >= 8) && (PIN <= 15) ){ // Number Pin Between 8 And 15
					GPIOC->CRH &=  ~( 3 << ( ( PIN - 8 ) * 4) ); // Config Bit Mode(In Register CRH) == 0
					GPIOC->CRH &= ~( 3  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode == 0
					GPIOC->CRH |= ( Config_IO << ( (PIN - 8) * 4)  ); // Config Bit Mode(Input or Output)(In Register CRH) 
					GPIOC->CRH |= ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode 
					while( ( ( GPIOC->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << ( ( PIN - 8 ) * 4) ) )  ||  ( ( GPIOC->CRH & ( 3  << ( ( ( PIN - 8 ) * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRH)             										
				}
				else{
				    while(1);
				};
				break;
			
			case 4: //PORT is D
				while( ( (Config_IO < 0) || (Config_IO > 3) ) || ( (Mode <0) || (Mode > 3) ) ); // check Config_IO And Mode Not INvalid
				if( (PIN >= 0) && (PIN <= 7) ){ // Number Pin Between 0 And 7
					GPIOD->CRL &=  ~( 3 << (PIN * 4) ); // Config Bit Mode(In Register CRL) == 0
					GPIOD->CRL &= ~( 3  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode == 0
					GPIOD->CRL |= ( Config_IO << (PIN * 4)  ); // Config Bit Mode(In Register CRL) 
					GPIOD->CRL |= ( Mode  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode 
					while( ( ( GPIOD->CRL & ( 3 << (PIN * 4) ) ) != ( Config_IO << (PIN * 4) ) )  ||  ( ( GPIOD->CRL & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( PIN * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRL)
				}
				else if( (PIN >= 8) && (PIN <= 15) ){ // Number Pin Between 8 And 15
					GPIOD->CRH &=  ~( 3 << ( ( PIN - 8 ) * 4) ); // Config Bit Mode(In Register CRH) == 0
					GPIOD->CRH &= ~( 3  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode == 0
					GPIOD->CRH |= ( Config_IO << ( (PIN - 8) * 4)  ); // Config Bit Mode(In Register CRH) 
					GPIOD->CRH |= ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode 
					while( ( ( GPIOD->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << ( ( PIN - 8 ) * 4) ) )  ||  ( ( GPIOD->CRH & ( 3  << ( ( ( PIN - 8 ) * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRH)             										
				}
				else{
				    while(1);
				};
				break;
				
			case 5: //PORT is E
				while( ( (Config_IO < 0) || (Config_IO > 3) ) || ( (Mode <0) || (Mode > 3) ) ); // check Config_IO And Mode Not INvalid
				if( (PIN >= 0) && (PIN <= 7) ){ // Number Pin Between 0 And 7
					GPIOE->CRL &=  ~( 3 << (PIN * 4) ); // Config Bit Mode(In Register CRL) == 0
					GPIOE->CRL &= ~( 3  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode == 0
					GPIOE->CRL |= ( Config_IO << (PIN * 4)  ); // Config Bit Mode(In Register CRL) 
					GPIOE->CRL |= ( Mode  << ( ( PIN * 4) + 2 )  ); // Config Bit CNF(In Register CRL) for Config Mode 
					while( ( ( GPIOE->CRL & ( 3 << (PIN * 4) ) ) != ( Config_IO << (PIN * 4) ) )  ||  ( ( GPIOE->CRL & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( PIN * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRL)
				}
				else if( (PIN >= 8) && (PIN <= 15) ){ // Number Pin Between 8 And 15
					GPIOE->CRH &=  ~( 3 << ( ( PIN - 8 ) * 4) ); // Config Bit Mode(In Register CRH) == 0
					GPIOE->CRH &= ~( 3  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode == 0
					GPIOE->CRH |= ( Config_IO << ( (PIN - 8) * 4)  ); // Config Bit Mode(In Register CRH) 
					GPIOE->CRH |= ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ); // Config Bit CNF(In Register CRH) for Config Mode 					while( ( ( GPIOB->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << (PIN * 4) ) )  &&  ( ( GPIOB->CRH & ( 3  << ( ( PIN * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRLH)             					
					while( ( ( GPIOE->CRH & ( 3 << ( ( PIN - 8 ) * 4) ) ) != ( Config_IO << ( ( PIN - 8 ) * 4) ) )  ||  ( ( GPIOE->CRH & ( 3  << ( ( ( PIN - 8 ) * 4) + 2 ) ) ) != ( Mode  << ( ( ( PIN - 8 ) * 4) + 2 )  ) ) ); // wait set Bits Mode And CNF(In Register CRH)             					
				}
				else{
				    while(1);
				};
				break;

			default: while(1);
		}
};


/*********** Functions Set Pins ******************/
void Set_PINA(char PIN){
    GPIOA->BSRR |= 1 << PIN; // Set PIN
	while( ( (GPIOA->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
};

void Set_PINB(char PIN){
    GPIOB->BSRR |= 1 << PIN; //set PIN
	//while( ( (GPIOB->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
};

void Set_PINC(char PIN){
    GPIOC->BSRR |= 1 << PIN; //set PIN
	while( ( (GPIOC->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
};

void Set_PIND(char PIN){
    GPIOD->BSRR |= 1 << PIN; //set PIN
	while( ( (GPIOD->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
};

void Set_PINE(char PIN){
    GPIOE->BSRR |= 1 << PIN; //set PIN
	while( ( (GPIOE->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
};

void Set_PIN(char PORT,char PIN){
	if(PORT == PORTA){
		GPIOA->BSRR |= 1 << PIN; // Set PIN
		while( ( (GPIOA->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
	}
	if(PORT == PORTB){
		GPIOB->BSRR |= 1 << PIN; // Set PIN
		while( ( (GPIOB->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
	}
	if(PORT == PORTC){
		GPIOC->BSRR |= 1 << PIN; // Set PIN
		while( ( (GPIOC->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
	}
	if(PORT == PORTD){
		GPIOD->BSRR |= 1 << PIN; // Set PIN
		while( ( (GPIOD->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
	}
	if(PORT == PORTE){
		GPIOE->BSRR |= 1 << PIN; // Set PIN
		while( ( (GPIOE->ODR) & ( 1 << PIN) )  != ( 1 << PIN ) ); // wait set PIN = 1
	}
};


/************ Functions Reset PIN ************/
void Reset_PINA(char PIN){
    GPIOA->BRR |= 1 << PIN;
	while( ( ( GPIOA->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) );
};

void Reset_PINB(char PIN){
    GPIOB->BRR |= 1 << PIN;
	while( ( ( GPIOB->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) );
};

void Reset_PINC(char PIN){
    GPIOC->BRR |= 1 << PIN;
	while( ( ( GPIOC->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) );
};

void Reset_PIND(char PIN){
    GPIOD->BRR |= 1 << PIN;
	while( ( ( GPIOD->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) );
};

void Reset_PINE(char PIN){
    GPIOE->BRR |= 1 << PIN;
	while( ( (GPIOE->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) );
};

void Reset_PIN(char PORT,char PIN){
	if(PORT == PORTA){
		GPIOA->BRR |= 1 << PIN; // set pin
		while( ( (GPIOA->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) ); // wait set pin
	}
	
	else if(PORT == PORTB){
		GPIOB->BRR |= 1 << PIN; // set pin
		while( ( (GPIOB->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) ); // wait set pin
	}
	
	else if(PORT == PORTC){
		GPIOC->BRR |= 1 << PIN; // set pin
		while( ( (GPIOC->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) ); // wait set pin
	}
	
	else if(PORT == PORTD){
		GPIOD->BRR |= 1 << PIN; // set pin
		while( ( (GPIOD->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) ); // wait set pin
	}
	
	else if(PORT == PORTE){
		GPIOE->BRR |= 1 << PIN; // set pin
		while( ( (GPIOE->ODR) & ( 1 << PIN) ) == ( 1 << PIN ) ); // wait set pin
	}
	
};



