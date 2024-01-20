/* 
 * File:   mcal_interrupt_config.h
 * Author: mO
 *
 * Created on 12 ??????, 2023, 06:12 ?
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* ----------------- Includes -----------------*/
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/* ----------------- Macro Declarations -----------------*/
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0
#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0


/* ----------------- Macro Functions Declarations -----------------*/


/* This macro will enable global interrupts. */
#define INTERRUPT_GlobalInterruptEnable()  sei()
/* This macro will disable global interrupts. */
#define INTERRUPT_GlobalInterruptDisable() cli()


/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/


#endif	/* MCAL_INTERRUPT_CONFIG_H */

