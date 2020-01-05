MCU=stm8
DEVICE=stm8s003?3
FLASHER=stlinkv2
FLASHER_BIN=../stm8flash.bin
CFLAGS=-I ../stm8s_libs/inc -DSTM8S003 --opt-code-size -c
CC=sdcc
LIB=stm8s_gpio.rel stm8s_clk.rel clock.rel delay.rel i2c.rel SK6812.rel
OBJ=main.rel
TARGET=app

.PHONY: all build clean

%.rel:	%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

%.rel:	../stm8s_libs/src/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

%.rel:	./src/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

all: build

test: build clean

build:	$(OBJ) $(LIB)
	$(CC) -m$(MCU) -o $(TARGET).ihx $(OBJ) $(LIB)

download:
	$(FLASHER_BIN) -c $(FLASHER) -p $(DEVICE) -w $(TARGET).ihx
clean:
	@rm -v *.sym *.asm *.lst *.rel *.ihx *lk *.rst *.cdb *.map *.adb

flash: build download clean