/* 
 * File:   spi.h
 * Author: mO
 *
 * Created on 19 ??????, 2023, 04:33 ?
 */

#ifndef SPI_H
#define	SPI_H

/* ----------------- Includes -----------------*/

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* ----------------- Macro Declarations -----------------*/

#define SPI_DISABLE    0
#define SPI_ENABLE     1

#define SPI_DATA_ORDER_MSB_FIRST       0
#define SPI_DATA_ORDER_LSB_FIRST       1

#define SPI_SLAVE_MODE                 0
#define SPI_MASTER_MODE                1

#define SPI_POLARITY_RISING_FALLING    0 /* clock first leading edge is rising, trailing edge is falling */
#define SPI_POLARITY_FALLING_RISING    1 /* clock first leading edge is falling, trailing edge is rising */

#define SPI_PHASE_SAMPLE_ON_LEADING    0 /* clock phase sample on leading edge and setup on trailing edge of sck */
#define SPI_PHASE_SAMPLE_ON_TRAILING   1 /* clock phase setup on leading edge and sample on trailing edge of sck */

#define SPI_CLK_RATE_DIV_4             0
#define SPI_CLK_RATE_DIV_16            1
#define SPI_CLK_RATE_DIV_64            2
#define SPI_CLK_RATE_DIV_128           3

#define SPI_DISABLE_DOUBLE_SPEED       0
#define SPI_ENABLE_DOUBLE_SPEED        1


/* ----------------- Macro Functions Declarations -----------------*/

#define SPI_DISABLE_MODULE()        (CLEAR_BIT(SPCR,SPE))
#define SPI_ENABLE_MODULE()         (SET_BIT(SPCR,SPE))

#define SPI_MODE(_mode)               (SPCR |= (_mode << 4))

#define SPI_DATA_ORDER(_order)        (SPCR |= (_order <<5))

#define SPI_CLOCK_POLARITY(_pol)        (SPCR |= (_pol <<3))

#define SPI_CLOCK_PHASE(_phase)        (SPCR |= (_phase <<2))

#define SPI_IS_TRANSFER_COMPETE()      (READ_BIT(SPSR,SPIF))
#define SPI_IS_WRITE_COLLISION()      (READ_BIT(SPSR,WCOL))
/* ----------------- Data Type Declarations -----------------*/

typedef struct{
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*SPI_InterruptHandler)(void);
#endif
    uint8 data_order    :1;
    uint8 clk_polarity  :1;
    uint8 clk_phase     :1;
    uint8 clk_rate      :2;
    uint8 speedX2       :1;
}spi_t;

/* ----------------- Software Interfaces Declarations -----------------*/

Std_ReturnType SPI_Master_Init(const spi_t *Config);
Std_ReturnType SPI_Slave_Init(const spi_t *Config);
Std_ReturnType SPI_DeInit(const spi_t *Config);
void SPI_Send_Byte(const uint8 _data);
uint8 SPI_Read_Byte();
void SPI_Send_Byte_NonBlocking(const uint8 _data);
uint8 SPI_Read_Byte_NonBlocking();

#endif	/* SPI_H */

