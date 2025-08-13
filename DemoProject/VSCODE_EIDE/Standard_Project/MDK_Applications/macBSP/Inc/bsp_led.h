#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "bsp_sys.h"

/****************************** LED_4G 引脚配置参数定义***************************************/
#define macLED_4G_GPIO_APBxClock_FUN RCC_APB2PeriphClockCmd
#define macLED_4G_GPIO_CLK RCC_APB2Periph_GPIOC
#define macLED_4G_GPIO_PORT GPIOC
#define macLED_4G_GPIO_PIN GPIO_Pin_4

#define macLED_4G_OFF() GPIO_ResetBits(macLED_4G_GPIO_PORT, macLED_4G_GPIO_PIN)
#define macLED_4G_ON() GPIO_SetBits(macLED_4G_GPIO_PORT, macLED_4G_GPIO_PIN)
#define macLED_4G_TOGGLE() GPIO_ReadOutputDataBit(macLED_4G_GPIO_PORT, macLED_4G_GPIO_PIN) ? GPIO_ResetBits(macLED_4G_GPIO_PORT, macLED_4G_GPIO_PIN) : GPIO_SetBits(macLED_4G_GPIO_PORT, macLED_4G_GPIO_PIN)



void LED_GPIO_Config(void);

#endif /* __BSP_LED_H */
