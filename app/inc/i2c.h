#ifndef __I2C_H
#define __I2C_H

/**
 * @brief Дефолтный 7ми битный адрес этого устройства на шине I2C
 */
#ifndef I2C_ADDRESS_7Bits
    #define I2C_ADDRESS_7Bits 0b00110110
#endif

/**
 * @brief Дефолтный 10и битный адрес этого устройства на шине I2C
 *        Если используется 10и битный адрес, то расскоментировать
 *        определение этой константы и установить нужный адрес
 */
// #define I2C_ADDRESS_10Bits 0x3F0

/**
 * @brief Размер буффера передаваемых данных
 */
#ifndef I2C_BUFFER_SIZE
    #define I2C_BUFFER_SIZE     5
#endif

/**********************************************
 * Аддрес в зависимости от разрядности
 */
#ifdef I2C_ADDRESS_10Bits
    #define I2C_ADDRESS I2C_ADDRESS_10Bits
#else
    #define I2C_ADDRESS I2C_ADDRESS_7Bits // 7bit
#endif
/**********************************************/

typedef volatile uint8_t I2C_Buffer_TypeDef;
typedef volatile bool I2C_Flag_TypeDef;

/**
 * @brief Callback определяемый в пользовательском коде
 *        и вызываемый при завершении получения данных
 *        от мастера, завершением считается достижение
 *        объема данных размеру установленного буффера
 *        и определенному в константе I2C_BUFFER_SIZE
 * @attention
 *        Важно понимать, что этот метод выполняется
 *        внутри прерывания.
 * 
 * @note Не очень хорошее его определение
 */
extern void I2C_ON_READ (void);

/**
 * @brief Общая инициализация
 */
void I2C_setup (void);

/**
 * @brief Инициализация для вектора прерывания
 */
void I2C_IRQ (void);

/**
 * @brief Размер используемого буффера
 *        на оба буффера один размер
 * @retval
 */
uint8_t I2C_get_buffer_size (void);

/**
 * @brief Возвращает текущее статус при получении
 * @retval *I2C_Flag_TypeDef
 */
I2C_Flag_TypeDef    *I2C_isRecived ();

/**
 * @brief Возвращает буффер полученых данных
 * @retval *I2C_Buffer_TypeDef
 */
I2C_Buffer_TypeDef  *I2C_getRxBuffer();

/**
 * @brief Возвращает буффер отправляемых данных
 * @retval ссылка на буффер
 */
I2C_Buffer_TypeDef  *I2C_getTxBuffer();

#endif