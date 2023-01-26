#include "main.h"

int main()
{
	uint8_t times = 0;;
	
	HAL_Init();
	
	sys_stm32_clock_init();
	delay_Init(MAIN_Fosc_M);
	uart_init(115200UL);
	
	LED_Init();
	
	while(1)
	{
		times++;
		
		LED = LED_ON;
		printf("LED State: ON\r\n");
		delay_ms(500);
		LED = LED_OFF;
		printf("LED State: OFF\r\n");
		delay_ms(500);
		
		printf("MAIN: %u\r\n", times);
	}
}
