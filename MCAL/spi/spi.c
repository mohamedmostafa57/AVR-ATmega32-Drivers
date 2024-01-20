/* 
 * File:   spi.c
 * Author: mO
 *
 * Created on 19 ??????, 2023, 04:33 ?
 */

#include "spi.h"


    static void (*SPI_InterruptHandler)(void) = NULL;

    
static void SPI_Msster_Mode_GPIO_PIN_Configurations(void);
static void SPI_Slave_Mode_GPIO_PIN_Configurations(void);
static void SPI_SELECT_CLOCK_RATE(const spi_t *Config);

Std_ReturnType SPI_Master_Init(const spi_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE_MODULE();
        /* set spi mode */
        SPI_MODE(SPI_MASTER_MODE);
        /* set spi master clock pins */
        SPI_Msster_Mode_GPIO_PIN_Configurations();
        /* set spi data order */
        SPI_DATA_ORDER(Config->data_order);
        /* set spi clock polarity */
        SPI_CLOCK_POLARITY(Config->clk_polarity);
        /* set spi clock phase */
        SPI_CLOCK_PHASE(Config->clk_phase);
        /* set spi clock rate */
        SPI_SELECT_CLOCK_RATE(Config);
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptEnable();
        sei();
        SPI_InterruptHandler = Config->SPI_InterruptHandler;
#endif
        SPI_ENABLE_MODULE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_Slave_Init(const spi_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE_MODULE();
        /* set spi mode */
        SPI_MODE(SPI_SLAVE_MODE);
        /* set spi master clock pins */
        SPI_Slave_Mode_GPIO_PIN_Configurations();
        /* set spi data order */
        SPI_DATA_ORDER(Config->data_order);
        /* set spi clock polarity */
        SPI_CLOCK_POLARITY(Config->clk_polarity);
        /* set spi clock phase */
        SPI_CLOCK_PHASE(Config->clk_phase);
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptEnable();
        sei();
        SPI_InterruptHandler = Config->SPI_InterruptHandler;
#endif
        SPI_ENABLE_MODULE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType SPI_DeInit(const spi_t *Config){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SPI_DISABLE_MODULE();
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        SPI_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}
void SPI_Send_Byte(const uint8 _data){
    SPDR = _data;
    while(!SPI_IS_TRANSFER_COMPETE());
}
uint8 SPI_Read_Byte(){
    while(!SPI_IS_TRANSFER_COMPETE());
    return SPDR;
}
void SPI_Send_Byte_NonBlocking( const uint8 _data){
    SPDR = _data;
}
uint8 SPI_Read_Byte_NonBlocking(){
    return SPDR;
}

static void SPI_Msster_Mode_GPIO_PIN_Configurations(void){
    pin_config_t SPI_MOSI = {.port = PORTB_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_MISO = {.port = PORTB_INDEX, .pin = GPIO_PIN6, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTB_INDEX, .pin = GPIO_PIN7, .direction = GPIO_DIRECTION_OUTPUT};
    
    gpio_pin_direction_intialize(&SPI_MOSI); 
    gpio_pin_direction_intialize(&SPI_MISO);
    gpio_pin_direction_intialize(&SPI_CLK);
}
static void SPI_Slave_Mode_GPIO_PIN_Configurations(void){
    pin_config_t SPI_MOSI = {.port = PORTB_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_MISO = {.port = PORTB_INDEX, .pin = GPIO_PIN6, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_CLK = {.port = PORTB_INDEX, .pin = GPIO_PIN7, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_SS = {.port = PORTB_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRECTION_INPUT};
    
    gpio_pin_direction_intialize(&SPI_MOSI); 
    gpio_pin_direction_intialize(&SPI_MISO);
    gpio_pin_direction_intialize(&SPI_CLK); 
    gpio_pin_direction_intialize(&SPI_SS);
}

static void SPI_SELECT_CLOCK_RATE(const spi_t *Config){
    switch(Config->clk_rate){
        case SPI_CLK_RATE_DIV_4:
            CLEAR_BIT(SPCR,SPR0);
            CLEAR_BIT(SPCR,SPR1);
            break;
        case SPI_CLK_RATE_DIV_16:
            SET_BIT(SPCR,SPR0);
            CLEAR_BIT(SPCR,SPR1);
            break;
        case SPI_CLK_RATE_DIV_64:
            CLEAR_BIT(SPCR,SPR0);
            SET_BIT(SPCR,SPR1);
            break;
        case SPI_CLK_RATE_DIV_128:
            SET_BIT(SPCR,SPR0);
            SET_BIT(SPCR,SPR1);
            break;     
    }
    if(Config->speedX2 == SPI_DISABLE_DOUBLE_SPEED){
        CLEAR_BIT(SPSR,SPI2X);
    }
    else if(Config->speedX2 == SPI_ENABLE_DOUBLE_SPEED){
        SET_BIT(SPSR,SPI2X);
    }
}

ISR(SPI_STC_vect){
    if(SPI_InterruptHandler){SPI_InterruptHandler();}
}