/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: mO
 *
 * Created on 12 ??????, 2023, 05:52 ?
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_FEATURE_ENABLE   1U

#define EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE      INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

//#define USART_TX_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE
#define USART_RX_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE

#define I2C_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
//#define SPI_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE

#endif	/* MCAL_INTERRUPT_GEN_CFG_H */
