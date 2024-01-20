/* 
 * File:   hal_timer1.h
 * Author: mO
 *
 * Created on 18 ??????, 2023, 03:38 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* ----------------- Includes -----------------*/

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* ----------------- Macro Declarations -----------------*/

/* Compare Output Mode, non-PWM Mode */
#define TMR1_NORMAL_PORT_OPERATION 0 /*OC1 pin disconnected*/
#define TMR1_TOGGLE_OC1_ON_CMP_MATCH 1
#define TMR1_CLEAR_OC1_ON_CMP_MATCH 2
#define TMR1_SET_OC1_ON_CMP_MATCH 3

/* Compare Output Mode, fast pWM Mode */
#define TMR1_NORMAL_PORT_OPERATION 0 /*OC1A/B pin disconnected*/
#define TMR1_TOGGLE_OC1A_ON_WGM_15 1 /* WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected.
                                        For all other WGM13:0 settings, normal port 
                                        operation, OC1A/OC1B disconnected. */
#define TMR1_NON_INVERTING_MODE    2 /*Clear OC1A/B on compare match, set OC1A/B at BOTTOM*/
#define TMR1_INVERTING_MODE        3 /*Set OC1A/B on compare match, clear OC1A/B at BOTTOM*/

/* Compare Output Mode, Phase Correct and Phase and Frequency Correct PWM Mode */
#define TMR1_NORMAL_PORT_OPERATION      0 /*OC1A/B pin disconnected*/
#define TMR1_TOGGLE_OC1A_ON_WGM_9_OR_14 1 /* WGM13:0 = 9 OR 14: Toggle OC1A on Compare Match, OC1B disconnected.
                                          For all other WGM13:0 settings, normal port 
                                          operation, OC1A/OC1B disconnected. */
#define TMR1_NON_INVERTING_MODE         2 /*Clear OC1A/B on compare match when up-counting. Set OC1A/B on compare match when downcounting*/
#define TMR1_INVERTING_MODE             3 /*Set OC1A/B on compare match when up-counting. Clear OC1A/B on compare match when downcounting*/

/* timer1 Input Capture Edge Select */
#define TMR1_IC_FALLING_EDGE            0
#define TMR1_IC_RISING_EDGE             1

/* timer1 compare output register Select */
#define TMR1_COM_A            0
#define TMR1_COM_B            1

/* timer1 Clock Select Bit Description */
#define TMR1_NO_CLK_SOURCE               0 /*timer/counter stopped*/
#define TMR1_NO_PRESCALING               1
#define TMR1_PRESCALER_CLK_8             2
#define TMR1_PRESCALER_CLK_64            3
#define TMR1_PRESCALER_CLK_256           4
#define TMR1_PRESCALER_CLK_1024          5
#define TMR1_EXT_CLK_SRC_T1_FALLING_EDGE 6
#define TMR1_EXT_CLK_SRC_T1_RISING_EDGE  7
/* ----------------- Macro Functions Declarations -----------------*/

#define TMR1_STOP_TIMER() (TCCR1B &= 0xF8)
#define TMR1_SET_PRESCALER(_pre) (TCCR1B |= _pre)
#define TMR1_SET_CMP_OUT_MODE_COM1A(_mode) (TCCR1A |= (_mode << 6))
#define TMR1_SET_CMP_OUT_MODE_COM1B(_mode) (TCCR1A |= (_mode << 4))
#define TMR1_INPUT_CAPTURE_EDGE(_edge)     (TCCR1B |= (_edge << 6))

/* ----------------- Data Type Declarations -----------------*/

typedef enum{
    TMR1_NORMAL_MODE = 0,
    TMR1_PHASE_CORRECT_PWM_8_BIT,
    TMR1_PHASE_CORRECT_PWM_9_BIT,
    TMR1_PHASE_CORRECT_PWM_10_BIT,
    TMR1_CTC_MODE,
    TMR1_FAST_PWM_8_BIT,
    TMR1_FAST_PWM_9_BIT,
    TMR1_FAST_PWM_10_BIT,
    TMR1_PHASE_AND_FREQ_CORRECT_PWM_ICR1,
    TMR1_PHASE_AND_FREQ_CORRECT_PWM_OCR1A,
    TMR1_PHASE_CORRECT_PWM_ICR1,
    TMR1_PHASE_CORRECT_PWM_OCR1A,  
    TMR1_CTC_MODE_ICR1,
    RESERVED,
    TMR1_FAST_PWM_ICR1,
    TMR1_FAST_PWM_OCR1A
}wgm_cfg;

typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
  void (*TMR1_OverflowInterruptHandler)(void);
  void (*TMR1_CompareMatch_A_InterruptHandler)(void);
  void (*TMR1_CompareMatch_B_InterruptHandler)(void);
  void (*TMR1_InputCaptureInterruptHandler)(void);
#endif
  wgm_cfg timer_mode;
  uint8 prescale  :3;
  uint8 cmp_out_mode : 2;
  uint8 cmp_out_Reg :  1;
  uint8 icp_edge :  1;
  uint16 preload_value;
  uint16 out_compare_value;
  uint16 input_capture_value;
} timer1_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType Timer1_Init(const timer1_t *_timer);
Std_ReturnType Timer1_DeInit(const timer1_t *_timer);
Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value);
void Timer1_Set_compare_value(const timer1_t *_timer, uint16 _value);
uint16  Timer1_GetCounterValue();
void TIMER1_DutyCycle(const timer1_t *_timer, uint8 Duty_Cycle);
#endif	/* HAL_TIMER1_H */

