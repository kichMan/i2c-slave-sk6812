/**
 * @note Нет проверки, в случае, если происходит передача по I2C
 * 		 в момент передачи значений в LED, I2C не сможет
 * 		 достучаться пока из-за отключенных прерываний.
 * @note Нет обнуления массива, когда при передачи буффер
 * 		 заполняется не полностью
 * 
 * @note Текущий вес 		"Bytes written: 2888"
 */ 

#include "stm8s_conf.h"

INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
	I2C_IRQ();
}

INTERRUPT_HANDLER(IRQ_Handler_TIM4, 23)
{
	delay_change();
	delay_IRQ();
}

static void main_set_leds ()
{
	disableInterrupts();
	SK6812_send_buff ();
	enableInterrupts();	
}

/**
 * @brief Если нужно убрать демо, то этот метод не нужен  
 */
static void main_demo_leds ()
{
	disableInterrupts();
	SK6812_demo();
	enableInterrupts();	
}

/**
 * @brief Периодичная отправка последнего состояния
 */
void main_statement_repeater ()
{
	delay_ms(300);
	main_set_leds();
}

/**
 * @brief Callback при полученных данных
 * @note Нулевой индекс зарезервирован для комманд
 * @attention Выполняется внутри прерывания
 */
void I2C_ON_READ ()
{
	I2C_Buffer_TypeDef * _buffer = I2C_getRxBuffer();
	TColor color;
	color.r = _buffer[1];
	color.g = _buffer[2];
	color.b = _buffer[3];
	color.w = _buffer[4];
	SK6812_set_buff_all(&color);
	main_set_leds();
}

void main(void)
{
	clock_setup();
	I2C_setup();
	SK6812_init();
	main_demo_leds();
	delay_init();
	enableInterrupts();

	while (1){
		main_statement_repeater();
	};
}