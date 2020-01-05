#ifndef __CLOCK_H
#define __CLOCK_H

/**
 * @brief Работа с тактированием микроконтроллера
 * 
 * @todo Если нужно избавиться от SPL библиотеки CLK, 
 *       о ножно опеределить метод CLK_GetClockFreq().
 *       Он используется при инициализации I2C.
 */

#define F_CPU 				16000000UL 

void clock_setup(void);

#endif