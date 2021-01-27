/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2014/04/library-08-ili9341-lcd-on-stm32f429-discovery-board/
 * @version v1.3
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   ILI9341 library for STM32F4xx with SPI communication, without LTDC hardware
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Tilen Majerle, 2015
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */
#ifndef ILI9341_H
#define ILI9341_H 130
#include "stm32f4_fonts.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_fonts.h"


/**
 * @defgroup ILI9341_Macros
 * @brief    Library defines
 * @{
 */

/**
 * @brief  This SPI pins are used on STM32F429-Discovery board
 */
#ifndef ILI9341_SPI
	#define ILI9341_SPI           	SPI1
	#define ILI9341_SPI_PORT		GPIOA
	#define ILI9341_SPI_MISO_PIN	GPIO_PIN_6
	#define ILI9341_SPI_MOSI_PIN	GPIO_PIN_7
	#define ILI9341_SPI_SCK_PIN		GPIO_PIN_5
#endif

/**
 * @brief  CS PIN for SPI, used as on STM32F429-Discovery board
 */
#ifndef ILI9341_CS_PIN
#define ILI9341_CS_PORT       GPIOB
#define ILI9341_CS_PIN        GPIO_PIN_12
#endif

/**
 * @brief  WRX PIN for data/command, used as on STM32F429-Discovery board
 */
#ifndef ILI9341_WRX_PIN
#define ILI9341_WRX_PORT      GPIOA
#define ILI9341_WRX_PIN       GPIO_PIN_8
#endif

/**
 * @brief  RESET for LCD
 */
#ifndef ILI9341_RST_PIN
#define ILI9341_RST_PORT      GPIOD
#define ILI9341_RST_PIN       GPIO_PIN_3
#endif

/* LCD settings */
#define ILI9341_WIDTH        240
#define ILI9341_HEIGHT       320
#define ILI9341_PIXEL        76800

/* Colors */
#define ILI9341_COLOR_WHITE			0xFFFF
#define ILI9341_COLOR_BLACK			0x0000
#define ILI9341_COLOR_RED			0xF800
#define ILI9341_COLOR_GREEN			0x07E0
#define ILI9341_COLOR_GREEN2		0xB723
#define ILI9341_COLOR_BLUE			0x001F
#define ILI9341_COLOR_BLUE2			0x051D
#define ILI9341_COLOR_YELLOW		0xFFE0
#define ILI9341_COLOR_ORANGE		0xFBE4
#define ILI9341_COLOR_CYAN			0x07FF
#define ILI9341_COLOR_MAGENTA		0xA254
#define ILI9341_COLOR_GRAY			0x7BEF
#define ILI9341_COLOR_BROWN			0xBBCA

/* Transparent background, only for strings and chars */
#define ILI9341_TRANSPARENT			0x80000000

/**
 * @}
 */
 
/**
 * @defgroup ILI9341_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Possible orientations for LCD
 */
typedef enum {
	ILI9341_Orientation_Portrait_1,  /*!< Portrait orientation mode 1 */
	ILI9341_Orientation_Portrait_2,  /*!< Portrait orientation mode 2 */
	ILI9341_Orientation_Landscape_1, /*!< Landscape orientation mode 1 */
	ILI9341_Orientation_Landscape_2  /*!< Landscape orientation mode 2 */
} ILI9341_Orientation_t;

/**
 * @brief  LCD options
 */
typedef struct {
	uint16_t width;
	uint16_t height;
	ILI9341_Orientation_t orientation; // 1 = portrait; 0 = landscape
} ILI931_Options_t;

/**
 * @}
 */

/**
 * @defgroup ILI9341_Functions
 * @brief    Library Functions
 * @{
 */

void ILI9341_Init(void);

void ILI9341_setConfig(void);

void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

void ILI9341_Fill(uint16_t color);

void ILI9341_Rotate(ILI9341_Orientation_t orientation);

void ILI9341_Putc(uint16_t x, uint16_t y, char c, FontDef_t* font, uint16_t foreground, uint16_t background);

void ILI9341_Puts(uint16_t x, uint16_t y, char* str, FontDef_t *font, uint16_t foreground, uint16_t background);

void ILI9341_GetStringSize(char* str, FontDef_t* font, uint16_t* width, uint16_t* height);

void ILI9341_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void ILI9341_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void ILI9341_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

void ILI9341_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void ILI9341_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void ILI9341_DisplayOn(void);

void ILI9341_DisplayOff(void);

ILI931_Options_t ILI9341_getOptions(void);

void ILI9341_printf(int16_t x, int16_t y, FontDef_t *font, int16_t foreground, int16_t background, const char *format, ...)  __attribute__((format (printf, 6, 7)));

void ILI9341_putImage(int16_t x0, int16_t y0, int16_t width, int16_t height, const int16_t *img, int32_t size);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif

