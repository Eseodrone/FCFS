 /**
  *
  * \file main.c
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "macro_types.h"
#include "main.h"
#include "stm32f4_uart.h"
#include "stm32f4_sys.h"
#include "appli.h"



#define TAB_SIZE	15
int demo_debug_tools(int a, int b, char c, char * str, int x, int y, int z)
{
	uint8_t tab[TAB_SIZE];
	int i;
	int ret;

	ret = (a+b+c+x+y+z)>>22;

	for(i=0; i<TAB_SIZE; i++)
		tab[i] = (uint8_t)i;

	while(ret--)
	{
		GPIOD->BSRR = GPIO_PIN_12;
		for(i=0;i<1000000;i++);
		GPIOD->BSRR = GPIO_PIN_12<<16;
		for(i=0;i<1000000;i++);
	}

	printf(str);
	tab[TAB_SIZE-1] = 0;
	printf((char*)tab);

	return ret;
}

int additionner_7(int a, int b, int c, int d, int e, int f, int g);
int additionner_n(int n, int a, int b, ...);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @func int main(void)
  * @param  None
  * @retval None
  */
int main(void)
{
	HAL_Init();
	SYS_init();			//initialisation du systeme (horloge...)
	//Fonction_montrant_l_utilisation_de_la_memoire();
	factorielle_n(3);
	factorielle_n(100);
	TD_mission_scratch();
	uint32_t s;
	s = additionner_7(1,2,3,4,5,6,7);
	s = additionner_7(10, -20, 30, 1, 2, 3, 4);
	s = additionner_7('A', 0x55, 12345678, 0xCAFEDECA, 0b011, "toto", &main);
	s = additionner_n(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	s = additionner_n(2, 10, 20);
	s = additionner_n(3, 10, 20, 30);
	s = additionner_n(100, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	asm_main();


	do_somme();

	APPLI_init();

	//Ligne appelée dans le main après les initialisations :
	//demo_debug_tools(111, 222, 0x55, "un chêne vert", 0xCAFEDECA, 0xDEADBEEF, 0xB16B00B5);


	while (1)
	{
		APPLI_process_main();
	}
}








