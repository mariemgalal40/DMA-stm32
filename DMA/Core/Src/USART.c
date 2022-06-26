#include "USART.h"

//
//
//void USART_Init(unsigned char baud_rate, unsigned char oversampling, unsigned char Word_length,
//               unsigned char mode,unsigned char stop){
//	*RCC_APB1ENR |= (0x01 << 17);  //enable clock of the USART2
//	*USART_CR1 |= 0x01<<13 ; //enable USART
//	*USART_BRR = baud_rate ;
//	*USART_CR1 |= 0x01<<mode ;
//	switch (oversampling) {
//			case 16:
//				*USART_CR1 &= ~(0x01<<15);
//				break;
//			case 8:
//				*USART_CR1 |= (0x01<<15);
//				break;
//			default:
//				break;
//		}
//	switch (Word_length) {
//				case 9:
//					*USART_CR1 |= (0x01<<12);
//					break;
//				case 8:
//					*USART_CR1 &= ~(0x01<<12);
//					break;
//				default:
//					break;
//			}
//
//	switch (stop) {
//						case 1 :
//							*USART_CR2 &= ~(0x03<<12);
//							break;
//						case 2:
//							*USART_CR1 |= 0x02<<2 ;
//							break;
//						default:
//							break;
//					}
//}


void display( char *data)
{
   unsigned	char i;
   for (i=0; data[i] != '\0';i++){
            *USART_DR = data[i];
            while (((*USART_SR>>6)&1)==0){

            }

}
}

