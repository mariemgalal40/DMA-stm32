#include "DMA.h"
#include "GPIO.h"
#include "EXIT.h"

unsigned int *DMA_REG[2][7]={{DMA2_LISR,DMA2_LIFCR,DMA2_S0CR,DMA2_S0NDTR,DMA2_S0PAR,DMA2_S0M0AR,DMA2_S0FCR},
		{DMA1_LISR,DMA1_LIFCR,DMA1_S0CR,DMA1_S0NDTR,DMA1_S0PAR,DMA1_S0M0AR,DMA1_S0FCR}};

void DMA_Init(unsigned char id){

	switch (id) {
		case 1:
			*NVIC_ISER0 = (0x01<<11) ;   //	enable the interrupt for dma1 stream0
			*RCC_AHB1ENR |= 1<<21;       //DMA1 enable clock
				break;
		case 0:
			*NVIC_ISER1 = (0x01<<24);  //	enable the interrupt for dma2 stream0
			*RCC_AHB1ENR |= 1<<22;
				break;
			default:
				break;
		}
	*DMA_REG[id][2] &= ~(0x01<<0); //disable stream 0
	while ((*DMA_REG[id][2]>>0) == 1) {} //don't do any thing untill bin 0 becomes 0

	*DMA_REG[id][2] |= 0x01<<4;  //enable transfer complete interrupt
	*DMA_REG[id][2] |=1<<9;  //Peripheral increment mode
	*DMA_REG[id][2] |=1<<10;  //Memory increment mode
}

void DMA_parameters(unsigned char id,unsigned int* Source_address, unsigned int *destination_address,
		unsigned char transfers_no,
		unsigned char transferitem_size,unsigned char transfer_mode,
		unsigned char transfer_type,unsigned char transfer_dir){
	*DMA_REG[id][4] = (unsigned int)Source_address;  //peripheral address register
	*DMA_REG[id][5] = (unsigned int)destination_address;  //memory 0 address register
	*DMA_REG[id][2] |= (0x03<<16);  //periority level -->very hogh
	*DMA_REG[id][2] &= ~(0x01<<5); //dma is the flow controller
	*DMA_REG[id][3] =  transfers_no;  //number of data

	if (transfer_dir == 0)  //m_to_m , m_to_p ,p_to_m
	{
		*DMA_REG[id][2] &= ~(transfer_dir<<6);   //p_to_m
	}
	else {
		*DMA_REG[id][2] |= (transfer_dir<<6);
	}

	if (transferitem_size == 0) //byte..half_word..word
	{
		*DMA_REG[id][2] &=~(transferitem_size<<13); //memory data size
		*DMA_REG[id][2] &=~(transferitem_size<<11); //Peripheral data size
		}
		else {
			*DMA_REG[id][2] |= (transferitem_size<<13);
			*DMA_REG[id][2] |= (transferitem_size<<11);
		}

	if (transfer_type == 0)
	{
		*DMA_REG[id][2] &= ~(transfer_type<<23); //single Memory transfer
		*DMA_REG[id][2] &= ~(transfer_type<<21);  //single Peripheral transfer
			}
	else {
		*DMA_REG[id][2] |= (transfer_type<<23); //Memory burst transfer
		*DMA_REG[id][2] |= (transfer_type<<21);  //Peripheral burst transfer
				}

	switch (transfer_mode) {
			case fifo:
				*DMA_REG[id][6] |= 0x01<<2; //enable fifo (disable direct mode)
				*DMA_REG[id][6] |=( 0x03<<0); //threshold(full fifo)
  	 				break;
			case direct_mode:
				*DMA_REG[id][6] &= ~(0x01<<2);
					break;
				default:
					break;
			}

}

void start_transfer (unsigned char id){

	*DMA_REG[id][1] |= (0x01<<0);   //clear all interrupts flags (fifo,direct,transfer complete ..)
	*DMA_REG[id][1] |= (0x01<<2);
	*DMA_REG[id][1] |= (0x01<<3);
	*DMA_REG[id][1] |= (0x01<<4);
	*DMA_REG[id][1] |= (0x01<<5);
	*DMA_REG[id][2] |= (0x01<<0); //enable stream0
}


int transfer_state (unsigned char id){
	unsigned int checkstate=0;
	//check if tci is 1 and tei is 0
	if ((((*DMA_REG[id][0]) >>5)&1) && (~(((*DMA_REG[id][0]) >>3)&1)))
	{
	checkstate =1;
	}
	else {
		 checkstate=0;
	}
    return checkstate;
	}



