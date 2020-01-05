#include "../stm8s_conf.h"

static TColor SK6812_BUFF[LED_COUNT];
static const TColor DEFAULT_COLOR = {0, 0, 0, 0};

static void SK6812_high(void)
{
	SetBit(LED_PORT->ODR, 6);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	ClrBit(LED_PORT->ODR, 6);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
}

static void SK6812_low(void)
{
	SetBit(LED_PORT->ODR, 6);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	ClrBit(LED_PORT->ODR, 6);
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
	__asm__("nop");
}

static void SK6812_send_single_command(uint8_t i)
{
    uint8_t s = LED_BITs;
    uint32_t temp = 0;
	TColor * color = &SK6812_BUFF[i];
	temp = (((uint32_t)color->g << 24) | ((uint32_t)color->r << 16) | ((uint32_t)color->b << 8) | ((uint32_t)color->w));
	while(s > 0) {
		if((temp & 0x80000000) == 0) {
			SK6812_low();
		} else {
			SK6812_high();
		}
       temp <<= 1;
	   s--;
    }
}

void SK6812_send_buff (void)
{
	register uint8_t i;
	for(i = 0; i < LED_COUNT; i++)
	{
		SK6812_send_single_command(i);
	}
}

void SK6812_init(void)
{
   	GPIO_DeInit(LED_PORT);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(LED_PORT, LED_PIN);
	SK6812_reset();
}

void SK6812_reset(void)
{
	SK6812_set_buff_all(&DEFAULT_COLOR);
	SK6812_send_buff ();
}

void SK6812_set_buff_one (const uint8_t i, const TColor *color)
{
	SK6812_BUFF[i].r = color->r;
	SK6812_BUFF[i].g = color->g;
	SK6812_BUFF[i].b = color->b;
	SK6812_BUFF[i].w = color->w;
}

void SK6812_set_buff_all (const TColor *color)
{
	register uint8_t i;
	for(i = 0; i < LED_COUNT; i++)
	{
		SK6812_set_buff_one(i, color);
	}
}

#ifdef SK6812_HAS_DEMO
void SK6812_demo(void)
{
	register uint8_t i = 0;
	register uint8_t j = 0;
	TColor demo[4];

	demo[0].r = 255;
	demo[0].g = 0;
	demo[0].b = 0;
	demo[0].w = 0;

	demo[1].r = 0;
	demo[1].g = 255;
	demo[1].b = 0;
	demo[1].w = 0;

	demo[2].r = 0;
	demo[2].g = 0;
	demo[2].b = 255;
	demo[2].w = 0;

	demo[3].r = 0;
	demo[3].g = 0;
	demo[3].b = 0;
	demo[3].w = 255;

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < LED_COUNT; j++)
		{
			SK6812_set_buff_all(&DEFAULT_COLOR);
			SK6812_set_buff_one(j, &demo[i]);
			SK6812_send_buff();
			delay_ms_hard(100);
		}
	}
	SK6812_reset();
}
#endif