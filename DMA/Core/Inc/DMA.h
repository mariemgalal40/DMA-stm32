#ifndef CORE_INC_DMA_H_
#define CORE_INC_DMA_H_


#define byte ((unsigned int)0x00)
#define half_word ((unsigned int)0x01)
#define word ((unsigned int)0x02)
#define fifo ((unsigned int)0x01)
#define direct_mode ((unsigned int)0x00)

#define Peripheral_to_memory ((unsigned int)0x00)
#define Memory_to_peripheral ((unsigned int)0x01)
#define Memory_to_memory ((unsigned int)0x02)

#define single_transfer ((unsigned int)0x00)
#define BEATS4 ((unsigned int)0x01)
#define BEATS8 ((unsigned int)0x02)
#define BEATS16 ((unsigned int)0x03)



#define DMA_REG(PORT_ID, REG_ID) ((unsigned int *)(PORT_ID + REG_ID))

#define DMA2_LISR DMA_REG (0x40026400 , 0x0000)
#define DMA2_LIFCR DMA_REG (0x40026400 , 0x0080)
#define DMA2_S0CR DMA_REG (0x40026400 , 0x0010)
#define DMA2_S0NDTR DMA_REG (0x40026400 , 0x0014)
#define DMA2_S0PAR DMA_REG (0x40026400 , 0x0018)
#define DMA2_S0M0AR DMA_REG (0x40026400 , 0x001C)
#define DMA2_S0FCR DMA_REG (0x40026400 , 0x0024)

#define DMA1_LISR DMA_REG (0x40026000 , 0x0000)
#define DMA1_LIFCR DMA_REG (0x40026000 , 0x0080)
#define DMA1_S0CR DMA_REG (0x40026000 , 0x0010)
#define DMA1_S0NDTR DMA_REG (0x40026000 , 0x0014)
#define DMA1_S0PAR DMA_REG (0x40026000 , 0x0018)
#define DMA1_S0M0AR DMA_REG (0x40026000 , 0x001C)
#define DMA1_S0FCR DMA_REG (0x40026000 , 0x0024)



void DMA_Init(unsigned char id);
void DMA_parameters(unsigned char id,unsigned int* Source_address,unsigned int *destination_address,
		unsigned char transfers_no,unsigned char transferitem_size,unsigned char transfer_mode,
		unsigned char transfer_type,unsigned char transfer_dir);

void start_transfer (unsigned char id);
int transfer_state (unsigned char id);

#endif /* CORE_INC_DMA_H_ */
