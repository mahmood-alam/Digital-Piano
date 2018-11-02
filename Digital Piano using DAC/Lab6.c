// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/6/17 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"


// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init(10000);
	int input;
  // other initialization
  //EnableInterrupts();
  while(1){ 
		GPIO_PORTF_DATA_R = 0x04;
		for(int i=0; i<1000000; i++){
			i++;
		}
		input = GPIO_PORTE_DATA_R;
		input = Piano_In();
		if(input==1){
			EnableInterrupts();
			Sound_Play(11363);		//A @ 440 Hz
		} else if (input==2){
			EnableInterrupts();
			Sound_Play(9019);			//C sharp @554 hz
		}else if (input==4){
			EnableInterrupts();
			Sound_Play(7584);			//E @ 659 Hz
		} else{
			DisableInterrupts();
		}
		GPIO_PORTF_DATA_R = 0x00;
		for(int i=0; i<1000000; i++){
			i++;
		}
  }    
}


