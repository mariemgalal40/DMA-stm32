#include "GPIO.h"
#include "USART.h"
#include "DMA.h"

unsigned int scr[100];
unsigned int dest[100];
unsigned char i,j,k,checkval,state;
void check_transmision(void);
int main(void) {

	for( i=0; i<100; i++) {
	    scr[i] = 100*(1+i);
	    dest[i] =0;
	}

	GPIO_EnableClock(0);    //	enable clock of port A
	GPIO_Init(0,0,OUTPUT,PUSH_PULL);
	DMA_Init(0);
	DMA_parameters(0,scr,dest,100,word,fifo,BEATS4,Memory_to_memory);
	start_transfer(0);
  while (1) {
  }
  return 0;
}

void DMA2_Stream0_ISR()
{
	check_transmission();
	}
void DMA1_Stream0_ISR()
{
	check_transmission();
	}
void check_transmission(void){
	for ( i=0; i<100; i++){
		if (scr[i] == dest[i])
		{
			checkval =1;
		}
		else{
			checkval =0;
			break;
		}
	}
	state = transfer_state(0);
	if ((state && checkval)==1){
		GPIO_WritePin(0,0,1);
	}
	else {
		GPIO_WritePin(0,0,0);
	}
}

