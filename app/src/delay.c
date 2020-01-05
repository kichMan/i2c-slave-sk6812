#include "../stm8s_conf.h"

volatile static uint16_t count = 0;

void delay_change () {
    if (count)
    {
        count--;
    }
}

void delay_us(uint16_t us)
{
    TIM4_Cmd(DISABLE);       // stop
    TIM4_TimeBaseInit(TIM4_PRESCALER_4, TIM4_US_PERIOD);
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    count = us>>1;
    TIM4_Cmd(ENABLE);       // let's go
    while(count);
}


void delay_ms(uint16_t ms)
{
    TIM4_Cmd(DISABLE);       // stop
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    count = ms;
    TIM4_Cmd(ENABLE);       // let's go
    while(count);
}

void delay_us_hard(uint16_t value)
{
	register uint16_t loops =  (DELAY_CONST * value);
	while(loops)
	{
		__asm__("nop");
		loops--;
	};
}


void delay_ms_hard(uint16_t value)
{
    while (value)
    {
        delay_us_hard(1000);
        value--;
    }
}

void delay_init ()
{
    TIM4_DeInit();
}

////////////////////////////////////////
void TIM4_DeInit()
{
  TIM4->CR1 = TIM4_CR1_RESET_VALUE;
  TIM4->IER = TIM4_IER_RESET_VALUE;
  TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
  TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
  TIM4->ARR = TIM4_ARR_RESET_VALUE;
  TIM4->SR1 = TIM4_SR1_RESET_VALUE;
}

void TIM4_Cmd(FunctionalState NewState)
{ 
  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM4->CR1 |= TIM4_CR1_CEN;
  }
  else
  {
    TIM4->CR1 &= (uint8_t)(~TIM4_CR1_CEN);
  }
}

void TIM4_TimeBaseInit(TIM4_Prescaler_TypeDef TIM4_Prescaler, uint8_t TIM4_Period)
{
  /* Set the Prescaler value */
  TIM4->PSCR = (uint8_t)(TIM4_Prescaler);
  /* Set the Autoreload value */
  TIM4->ARR = (uint8_t)(TIM4_Period);
}

void TIM4_ClearFlag(TIM4_FLAG_TypeDef TIM4_FLAG)
{
  /* Clear the flags (rc_w0) clear this bit by writing 0. Writing �1� has no effect*/
  TIM4->SR1 = (uint8_t)(~TIM4_FLAG);
}

void TIM4_ITConfig(TIM4_IT_TypeDef TIM4_IT, FunctionalState NewState)
{ 
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIM4->IER |= (uint8_t)TIM4_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIM4->IER &= (uint8_t)(~TIM4_IT);
  }
}

void delay_IRQ(void) {
    TIM4->SR1 = (uint8_t)(~TIM4_IT_UPDATE);
}