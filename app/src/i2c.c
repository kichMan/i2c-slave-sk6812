#include "../stm8s_conf.h"

static I2C_Flag_TypeDef __flag;

static I2C_Buffer_TypeDef rx_buffer[I2C_BUFFER_SIZE];
static I2C_Buffer_TypeDef tx_buffer[I2C_BUFFER_SIZE]; // Должен бьть указателем


extern void I2C_ON_READ (void);

static volatile uint8_t __counter;

/**
 * @brief Вызывается в начале транзакции с ведомым
 *        устройством (распознается подчиненный адрес)
 */
static void I2C_transaction_begin(void)
{
    __counter = 0;
}

/**
 * @brief Вызывается при завершении транзакция с ведомым
 *        устройством (обнаружен стоп или Nack).
 */
static void I2C_transaction_end(void)
{
    // not used
}

/**
 * @brief Вызывается когда принимается байт
 */
static void I2C_byte_received(uint8_t rx_data)
{
    rx_buffer[__counter] = rx_data;
    __counter += 1;

    if(__counter == 1){
        __flag = FALSE;
    }
    if(__counter == I2C_BUFFER_SIZE){
        __flag = TRUE;
        //буффер полон
        I2C_ON_READ();
    }
}

/**
 * @brief Вызывается при отправке байта
 */
static uint8_t I2C_byte_write(void)
{
    uint8_t i = __counter;
    __counter += 1;
    return tx_buffer[i];
}

static void I2C_init_data ()
{
    register uint8_t i = 0;
    __counter = 0;
    __flag = FALSE;
    for(i = 0; i< I2C_BUFFER_SIZE; i++)
    {
        rx_buffer[i] = 0x00;
    }
}

I2C_Flag_TypeDef *I2C_isRecived ()
{
    return &__flag;
}

I2C_Buffer_TypeDef *I2C_getRxBuffer()
{
    return (I2C_Buffer_TypeDef *) &rx_buffer;
}

I2C_Buffer_TypeDef *I2C_getTxBuffer()
{
    return (I2C_Buffer_TypeDef *) &tx_buffer;
}


void I2C_setup (void)
{
    uint8_t input_clock = CLK_GetClockFreq()/1000000; // 16
    I2C->CR1 |= 0x01;				  // Enable I2C peripheral
    I2C->CR2 = 0x04;					// Enable I2C acknowledgement
    I2C->FREQR = input_clock; 					// Set I2C Freq value (16MHz)
    #ifdef I2C_ADDRESS_10Bits
    I2C->OARL = (I2C_ADDRESS & 0xFF) ;							// set slave address LSB 
    I2C->OARH = 0xC0 | ((I2C_ADDRESS & 0x300) >> 7);	// Set 10bits address mode and address MSB
    #else
    I2C->OARL = (I2C_ADDRESS << 1) ;  // set slave address to 0x51 (put 0xA2 for the register dues to7bit address) 
    I2C->OARH = 0x40;
    #endif
    I2C->ITR = 0x07;                 // all I2C interrupt enable
    
    //////////////
    I2C_init_data();
}

void I2C_IRQ (void)
{
    static uint8_t SR1;
    static uint8_t SR2;
    static uint8_t SR3;

    // save the I2C registers configuration
    SR1 = I2C->SR1;
    SR2 = I2C->SR2;
    SR3 = I2C->SR3;

    /* Communication error? */
    if (SR2 & (I2C_SR2_WUFH | I2C_SR2_OVR |I2C_SR2_ARLO |I2C_SR2_BERR))
    {
        I2C->CR2|= I2C_CR2_STOP;        // stop communication - release the lines
        I2C->SR2= 0;                    // clear all error flags
        return;
    }
    /* More bytes received ? */
    if ((SR1 & (I2C_SR1_RXNE | I2C_SR1_BTF)) == (I2C_SR1_RXNE | I2C_SR1_BTF))
    {
        I2C_byte_received(I2C->DR);
        return;
    }
    /* Byte received ? */
    if (SR1 & I2C_SR1_RXNE)
    {
        I2C_byte_received(I2C->DR);
        return;
    }
    /* NAK? (=end of slave transmit comm) */
    if (SR2 & I2C_SR2_AF)
    {	
        I2C->SR2 &= ~I2C_SR2_AF;	  // clear AF
        I2C_transaction_end();
        return;
    }
    /* Stop bit from Master  (= end of slave receive comm) */
    if (SR1 & I2C_SR1_STOPF) 
    {
        I2C->CR2 |= I2C_CR2_ACK;	  // CR2 write to clear STOPF
        I2C_transaction_end();
        return;
    }
    /* Slave address matched (= Start Comm) */
    if (SR1 & I2C_SR1_ADDR)
    {
        __flag = FALSE;
        I2C_transaction_begin();
        return;
    }
    /* More bytes to transmit ? */
    if ((SR1 & (I2C_SR1_TXE | I2C_SR1_BTF)) == (I2C_SR1_TXE | I2C_SR1_BTF))
    {
        I2C->DR = I2C_byte_write();
        return;
    }
    /* Byte to transmit ? */
    if (SR1 & I2C_SR1_TXE)
    {
        I2C->DR = I2C_byte_write();
        return;
    }	
    GPIOD->ODR^=1;
}

uint8_t I2C_get_buffer_size (void)
{
    return (uint8_t) I2C_BUFFER_SIZE;
}