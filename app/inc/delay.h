
#ifndef __DELAY_H
#define __DELAY_H

/**
 * @brief Задержки через прерывание аппаратного таймера
 */

// #include "stm8s_conf.h"

#define TIM4_PERIOD         124
#define TIM4_US_PERIOD      4

#define DELAY_CONST			(F_CPU / 16000000.0F)

void delay_change ();

void delay_us(uint16_t value);
void delay_ms(uint16_t value);
void delay_us_hard(uint16_t value);
void delay_ms_hard(uint16_t value);
void delay_init ();

/*******************************************************
 * @note Инициализация была отвязана от SPL
 *******************************************************/
typedef enum
{
  TIM4_PRESCALER_4    = ((uint8_t)0x02),
  TIM4_PRESCALER_128   = ((uint8_t)0x07)
} TIM4_Prescaler_TypeDef;

typedef enum
{
  TIM4_FLAG_UPDATE                   = ((uint8_t)0x01)
} TIM4_FLAG_TypeDef;

typedef enum
{
  TIM4_IT_UPDATE                     = ((uint8_t)0x01)
} TIM4_IT_TypeDef;

void TIM4_DeInit();
void TIM4_Cmd(FunctionalState NewState);
void TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period);
void TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG);
void TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState);
void delay_IRQ(void);
/*******************************************************/

#endif