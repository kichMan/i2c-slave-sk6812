# i2c-slave-sk6812

The driver for I2C-slave on STM8S with RGBW Leds SK6812 (SK6812RGBW)

## Сборка stm8flash

*Source: [https://github.com/vdudouyt/stm8flash](https://github.com/vdudouyt/stm8flash)*

```shell
# Собираем и переносим исполняемый файл
cd ./stm8flash && make && cp ./stm8flash ../stm8flash.bin && make clean && cd ..

# Если ошибка, то возможно нужны зависимости
sudo apt install build-essential
```

## Библиотека SPL (Std. Peripheral Library for)

> *Добавлена для быстрого старта, может быть удалена в будущем*

Взята с официального сайта [www.st.com](https://www.st.com/en/embedded-software/stm8-embedded-software.html) и располагается в директории **./stm8s_libs**

## Компилятор под Linux

Для компиляции под Linux нужен компилятор [SDCC](http://sdcc.sourceforge.net/).

## Программатор

Использовался ST-Link V2 c дровами от сообщества, [источник](https://github.com/texane/stlink).

## Микроконтроллер

Проверено на:

* [STM8S003F3U6TR](https://www.st.com/en/microcontrollers-microprocessors/stm8s003f3.html) в корпусе UFQFPN-20 3x3mm;
* [STM8S103F3P6](https://www.st.com/en/microcontrollers-microprocessors/stm8s103f3.html) в корпусе TSSOP-20.
