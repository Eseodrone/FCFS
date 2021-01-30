/*
 *
 *
 */
#include "stm32f103_gpio.h"

void GPIO_Init(){

	//Activation des horloges des peropheriques GPIOx
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	//Config du bouton
	BSP_GPIO_PinCfg(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
	//Config des leds
	BSP_GPIO_PinCfg(LED2_GPIO_PORT, LED2_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, 0);
}


void BSP_GPIO_PinCfg(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin, uint32_t GPIO_Mode, uint32_t GPIO_Pull, uint32_t GPIO_Speed, uint32_t GPIO_Alternate)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//Structure contenant les arguments de la fonction GPIO_Init

	GPIO_InitStructure.Pin = GPIO_Pin;
	GPIO_InitStructure.Mode = GPIO_Mode;
	GPIO_InitStructure.Pull = GPIO_Pull;
	GPIO_InitStructure.Speed = GPIO_Speed;
	//GPIO_InitStructure.Alternate = GPIO_Alternate;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStructure);
}




