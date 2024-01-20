/* 
 * File:   mcal_internal_interrupt.h
 * Author: mO
 *
 * Created on 14 ??????, 2023, 04:15 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Functions Declarations -----------------*/

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the ADC Module */
#define ADC_InterruptDisable()         (CLEAR_BIT(ADCSRA,ADIE))
/* This routine sets the interrupt enable for the ADC Module */
#define ADC_InterruptEnable()          (SET_BIT(ADCSRA,ADIE))
/* This routine clears the interrupt flag for the ADC Module */
#define ADC_InterruptFlagClear()       (SET_BIT(ADCSRA,ADIF))
#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the timer0 module overflow */
#define TIMER0_OverflowInterruptDisable()         (CLEAR_BIT(TIMSK,TOIE0))
/* This routine sets the interrupt enable for the timer0 module overflow */
#define TIMER0_OverflowInterruptEnable()          (SET_BIT(TIMSK,TOIE0))
/* This routine clears the interrupt flag for the timer0 Module overflow */
#define TIMER0_OverflowInterruptFlagClear()       (SET_BIT(TIFR,TOV0))

/* This routine clears the interrupt enable for the timer0 module compare match */
#define TIMER0_CompareMatchInterruptDisable()         (CLEAR_BIT(TIMSK,OCIE0))
/* This routine sets the interrupt enable for the timer0 module compare match */
#define TIMER0_CompareMatchInterruptEnable()          (SET_BIT(TIMSK,OCIE0))
/* This routine clears the interrupt flag for the timer0 Module compare match */
#define TIMER0_CompareMatchInterruptFlagClear()       (SET_BIT(TIFR,OCF0))
#endif

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the timer1 module overflow */
#define TIMER1_OverflowInterruptDisable()         (CLEAR_BIT(TIMSK,TOIE1))
/* This routine sets the interrupt enable for the timer1 module overflow */
#define TIMER1_OverflowInterruptEnable()          (SET_BIT(TIMSK,TOIE1))
/* This routine clears the interrupt flag for the timer1 Module overflow */
#define TIMER1_OverflowInterruptFlagClear()       (SET_BIT(TIFR,TOV1))

/* This routine clears the interrupt enable for the timer1 module compare match */
#define TIMER1_CompareMatch_A_InterruptDisable()         (CLEAR_BIT(TIMSK,OCIE1A))
/* This routine sets the interrupt enable for the timer1 module compare match */
#define TIMER1_CompareMatch_A_InterruptEnable()          (SET_BIT(TIMSK,OCIE1A))
/* This routine clears the interrupt flag for the timer1 Module compare match */
#define TIMER1_CompareMatch_A_InterruptFlagClear()       (SET_BIT(TIFR,OCF1A))

/* This routine clears the interrupt enable for the timer1 module compare match */
#define TIMER1_CompareMatch_B_InterruptDisable()         (CLEAR_BIT(TIMSK,OCIE1B))
/* This routine sets the interrupt enable for the timer1 module compare match */
#define TIMER1_CompareMatch_B_InterruptEnable()          (SET_BIT(TIMSK,OCIE1B))
/* This routine clears the interrupt flag for the timer1 Module compare match */
#define TIMER1_CompareMatch_B_InterruptFlagClear()       (SET_BIT(TIFR,OCF1B))

/* This routine clears the interrupt enable for the timer1 module input capture */
#define TIMER1_InputCaptureInterruptDisable()             (CLEAR_BIT(TIMSK,TICIE1))
/* This routine sets the interrupt enable for the timer1 module input capture */
#define TIMER1_InputCaptureInterruptEnable()              (SET_BIT(TIMSK,TICIE1))
/* This routine clears the interrupt flag for the timer1 Module input capture */
#define TIMER1_InputCaptureInterruptFlagClear()          (SET_BIT(TIFR,ICF1))
#endif

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the timer2 module overflow */
#define TIMER2_OverflowInterruptDisable()         (CLEAR_BIT(TIMSK,TOIE2))
/* This routine sets the interrupt enable for the timer2 module overflow */
#define TIMER2_OverflowInterruptEnable()          (SET_BIT(TIMSK,TOIE2))
/* This routine clears the interrupt flag for the timer2 Module overflow */
#define TIMER2_OverflowInterruptFlagClear()       (SET_BIT(TIFR,TOV2))

/* This routine clears the interrupt enable for the timer2 module compare match */
#define TIMER2_CompareMatchInterruptDisable()         (CLEAR_BIT(TIMSK,OCIE2))
/* This routine sets the interrupt enable for the timer2 module compare match */
#define TIMER2_CompareMatchInterruptEnable()          (SET_BIT(TIMSK,OCIE2))
/* This routine clears the interrupt flag for the timer2 Module compare match */
#define TIMER2_CompareMatchInterruptFlagClear()       (SET_BIT(TIFR,OCF2))
#endif

#if USART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the usart transmitter */
#define USART_DR_EmptyInterruptDisable()         (CLEAR_BIT(UCSRB,UDRIE))
/* This routine sets the interrupt enable for the usart transmitter */
#define USART_DR_EmptyInterruptEnable()           (SET_BIT(UCSRB,UDRIE))
#endif

#if USART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the usart receiver */
#define USART_RX_CompleteInterruptDisable()         (CLEAR_BIT(UCSRB,RXCIE))
/* This routine sets the interrupt enable for the usart receiver */
#define USART_RX_CompleteInterruptEnable()          (SET_BIT(UCSRB,RXCIE))
#endif

#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the spi module */
#define SPI_InterruptDisable()         (CLEAR_BIT(SPCR,SPIE))
/* This routine sets the interrupt enable for the spi module */
#define SPI_InterruptEnable()          (SET_BIT(SPCR,SPIE))
#endif

#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the I2C module */
#define I2C_InterruptDisable()         (CLEAR_BIT(TWCR,TWIE))
/* This routine sets the interrupt enable for the I2C module */
#define I2C_InterruptEnable()          (SET_BIT(TWCR,TWIE))
/* This routine clears the interrupt flag for the I2C module */
#define I2C_InterruptFlagClear()       (SET_BIT(TWCR,TWINT))
#endif
#endif	/* MCAL_INTERNAL_INTERRUPT_H */

