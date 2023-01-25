#ifndef __LED_H
#define __LED_H

#include "sys.h"

#include "stm32g0xx_hal_rcc.h"
#include "stm32g0xx_hal_gpio.h"

#define LED_GPIO_PORT				GPIOB
#define LED_GPIO_PIN				GPIO_PIN_0

typedef enum{
	LED_ON = 0,
	LED_OFF = 1
}LED_State_Enum_t;
#define LED			PBout(0)

void LED_Init(void);

void LED_Toggle(void);

#endif /* __LED_H */
