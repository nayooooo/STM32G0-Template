#include "delay.h"

static uint32_t fac_us = 0;					// us延时倍数

/**
 * @fn void delay_us(uint32_t nus)
 * @brief 延时n微妙
 *
 * @param [nus] 延时微妙数
 *
 */
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	uint32_t reload = SysTick->LOAD;		// LOAD的值
	ticks = nus * fac_us;					// 需要的节拍数
	told = SysTick->VAL;					// 刚进入时的计数器值
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told) {
			if (tnow < told) tcnt += told - tnow;
			else tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks) break;		// 达到或超过所需节拍数则跳出循环
		}
	}
}

void delay(uint32_t nms)
{
	while(nms--) delay_us(1000);
}

void delay_Init(uint8_t SYSCLK_M)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	fac_us = SYSCLK_M;
}
