/* 
 * File:   usart.c
 * Author: mO
 *
 * Created on 20 ??????, 2023, 04:36 ?
 */

#include "usart.h"

static void (*USART_RxInterruptHandler)(void) = NULL;
static void (*USART_TxInterruptHandler)(void) = NULL;
    uint8 flag = 0;
static void USART_tx_select(const usart_t *_usart);
static void USART_rx_select(const usart_t *_usart);
static void USART_baudrate_select(const usart_t *_usart);

Std_ReturnType USART_Init(const usart_t *_usart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _usart){
        ret = E_NOT_OK;
    }
    else
    {
        USART_MODE(_usart->sync_Async);
        USART_SPEED_SELECT(_usart->speed);
        USART_tx_select(_usart);
        USART_rx_select(_usart);
        USART_CHR_SIZE_SELECT(_usart->data_size);
        USART_PARITY_SELECT(_usart->parity);
        USART_STOP_BIT_SELECT(_usart->stop_bit_size);
        
#if USART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    sei();
    USART_RX_CompleteInterruptEnable();
    USART_RxInterruptHandler = _usart->USART_RxInterruptHandler;
#endif
#if USART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    sei();
    USART_DR_EmptyInterruptEnable();
    USART_TxInterruptHandler = _usart->USART_TxInterruptHandler;
#endif
    USART_baudrate_select(_usart);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType USART_DeInit(const usart_t *_usart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _usart){
        ret = E_NOT_OK;
    }
    else
    {
        USART_DISABLE_TRANSMITTION();
        USART_DISABLE_RECEIVER();
#if USART_RX_INTERRUPT_FEATURE_ENABLE
    USART_RX_CompleteInterruptDisable();
#endif
#if USART_UDRE_INTERRUPT_FEATURE_ENABLE
    USART_DR_EmptyInterruptDisable();
#endif
    ret = E_OK;
    }
    return ret;
}

uint8 USART_ReadByteBlocking(void){
    while(!USART_RECEIVE_COMPLETE());
    return UDR;
}
uint8 USART_ReadByteNonBlocking(void){
    return UDR;
}
void USART_RX_Restart(void){
    USART_DISABLE_RECEIVER();
    USART_ENABLE_RECEIVER();
}

void USART_WriteByteBlocking(uint8 _data){
    while(!USART_DATA_REG_EMPTY());
    UDR = _data;
}
void USART_WriteStringBlocking(uint8 *_data, uint16 str_len){
    uint16 char_counter = ZERO_INIT;
    for(char_counter=ZERO_INIT; char_counter < str_len; char_counter++){
        USART_WriteByteBlocking(_data[char_counter]);
    }
}
void USART_WriteByteNonBlocking(uint8 _data){
    UDR = _data;
}
void USART_WriteStringNonBlocking(uint8 *_data, uint16 str_len){
    uint16 char_counter = ZERO_INIT;
    for(char_counter=ZERO_INIT; char_counter < str_len; char_counter++){
        USART_WriteByteNonBlocking(_data[char_counter]);
    }
}

static void USART_tx_select(const usart_t *_usart){
    if(_usart->tx_mode == USART_TRANSMIT_ENABLE){
        USART_ENABLE_TRANSMITTION();
    }
    else if(_usart->tx_mode == USART_TRANSMIT_DISABLE){
        USART_DISABLE_TRANSMITTION();
    }
}
static void USART_rx_select(const usart_t *_usart){
    if(_usart->rx_mode == USART_RECEIVE_ENABLE){
        USART_ENABLE_RECEIVER();
    }
    else if(_usart->rx_mode == USART_RECEIVE_DISABLE){
        USART_DISABLE_RECEIVER();
    }
}

static void USART_baudrate_select(const usart_t *_usart){
    uint16 baud = 0;
    if(_usart->speed == USART_NORMAL_SPEED){
        baud = (uint16)((F_CPU / (16*_usart->baud_rate))-1);
        UBRRH = (uint8)(baud >> 8);
        UBRRL = (uint8)baud;
    }
    else if(_usart->speed == USART_DOUBLE_SPEED){
        baud = (uint16)((F_CPU / (8*_usart->baud_rate))-1);
        UBRRH = (uint8)(baud >> 8);
        UBRRL = (uint8)baud;
    }
}

ISR(USART_RXC_vect){
    if(USART_RxInterruptHandler){USART_RxInterruptHandler();}
}

ISR(USART_UDRE_vect){
    if(USART_TxInterruptHandler){USART_TxInterruptHandler();}
    
}