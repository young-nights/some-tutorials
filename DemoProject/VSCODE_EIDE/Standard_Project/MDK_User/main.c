#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "bsp_sys.h"

/*******************************************/
/*              中断优先级分配             */
/*-----------------------------------------*/
/*	USART1  -> 主优先级：3  子优先级：0
 *  USART3  -> 主优先级：4  子优先级：0
 *  TIM2    -> 主优先级：2  子优先级：0
 */


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main ( void )
{	
		/*设置中断优先级分组为组4：4位抢占优先级*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    /* 系统时钟初始化 */
    SystemInit(); 
    /* PB3/PB4作为普通IO使用，需要进行复用操作，所以要开启复用时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    /*  PB3/PB4用作JTAG的调试引脚，为将其用作GPIO，需要关闭JTAG功能 */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    CPU_TS_TmrInit();  // 初始化时间戳计数器

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





















