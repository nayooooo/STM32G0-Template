#include "main.h"

int main()
{
	HAL_Init();
	SystemClock_Config();
	delay_Init(MAIN_Fosc_M);
	
	LED_Init();
	
	while(1)
	{
		LED = LED_ON;
		delay(500);
		LED = LED_OFF;
		delay(500);
	}
}
