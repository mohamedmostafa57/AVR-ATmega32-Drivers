/* 
 * File:   hal_timer2.h
 * Author: mO
 *
 * Created on 19 ??????, 2023, 02:13 ?
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* ----------------- Includes -----------------*/

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* ----------------- Macro Declarations -----------------*/
/* timer2 Clock Select Bit Description */
#define TMR2_NO_CLK_SOURCE      0   /*timer/counter stopped*/
#define TMR2_NO_PRESCALING      1
#define TMR2_PRESCALER_CLK_8    2
#define TMR2_PRESCALER_CLK_32   3
#define TMR2_PRESCALER_CLK_64   4
#define TMR2_PRESCALER_CLK_128  5
#define TMR2_PRESCALER_CLK_256  6
#define TMR2_PRESCALER_CLK_1024 7

/* Waveform Generation Mode Bit Description */
#define TMR2_NORMAL_MODE            0
#define TMR2_PHASE_CORRECT_PWM_MODE 1
#define TMR2_CTC_MODE               2
#define TMR2_FAST_PWM_MODE          3

/* Compare Output Mode, non-PWM Mode */
#define TMR2_NORMAL_PORT_OPERATION   0 /*OC2 pin disconnected*/
#define TMR2_TOGGLE_OC2_ON_CMP_MATCH 1
#define TMR2_CLEAR_OC2_ON_CMP_MATCH  2
#define TMR2_SET_OC2_ON_CMP_MATCH    3

/* Compare Output Mode, fast pWM Mode */
#define TMR2_NORMAL_PORT_OPERATION 0 /*OC2 pin disconnected*/
#define TMR2_NON_INVERTING_MODE    2 /*Clear OC2 on compare match, set OC2 at BOTTOM*/
#define TMR2_INVERTING_MODE        3 /*Set OC2 on compare match, clear OC2 at BOTTOM*/

/* Compare Output Mode, phase correct pWM Mode */
#define TMR2_NORMAL_PORT_OPERATION 0 /*OC2 pin disconnected*/
#define TMR2_NON_INVERTING_MODE    2 /*Clear OC2 on compare match when up-counting. Set OC2 on compare match when downcounting*/
#define TMR2_INVERTING_MODE        3 /*Set OC2 on compare match when up-counting. Clear OC2 on compare match when downcounting*/
/* ----------------- Macro Functions Declarations -----------------*/

#define TMR2_STOP_TIMER()            (TCCR2 &= 0xF8)
#define TMR2_SET_PRESCALER(_pre)     (TCCR2 |= _pre)
#define TMR2_SET_CMP_OUT_MODE(_mode) (TCCR2 |= (_mode << 4))

/* ----------------- Data Type Declarations -----------------*/

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  void (*TMR2_OverflowInterruptHandler)(void);
  void (*TMR2_CompareMatchInterruptHandler)(void);
#endif
  uint8 timer_mode : 2;
  uint8 prescale;
  uint8 cmp_out_mode : 2;
  uint8 preload_value;
  uint8 out_compare_value;
} timer2_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer2_Init(const timer2_t *_timer);
Std_ReturnType Timer2_DeInit(const timer2_t *_timer);
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value);
Std_ReturnType Timer2_Set_compare_value(const timer2_t *_timer, uint8 _value);
uint8_t  Timer2_GetCounterValue();
void TIMER2_DutyCycle(const timer2_t *_timer, uint8 Duty_Cycle);

#endif	/* HAL_TIMER2_H */

