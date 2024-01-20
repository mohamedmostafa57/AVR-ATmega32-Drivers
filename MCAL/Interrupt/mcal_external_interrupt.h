/* 
 * File:   mcal_external_interrupt.h
 * Author: mO
 *
 * Created on 12 ??????, 2023, 06:40 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* ----------------- Includes -----------------*/
#include "mcal_interrupt_config.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
/* This routine clears the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptDisable()         (CLEAR_BIT(GICR,INT0))
/* This routine sets the interrupt enable for the external interrupt, INT0 */
#define EXT_INT0_InterruptEnable()          (SET_BIT(GICR,INT0))
/* This routine clears the interrupt flag for the external interrupt, INT0 */
#define EXT_INT0_InterruptFlagClear()       (SET_BIT(GIFR,INTF0))
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT0_RisingEdgeSet()            do { \
                                                SET_BIT(MCUCR, ISC00); \
                                                SET_BIT(MCUCR, ISC01); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT0_FallingEdgeSet()           do { \
                                                CLEAR_BIT(MCUCR, ISC00); \
                                                SET_BIT(MCUCR, ISC01); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to any logical change */
#define EXT_INT0_AnyLogicalChangeSet()      do { \
                                                SET_BIT(MCUCR, ISC00); \
                                                CLEAR_BIT(MCUCR, ISC01); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to low level */
#define EXT_INT0_LowLevelSet()              do { \
                                                CLEAR_BIT(MCUCR, ISC00); \
                                                CLEAR_BIT(MCUCR, ISC01); \
                                               } while(0)

/* This routine clears the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptDisable()         (CLEAR_BIT(GICR,INT1))
/* This routine sets the interrupt enable for the external interrupt, INT1 */
#define EXT_INT1_InterruptEnable()          (SET_BIT(GICR,INT1))
/* This routine clears the interrupt flag for the external interrupt, INT1 */
#define EXT_INT1_InterruptFlagClear()       (SET_BIT(GIFR,INTF1))
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT1_RisingEdgeSet()            do { \
                                                SET_BIT(MCUCR, ISC10); \
                                                SET_BIT(MCUCR, ISC11); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT1_FallingEdgeSet()           do { \
                                                CLEAR_BIT(MCUCR, ISC10); \
                                                SET_BIT(MCUCR, ISC11); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to any logical change */
#define EXT_INT1_AnyLogicalChangeSet()      do { \
                                                SET_BIT(MCUCR, ISC10); \
                                                CLEAR_BIT(MCUCR, ISC11); \
                                               } while(0)
/* This routine set the edge detect of the extern interrupt to low level */
#define EXT_INT1_LowLevelSet()              do { \
                                                CLEAR_BIT(MCUCR, ISC10); \
                                                CLEAR_BIT(MCUCR, ISC11); \
                                               } while(0)

/* This routine clears the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptDisable()         (CLEAR_BIT(GICR,INT2))
/* This routine sets the interrupt enable for the external interrupt, INT2 */
#define EXT_INT2_InterruptEnable()          (SET_BIT(GICR,INT2))
/* This routine clears the interrupt flag for the external interrupt, INT2 */
#define EXT_INT2_InterruptFlagClear()       (SET_BIT(GIFR,INTF2))
/* This routine set the edge detect of the extern interrupt to negative edge */
#define EXT_INT2_RisingEdgeSet()            (SET_BIT(MCUCSR,ISC2))
/* This routine set the edge detect of the extern interrupt to positive edge */
#define EXT_INT2_FallingEdgeSet()           (CLEAR_BIT(MCUCSR,ISC2))
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

/* ----------------- Data Type Declarations -----------------*/
typedef void (*InterruptHandler)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE,
    INTERRUPT_ANY_LOGICAL_CHANGE,
    INTERRUPT_LOW_LEVEL
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 =  0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;

typedef struct{
    InterruptHandler EXT_InterruptHandler;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
}interrupt_INTx_t;


/* ----------------- Software Interfaces Declarations -----------------*/

Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj);


Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);

#endif