#ifndef INC_USART_H_
#define INC_USART_H_

//#define transmitter ((unsigned char)0x03)
//#define Receiver ((unsigned char)0x02)


#define USART_REG(PORT_ID, REG_ID) ((unsigned int*)(PORT_ID + REG_ID))

#define RCC_APB1ENR USART_REG (0x40023800 , 0x40)

#define USART_SR USART_REG (0x40004400 , 0x00)
#define USART_DR USART_REG (0x40004400 , 0x04)
#define USART_BRR USART_REG (0x40004400 , 0x08)
#define USART_CR1 USART_REG (0x40004400 , 0x0C)
#define USART_CR2 USART_REG (0x40004400 , 0x10)
#define USART_CR3 USART_REG (0x40004400 , 0x14)
#define USART_GTPR USART_REG (0x40004400 , 0x18)

//#define USART00_REG(PORT_ID, REG_ID) (*(unsigned int *)(PORT_ID + REG_ID))
//
//#define USART_DR USART00_REG (0x40004400 , 0x04)
//#define USART_SR USART00_REG (0x40004400 , 0x00)




//void USART_Init(unsigned char baud_rate, unsigned char oversampling, unsigned char Word_length,
//               unsigned char mode,unsigned char stop);

void display( char *data);


#endif /* INC_USART_H_ */
