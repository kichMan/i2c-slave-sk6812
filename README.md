# i2c-slave-sk6812

The driver for I2C-slave on STM8S with RGBW Leds SK6812 (SK6812RGBW)

## Установка stm8flash

```shell
# Собираем и переносим исполняемый файл
cd ./stm8flash && make && cp ./stm8flash ../stm8flash.bin && make clean

# Если ошибка, то возможно нужны зависимости
sudo apt install build-essential
```
