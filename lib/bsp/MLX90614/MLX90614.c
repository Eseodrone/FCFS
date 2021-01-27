/*
 * MLX90614.c
 *
 *  Created on: 16 janv. 2016
 *      Author: Nirgal
 */

/**
 * Ce pilote permet d'interfacer le capteur de température à distance MLX90614.
 * Ce capteur permet la mesure d'une température ambiante ET d'une température de l'objet vu à distance.
 *
 * Comment utiliser ce pilote :
 *
 * Possibilité 1 : utiliser la fonction de démo : DEMO_MLX90614_statemachine(), qui doit être appelée en boucle.
 * Possibilité 2 :
 *    1- appeler MLX90614_init() une fois
 *    2- appeler quand vous le souhaitez les fonctions readObjectTempC() et readAmbiantTempC() qui renvoient les température ambiante et observées en degré Celcius.
 *
 * Par défaut, les broches utilisées sont celles de l'I2C1 : PB7 pour SDA et PB8 pour SCL.
 * 	Ces configurations sont modifiables dans la fonction MLX90614_init();
 */

/***************************************************
  Ce pilote est inspiré d'une librairie pour le capteur MLX90614 Temp Sensor dont les commentaires sont disponibles ci dessous.
  Designed specifically to work with the MLX90614 sensors in the
  adafruit shop
  ----> https://www.adafruit.com/products/1748
  ----> https://www.adafruit.com/products/1749
  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "MLX90614.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_gpio.h"


  I2C_HandleTypeDef hi2c;
  volatile uint32_t t = 0;

  uint16_t read16(uint8_t a);


void MLX90614_init(void)
{
	hi2c.Instance = I2C1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.ClockSpeed = 100000;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c.Init.OwnAddress1 = 0;
	hi2c.Init.OwnAddress2 = 0;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_7, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_FAST, GPIO_AF4_I2C1);	//SDA
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_8, GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_FAST, GPIO_AF4_I2C1);	//SCL
	__HAL_RCC_I2C1_CLK_ENABLE();
	HAL_I2C_Init(&hi2c);
}



running_e DEMO_MLX90614_statemachine(bool_e ask_for_finish)
{
	typedef enum
	{
		INIT = 0,
		RUN,
		CLOSE
	}state_e;
	static state_e state = INIT;
	running_e ret = IN_PROGRESS;

	switch(state)
	{
		case INIT:
			MLX90614_init();
			state = RUN;
			break;
		case RUN:
			if(ask_for_finish)
				state = CLOSE;
			if(!t)
			{
				double ambiant, object;
				t = 100;
				object = readObjectTempC();
				ambiant = readAmbientTempC();
				printf("Object = %.1f°C | Ambiant %.1f°C\n",object, ambiant);
			}
			break;
		case CLOSE:
			state = INIT;
			ret = END_OK;
			break;
	}

	return ret;
}

void DEMO_MLX90614_process_1ms(void)
{
	if(t)
		t--;
}


double readObjectTempF(void)
{
  return (readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;
}


double readAmbientTempF(void)
{
  return (readTemp(MLX90614_TA) * 9 / 5) + 32;
}

double readObjectTempC(void)
{
  return readTemp(MLX90614_TOBJ1);
}


double readAmbientTempC(void)
{
  return readTemp(MLX90614_TA);
}

float readTemp(uint8_t reg)
{
  float temp;

  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

/*********************************************************************/

uint16_t read16(uint8_t a)
{
  uint8_t ret[3];

  HAL_I2C_Mem_Read(&hi2c,MLX90614_I2CADDR<<1,a,1,ret,3,1000);
 /*
  Wire.beginTransmission(_addr); // start transmission to device
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(false); // end transmission

  Wire.requestFrom(_addr, (uint8_t)3);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret |= Wire.read() << 8; // receive DATA

  uint8_t pec = Wire.read();
*/
  return ret[0] | ret[1] << 8;
}
