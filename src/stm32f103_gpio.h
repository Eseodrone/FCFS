/*
 *
 */


#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f1xx_hal.h"
#include "stm32f1xx_nucleo.h"


void GPIO_Init();
void BSP_GPIO_PinCfg(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed, uint32_t GPIO_Alternate);




#endif /* GPIO_H_ */
