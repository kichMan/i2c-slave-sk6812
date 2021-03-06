#ifndef __SK6812_H
#define __SK6812_H

/**
 * @brief Управление светодиодами SK6812RGBW
 *      Размер периода на бит подбирается тактом пустышкой (noop),
 *      поэтому если отсутствует внешний резонатор (или генератор),
 *      то правильность этого периода зависит от внешних факторов.
 *      Поэтому, желательно подобрать количество пустышек на период
 *      вручную, учитывая размер высокго и низкого периода
 *      указанного в datasheet светодиода.
 * 
 * @note Подбор периода представляет из себя количество вызовов
 *      пустышек в статичных методах, которые в протоколе данных
 *      из себя представляют значения "1" или "0":
 *      static void SK6812_high(void);
 *      static void SK6812_low(void);
 * 
 * @note Если есть возможность помимо "ручного" подбора 
 *      воспользоваться осциллографом или логическим анализатором,
 *      то лучше воспользоваться осциллографом. Так как практичным
 *      путем было определено, что логический анализатор
 *      показывает неверное временное значение периода.
 */

#define LED_PORT        GPIOC
#define LED_PIN         GPIO_PIN_6
#define LED_COUNT       8
#define LED_BITs        32 // Количество бит на один LED

typedef struct { uint8_t r, g, b, w; } TColor;

/**
 * @brief 
 */
void SK6812_init (void);

/**
 * @brief Сбросить буффер и отправить всем светодиодам
 *        значение с дефолтеным цветом (т.е. выключить их)
 */
void SK6812_reset (void);

/**
 * @brief Установить в буффере цвет для одного светодиода
 * @param i: Индекс позиции изменяемого светодиода
 * @param color: Значение цвета по типу TColor
 */
void SK6812_set_buff_one (const uint8_t i, const TColor *color);

/**
 * @brief Установить в буффере цвет для всех светодиодов
 * @param color: Значение цвета по типу TColor
 */
void SK6812_set_buff_all (const TColor *color);

/**
 * @brief Отправить буффер на все светодиоды
 */
void SK6812_send_buff (void);

/**
 * @brief Демо, если не нужно, то удалить константу
 */
#define SK6812_HAS_DEMO
#ifdef SK6812_HAS_DEMO
    void SK6812_demo(void);
#endif

#endif