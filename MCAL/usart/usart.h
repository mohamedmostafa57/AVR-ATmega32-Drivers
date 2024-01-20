/* 
 * File:   usart.h
 * Author: mO
 *
 * Created on 20 ??????, 2023, 04:36 ?
 */

#ifndef USART_H
#define	USART_H

/* ----------------- Includes -----------------*/

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* ----------------- Macro Declarations -----------------*/

#define USART_NORMAL_SPEED         0
#define USART_DOUBLE_SPEED         1

#define USART_ASYNCHRONOUS_MODE    0
#define USART_SYNCHRONOUS_MODE     1

#define USART_RECEIVE_DISABLE      0
#define USART_RECEIVE_ENABLE       1

#define USART_TRANSMIT_DISABLE     0
#define USART_TRANSMIT_ENABLE      1

#define USART_STOP_SIZE_1BIT       0
#define USART_STOP_SIZE_2BIT       1

#define USART_NO_PARITY            0
#define USART_EVEN_PARITY          2
#define USART_ODD_PARITY           3

#define USART_SIZE_5BIT            0
#define USART_SIZE_6BIT            1
#define USART_SIZE_7BIT            2
#define USART_SIZE_8BIT            3
/* ----------------- Macro Functions Declarations -----------------*/

#define USART_FRAME_ERROR()          (READ_BIT(UCSRA,FE))
#define USART_OVERRUN_ERROR()        (READ_BIT(UCSRA,DOR))
#define USART_PARITY_ERROR()         (READ_BIT(UCSRA,PE))

#define USART_RECEIVE_COMPLETE()     (READ_BIT(UCSRA,RXC))
#define USART_TRANSMIT_COMPLETE()    (READ_BIT(UCSRA,TXC))
#define USART_DATA_REG_EMPTY()       (READ_BIT(UCSRA,UDRE))

#define USART_ENABLE_TRANSMITTION()  (SET_BIT(UCSRB,TXEN))
#define USART_ENABLE_RECEIVER()      (SET_BIT(UCSRB,RXEN))
#define USART_DISABLE_TRANSMITTION() (CLEAR_BIT(UCSRB,TXEN))
#define USART_DISABLE_RECEIVER()     (CLEAR_BIT(UCSRB,RXEN))

#define USART_MODE(_mode)            (UCSRC |= (_mode << 6))

#define USART_SPEED_SELECT(_speed)   (UCSRA |= (_speed << 1))

#define USART_PARITY_SELECT(_PARITY) (UCSRC |= (_PARITY <<4))

#define USART_STOP_BIT_SELECT(_STOP) (UCSRC |= (_STOP <<3))

#define USART_CHR_SIZE_SELECT(_size) (UCSRC |= (_size <<1))

/* ----------------- Data Type Declarations -----------------*/

typedef struct{
    uint8 speed         :1;
    uint8 sync_Async    :1;
    uint8 tx_mode       :1;
    uint8 rx_mode       :1;
    uint8 data_size     :2;
    uint8 parity        :2;
    uint8 stop_bit_size;
    uint32 baud_rate;
#if USART_RX_INTERRUPT_FEATURE_ENABLE
    void (*USART_RxInterruptHandler)(void);
#endif
#if USART_TX_INTERRUPT_FEATURE_ENABLE
    void (*USART_TxInterruptHandler)(void);
#endif
}usart_t;

/* ----------------- Software Interfaces Declarations -----------------*/

Std_ReturnType USART_Init(const usart_t *_usart);
Std_ReturnType USART_DeInit(const usart_t *_usart);

uint8 USART_ReadByteBlocking(void);
uint8 USART_ReadByteNonBlocking(void);
void USART_RX_Restart(void);

void USART_WriteByteBlocking(uint8 _data);
void USART_WriteStringBlocking(uint8 *_data, uint16 str_len);
void USART_WriteByteNonBlocking(uint8 _data);
void USART_WriteStringNonBlocking(uint8 *_data, uint16 str_len);
#endif	/* USART_H */

