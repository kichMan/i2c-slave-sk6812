#include <stdint.h>

#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

#ifndef _SDCC_
    #define _SDCC_
#endif

#ifndef STM8S003
    #define STM8S003
#endif

#include "stm8s.h"

// #include "stm8s_adc1.h"
// #include "stm8s_adc2.h"
// #include "stm8s_awu.h"
// #include "stm8s_beep.h"
// #include "stm8s_can.h"
#include "stm8s_clk.h"
// #include "stm8s_exti.h"
// #include "stm8s_flash.h"
#include "stm8s_gpio.h"
// #include "stm8s_i2c.h"
// #include "stm8s_itc.h"
// #include "stm8s_iwdg.h"
// #include "stm8s_rst.h"
// #include "stm8s_spi.h"
// #include "stm8s_tim1.h"
// #include "stm8s_tim2.h"
// #include "stm8s_tim3.h"
// #include "stm8s_tim4.h"
// #include "stm8s_tim5.h"
// #include "stm8s_tim6.h"
// #include "stm8s_uart1.h"
// #include "stm8s_uart2.h"
// #include "stm8s_uart3.h"
// #include "stm8s_uart4.h"
// #include "stm8s_wwdg.h"


// Customs
#include "./inc/clock.h"
#include "./inc/delay.h"
#include "./inc/i2c.h"
#include "./inc/SK6812.h"

#endif /* __STM8S_CONF_H */