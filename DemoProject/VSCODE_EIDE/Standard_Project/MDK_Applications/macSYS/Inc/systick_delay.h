#ifndef __SYSTICK_DELAY_H
#define __SYSTICK_DELAY_H
#include "bsp_sys.h"


void delay_init(uint16_t sysclk);   /* ��ʼ���ӳٺ��� */
void delay_ms(uint16_t nms);        /* ��ʱnms */
void delay_us(uint32_t nus);        /* ��ʱnus */


#endif /*__SYSTICK_DELAY_H*/
