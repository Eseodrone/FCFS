/*
 * appli.c
 *
 *  Created on: 08/2015
 *      Author: S. Poiraud
 */
#include "appli.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_gpio.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "macro_types.h"
#include "timer.h"

#define GREEN_LED	GPIOD, GPIO_PIN_12
#define ORANGE_LED	GPIOD, GPIO_PIN_13
#define RED_LED		GPIOD, GPIO_PIN_14
#define BLUE_LED	GPIOD, GPIO_PIN_15
#define BLUE_BUTTON	GPIOA, GPIO_PIN_0

static volatile uint32_t t_ms;
static volatile bool_e flag_new_value;

//////////////////////////////////////

/*
 * Initialisation de notre application, et des périphériques qu'elle utilise
 */
void APPLI_init(void)
{
	GPIO_Configure();	//Configuration des broches d'entree-sortie.

	UART_init(UART6_ID,115200);	//Initialisation de l'USART6 (PC6=Tx, PC7=Rx, 115200 bauds/sec)
	SYS_set_std_usart(UART6_ID,UART6_ID,UART6_ID);

	//Configuration des ports des LEDS en sortie
	BSP_GPIO_PinCfg(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FAST, 0);

	//Configuration du port du bouton bleu en entrée, avec interruption
	GPIO_InitTypeDef GPIO_InitStructure;					//Structure contenant les arguments de la fonction GPIO_Init
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Alternate = 0;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_EnableIRQ(EXTI0_IRQn);

	TIMER2_init_for_1ms();
}



/*
 * @brief Boucle de tâche de fond de l'application
 * @pre : doit être appelée régulièrement.
 */
void APPLI_process_main(void)
{
	if(flag_new_value)
	{
		flag_new_value = FALSE;
		printf("%lu\n",t_ms);
	}
}

//Routine d'interruption pour la ligne d'interruption externe 0.
void EXTI0_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_0) != RESET) //Normalement forcément vrai !
	{
		__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);	//On acquitte l'interruption.
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))	//Front montant
		{
			t_ms = 0;
			TIMER2_run();
		}
		else	//Front descendant
		{
			TIMER2_stop();
			flag_new_value = TRUE;
		}
	}
}

void TIMER2_user_handler_it_1ms(void)
{
	t_ms++;
}
