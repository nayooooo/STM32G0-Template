#include "delay.h"

static uint32_t fac_us = 0;					// us��ʱ����

/**
 * @fn void delay_us(uint32_t nus)
 * @brief ��ʱn΢�������ʱ(2^32-1)us
 *
 * @param [nus] ��ʱ΢����
 *
 */
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0, tcntold = tcnt;
	uint32_t reload = SysTick->LOAD;		// LOAD��ֵ
	ticks = nus * fac_us;					// ��Ҫ�Ľ�����
	told = SysTick->VAL;					// �ս���ʱ�ļ�����ֵ
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told) {
			// SysTick�ݼ�
			if (tnow < told) tcnt += told - tnow;
			else tcnt += reload - tnow + told;
			told = tnow;
			if (tcntold > tcnt) break;		// ����ԭ����tcnt�������������״̬
			else tcntold = tcnt;
			if (tcnt >= ticks) break;		// �ﵽ�򳬹����������������ѭ��
		}
	}
}

/**
 * @fn void delay_ms(uint32_t nms)
 * @brief ��ʱn���������ʱ(2^32-1)ms
 * @details �� 2147483 ������ (2^32-1)/(16/8(��Ƶ��))/1000 ����������
 *			��������ʱʱ������Ϊdelay_us�������ʱ����Ҫ�����Ƿ���װ��
 *
 * @param [nus] ��ʱ������
 *
 */
void delay_ms(uint32_t nms)
{
	if (nms < 2147483UL)
		delay_us(nms * 1000);
	else {
		// ʣ����ʱ���ִ��� 2147483 ms
		while (nms > 2147483UL) {
			delay_us(2147483UL * 1000);
			nms -= 2147483UL;  // ��ȥ����ʱ�Ĳ���
		}
		// ʣ����ʱ����С�� 2147483 ms
		delay_us(nms * 1000);
	}
}

void delay_Init(uint8_t SYSCLK_M)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);
	fac_us = SYSCLK_M / 8;
}
