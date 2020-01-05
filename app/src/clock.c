#include "../stm8s_conf.h"

void clock_setup(void)
{
	CLK_DeInit();

	CLK_HSECmd(DISABLE);	// внешний кварцевый резонатор
	CLK_LSICmd(DISABLE);	// внутренний низкоскоростной RC-генератор 128 КГц
	CLK_HSICmd(ENABLE);		// внутренний высокоскоростной RC-генератор 16 МГц

	while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);// Ожидаем пока будет готов RC-генератор
	
	CLK_ClockSwitchCmd(ENABLE);
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU by RC HSI
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);  // коэффициент деления
    // // CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1); // set 16 MHz for CPU
	/**
	 * error status, т.к. используется вн. RC-генератор, то комментим
	 */
	// CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, 
	// 	DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);
	
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
	// CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
	// CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}