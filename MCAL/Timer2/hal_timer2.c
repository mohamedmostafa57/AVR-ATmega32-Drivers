/* 
 * File:   hal_timer2.c
 * Author: mO
 *
 * Created on 19 ??????, 2023, 02:13 ?
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR2_OverflowInterruptHandler)(void);
static void (*TMR2_CompareMatchInterruptHandler)(void);
#endif

static void Timer2_set_mode(const timer2_t *_timer);
static void Timer2_set_oc2_pin(const timer2_t *_timer);

Std_ReturnType Timer2_Init(const timer2_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    /* disable timer/counter*/
    TMR2_STOP_TIMER();
    /* select timer mode*/
    Timer2_set_mode(_timer);
    TMR2_SET_PRESCALER(_timer->prescale);
    TMR2_SET_CMP_OUT_MODE(_timer->cmp_out_mode);
    TCNT2 = _timer->preload_value;
    OCR2 = _timer->out_compare_value;
    Timer2_set_oc2_pin(_timer);
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    sei();
    TIMER2_CompareMatchInterruptEnable();
    TIMER2_OverflowInterruptEnable();
    TMR2_OverflowInterruptHandler = _timer->TMR2_OverflowInterruptHandler;
    TMR2_CompareMatchInterruptHandler = _timer->TMR2_CompareMatchInterruptHandler;
#endif
    ret = E_OK;
  }
  return ret;
}
Std_ReturnType Timer2_DeInit(const timer2_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TMR2_STOP_TIMER();
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER2_CompareMatchInterruptDisable();
    TIMER2_OverflowInterruptDisable();
#endif
    ret = E_OK;
  }
  return ret;
}
Std_ReturnType Timer2_Write_Value(const timer2_t *_timer, uint8 _value) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TCNT2 = _value;
    ret = E_OK;
  }
  return ret;
}

Std_ReturnType Timer2_Set_compare_value(const timer2_t *_timer, uint8 _value) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    OCR2 = _value;
    ret = E_OK;
  }
  return ret;
}

uint8 Timer2_GetCounterValue() { return TCNT2; }

void TIMER2_DutyCycle(const timer2_t *_timer, uint8 Duty_Cycle) {
  Duty_Cycle = Duty_Cycle / 100.0 * 255.0;
  if (_timer->cmp_out_mode == TMR2_NON_INVERTING_MODE) {
    OCR2 = Duty_Cycle;
  } else if (_timer->cmp_out_mode == TMR2_INVERTING_MODE) {
    OCR2 = (uint8)(255 - Duty_Cycle);
  }
}

static void Timer2_set_mode(const timer2_t *_timer) {
  switch (_timer->timer_mode) {
    case TMR2_NORMAL_MODE:
      CLEAR_BIT(TCCR2, WGM20);
      CLEAR_BIT(TCCR2, WGM21);
      break;
    case TMR2_PHASE_CORRECT_PWM_MODE:
      SET_BIT(TCCR2, WGM20);
      CLEAR_BIT(TCCR2, WGM21);
      break;
    case TMR2_CTC_MODE:
      CLEAR_BIT(TCCR2, WGM20);
      SET_BIT(TCCR2, WGM21);
      break;
    case TMR2_FAST_PWM_MODE:
      SET_BIT(TCCR2, WGM20);
      SET_BIT(TCCR2, WGM21);
      break;
    default:
      break;
  }
}

static void Timer2_set_oc2_pin(const timer2_t *_timer) {
  if (_timer->timer_mode != TMR2_NORMAL_MODE) {
    SET_BIT(DDRD, PB7);
  } else { /* Nothing */
  }
}

ISR(TIMER2_OVF_vect) {
  if (TMR2_OverflowInterruptHandler) {
    TMR2_OverflowInterruptHandler();
  }
}
ISR(TIMER2_COMP_vect) {
  if (TMR2_CompareMatchInterruptHandler) {
    TMR2_CompareMatchInterruptHandler();
  }
}