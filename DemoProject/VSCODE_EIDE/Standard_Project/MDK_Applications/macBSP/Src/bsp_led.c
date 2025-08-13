#include "bsp_led.h"

/**
 * @brief  配置 LED 的 GPIO 功能
 * @param  无
 * @retval 无
 */
void LED_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 配置 LED_4G 引脚 */
	RCC_APB2PeriphClockCmd(macLED_4G_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = macLED_4G_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(macLED_4G_GPIO_PORT, &GPIO_InitStructure);
}
