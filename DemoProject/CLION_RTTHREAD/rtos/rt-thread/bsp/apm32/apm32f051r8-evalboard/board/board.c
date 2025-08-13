/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-11     luobeihai    first version
 */

#include "board.h"

void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);

    /* Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_9, GPIO_AF_PIN1);

    /* Connect PXx to USARRX_Rx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_PIN1);

    /* Configure USART Tx/Rx as alternate function push-pull */
    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_ConfigStruct.outtype = GPIO_OUT_TYPE_PP;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.pin  = GPIO_PIN_10;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    /* Connect PXx to USARTx_Tx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_PIN1);

    /* Connect PXx to USARRX_Rx */
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_3, GPIO_AF_PIN1);

    /* Configure USART Tx/Rx as alternate function push-pull */
    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_ConfigStruct.outtype = GPIO_OUT_TYPE_PP;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_PU;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.pin  = GPIO_PIN_3;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif
}

void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI
    GPIO_Config_T GPIO_InitStructure;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI2)
    {
        /* Enable related Clock */
        RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI2);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

        /* Config SPI PinAF */
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_15, GPIO_AF_PIN0);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_14, GPIO_AF_PIN0);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_13, GPIO_AF_PIN0);

        /* Config SPI GPIO*/
        GPIO_ConfigStructInit(&GPIO_InitStructure);
        GPIO_InitStructure.pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
        GPIO_InitStructure.mode = GPIO_MODE_AF;
        GPIO_InitStructure.outtype = GPIO_OUT_TYPE_PP;
        GPIO_InitStructure.pupd = GPIO_PUPD_NO;
        GPIO_Config(GPIOB, &GPIO_InitStructure);
    }
#endif
}

void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM
    GPIO_Config_T gpio_config;
    TMR_T *tmr_x = (TMR_T *)Instance;

    if (tmr_x == TMR3)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

        /* TMR3 channel 1 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_6, GPIO_AF_PIN0);
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF;
        gpio_config.outtype = GPIO_OUT_TYPE_PP;
        gpio_config.pupd = GPIO_PUPD_NO;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_7, GPIO_AF_PIN0);
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_8, GPIO_AF_PIN0);
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_9, GPIO_AF_PIN0);
        gpio_config.pin = GPIO_PIN_9;
        GPIO_Config(GPIOC, &gpio_config);
    }
#endif
}
