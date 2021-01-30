/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f103_gpio.h"
#include "stm32f1xx.h"
#include "stm32f1xx_nucleo.h"

int main(void)
{
	HAL_Init();
	GPIO_Init();

	while(1){
		if(HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN) == GPIO_PIN_RESET){
			HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
			wait(0.5);
		}
	}
}
