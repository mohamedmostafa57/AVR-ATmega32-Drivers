/*
 * File:   hal_timer.c
 * Author: mO
 *
 * Created on 12 ??????, 2023, 06:40 ?
 */
#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR0_OverflowInterruptHandler)(void);
static void (*TMR0_CompareMatchInterruptHandler)(void);
#endif

static void Timer0_set_mode(const timer0_t *_timer);
static void Timer0_set_oc0_pin(const timer0_t *_timer);

Std_ReturnType Timer0_Init(const timer0_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    /* disable timer/counter*/
    TMR0_STOP_TIMER();
    /* select timer mode*/
    Timer0_set_mode(_timer);
    TMR0_SET_PRESCALER(_timer->prescale);
    TMR0_SET_CMP_OUT_MODE(_timer->cmp_out_mode);
    TCNT0 = _timer->preload_value;
    OCR0 = _timer->out_compare_value;
    Timer0_set_oc0_pin(_timer);
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    sei();
    TIMER0_CompareMatchInterruptEnable();
    TIMER0_OverflowInterruptEnable();
    TMR0_OverflowInterruptHandler = _timer->TMR0_OverflowInterruptHandler;
    TMR0_CompareMatchInterruptHandler =
        _timer->TMR0_CompareMatchInterruptHandler;
#endif
    ret = E_OK;
  }
  return ret;
}
Std_ReturnType Timer0_DeInit(const timer0_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TMR0_STOP_TIMER();
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER0_CompareMatchInterruptDisable();
    TIMER0_OverflowInterruptDisable();
#endif
    ret = E_OK;
  }
  return ret;
}
Std_ReturnType Timer0_Write_Value(const timer0_t *_timer, uint8 _value) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TCNT0 = _value;
    ret = E_OK;
  }
  return ret;
}

Std_ReturnType Timer0_Set_compare_value(const timer0_t *_timer, uint8 _value) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    OCR0 = _value;
    ret = E_OK;
  }
  return ret;
}

uint8 Timer0_GetCounterValue() { return TCNT0; }

void TIMER0_DutyCycle(const timer0_t *_timer, uint8 Duty_Cycle) {
  Duty_Cycle = Duty_Cycle / 100.0 * 255.0;
  if (_timer->cmp_out_mode == TMR0_NON_INVERTING_MODE) {
    OCR0 = Duty_Cycle;
  } else if (_timer->cmp_out_mode == TMR0_INVERTING_MODE) {
    OCR0 = (uint8)(255 - Duty_Cycle);
  }
}

static void Timer0_set_mode(const timer0_t *_timer) {
  switch (_timer->timer_mode) {
    case TMR0_NORMAL_MODE:
      CLEAR_BIT(TCCR0, WGM00);
      CLEAR_BIT(TCCR0, WGM01);
      break;
    case TMR0_PHASE_CORRECT_PWM_MODE:
      SET_BIT(TCCR0, WGM00);
      CLEAR_BIT(TCCR0, WGM01);
      break;
    case TMR0_CTC_MODE:
      CLEAR_BIT(TCCR0, WGM00);
      SET_BIT(TCCR0, WGM01);
      break;
    case TMR0_FAST_PWM_MODE:
      SET_BIT(TCCR0, WGM00);
      SET_BIT(TCCR0, WGM01);
      break;
    default:
      break;
  }
}

static void Timer0_set_oc0_pin(const timer0_t *_timer) {
  if (_timer->timer_mode != TMR0_NORMAL_MODE) {
    SET_BIT(DDRB, PB3);
  } else { /* Nothing */
  }
}

ISR(TIMER0_OVF_vect) {
  if (TMR0_OverflowInterruptHandler) {
    TMR0_OverflowInterruptHandler();
  }
}
ISR(TIMER0_COMP_vect) {
  if (TMR0_CompareMatchInterruptHandler) {
    TMR0_CompareMatchInterruptHandler();
  }
}