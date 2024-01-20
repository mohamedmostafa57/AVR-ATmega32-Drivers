/*
 * File:   hal_timer.h
 * Author: mO
 *
 * Created on 12 ??????, 2023, 06:40 ?
 */

#ifndef HAL_TIMER_0_H
#define HAL_TIMER_0_H

/* ----------------- Includes -----------------*/

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* ----------------- Macro Declarations -----------------*/
/* timer0 Clock Select Bit Description */
#define TMR0_NO_CLK_SOURCE 0 /*timer/counter stopped*/
#define TMR0_NO_PRESCALING 1
#define TMR0_PRESCALER_CLK_8 2
#define TMR0_PRESCALER_CLK_64 3
#define TMR0_PRESCALER_CLK_256 4
#define TMR0_PRESCALER_CLK_1024 5
#define TMR0_EXT_CLK_SRC_T0_FALLING_EDGE 6
#define TMR0_EXT_CLK_SRC_T0_RISING_EDGE 7

/* Waveform Generation Mode Bit Description */
#define TMR0_NORMAL_MODE 0
#define TMR0_PHASE_CORRECT_PWM_MODE 1
#define TMR0_CTC_MODE 2
#define TMR0_FAST_PWM_MODE 3

/* Compare Output Mode, non-PWM Mode */
#define TMR0_NORMAL_PORT_OPERATION 0 /*OC0 pin disconnected*/
#define TMR0_TOGGLE_OC0_ON_CMP_MATCH 1
#define TMR0_CLEAR_OC0_ON_CMP_MATCH 2
#define TMR0_SET_OC0_ON_CMP_MATCH 3

/* Compare Output Mode, fast pWM Mode */
#define TMR0_NORMAL_PORT_OPERATION 0 /*OC0 pin disconnected*/
#define TMR0_NON_INVERTING_MODE \
  2 /*Clear OC0 on compare match, set OC0 at BOTTOM*/
#define TMR0_INVERTING_MODE                  \
  3 /*Set OC0 on compare match, clear OC0 at \
       BOTTOM*/

/* Compare Output Mode, phase correct pWM Mode */
#define TMR0_NORMAL_PORT_OPERATION 0 /*OC0 pin disconnected*/
#define TMR0_NON_INVERTING_MODE                                             \
  2 /*Clear OC0 on compare match when up-counting. Set OC0 on compare match \
       when downcounting*/
#define TMR0_INVERTING_MODE                                                 \
  3 /*Set OC0 on compare match when up-counting. Clear OC0 on compare match \
       when downcounting*/
/* ----------------- Macro Functions Declarations -----------------*/

#define TMR0_STOP_TIMER() (TCCR0 &= 0xF8)
#define TMR0_SET_PRESCALER(_pre) (TCCR0 |= _pre)
#define TMR0_SET_CMP_OUT_MODE(_mode) (TCCR0 |= (_mode << 4))

/* ----------------- Data Type Declarations -----------------*/

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  void (*TMR0_OverflowInterruptHandler)(void);
  void (*TMR0_CompareMatchInterruptHandler)(void);
#endif
  uint8 timer_mode : 2;
  uint8 prescale;
  uint8 cmp_out_mode : 2;
  uint8 preload_value;
  uint8 out_compare_value;
} timer0_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer0_Init(const timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const timer0_t *_timer);
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint8 _value);
Std_ReturnType Timer0_Set_compare_value(const timer0_t *_timer, uint8 _value);
uint8_t  Timer0_GetCounterValue();
void TIMER0_DutyCycle(const timer0_t *_timer, uint8 Duty_Cycle);
#endif /* HAL_TIMER_0_H*/
