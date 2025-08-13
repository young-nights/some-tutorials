#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "bsp_sys.h"

/*******************************************/
/*              �ж����ȼ�����             */
/*-----------------------------------------*/
/*	USART1  -> �����ȼ���3  �����ȼ���0
 *  USART3  -> �����ȼ���4  �����ȼ���0
 *  TIM2    -> �����ȼ���2  �����ȼ���0
 */


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main ( void )
{	
		/*�����ж����ȼ�����Ϊ��4��4λ��ռ���ȼ�*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    /* ϵͳʱ�ӳ�ʼ�� */
    SystemInit(); 
    /* PB3/PB4��Ϊ��ͨIOʹ�ã���Ҫ���и��ò���������Ҫ��������ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    /*  PB3/PB4����JTAG�ĵ������ţ�Ϊ��������GPIO����Ҫ�ر�JTAG���� */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    CPU_TS_TmrInit();  // ��ʼ��ʱ���������

    LED_GPIO_Config();

    while (1)
    {

      macLED_4G_ON();
      Delay_ms(100);
      macLED_4G_OFF();
      Delay_ms(100);
    }
}


/*********************************************END OF FILE**********************/





















