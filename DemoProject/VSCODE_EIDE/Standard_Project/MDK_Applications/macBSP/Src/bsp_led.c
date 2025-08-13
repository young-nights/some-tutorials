#include "bsp_led.h"

/**
 * @brief  ���� LED �� GPIO ����
 * @param  ��
 * @retval ��
 */
void LED_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ���� LED_4G ���� */
	RCC_APB2PeriphClockCmd(macLED_4G_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = macLED_4G_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(macLED_4G_GPIO_PORT, &GPIO_InitStructure);
}
