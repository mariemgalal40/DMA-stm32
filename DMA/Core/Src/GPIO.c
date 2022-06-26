#include "GPIO.h"

unsigned int *lookup[2][10]={{GPIOA_MODER,GPIOA_OTYPER,GPIOA_OSPEEDR,GPIOA_PUPDR,GPIOA_IDR,GPIOA_ODR,GPIOA_BSRR,GPIOA_LCKR,GPIOA_AFRL,GPIOA_AFRH},
		{GPIOB_MODER,GPIOB_OTYPER,GPIOB_OSPEEDR,GPIOB_PUPDR,GPIOB_IDR,GPIOB_ODR,GPIOB_BSRR,GPIOB_LCKR,GPIOB_AFRL,GPIOB_AFRH}};



void GPIO_EnableClock(unsigned char PORT_ID) {

      *RCC_AHB1ENR |= (0x01 << PORT_ID);

}



void GPIO_Init(unsigned char PORT_ID, unsigned char PinNum, unsigned char PinMode,
               unsigned char DefaultState) {

      // Configure moder register for pin direction
	*lookup[PORT_ID][0] &= ~(0x03 << 2 * PinNum);
	*lookup[PORT_ID][0] |= PinMode << 2 * PinNum;


	*lookup[PORT_ID][1] &= ~(1 << PinNum);
	*lookup[PORT_ID][1] |= ((DefaultState & _OUTTYPE_MASK) >> _OUTTYPE_SHIFT) << PinNum;

	*lookup[PORT_ID][3] &= ~(0x03 << 2 * PinNum);
	*lookup[PORT_ID][3] |= ((DefaultState & _PUPD_MASK) >> _PUPD_SHIFT) << (2 * PinNum);


}

unsigned char GPIO_WritePin(unsigned char PORT_ID, unsigned char PinNum,
                            unsigned char Data) {
  unsigned char result;
      if (((*lookup[PORT_ID][0] & (0x03 << 2 * PinNum)) >> (2 * PinNum)) == 1) {
        if (Data) {
        	*lookup[PORT_ID][5] |= (1 << PinNum);
        } else {
        	*lookup[PORT_ID][5] &= ~(1 << PinNum);
        }
        result = OK;
      } else {
        result = NOK;
      }


  return result;
}

unsigned char GPIO_ReadPin(unsigned char PORT_ID, unsigned char PinNum) {
  unsigned char data = 0;

      data = (*lookup[PORT_ID][4] & (1 << PinNum)) >> PinNum;

      data = (*lookup[PORT_ID][4] & (1 << PinNum)) >> PinNum;


  return data;
}
