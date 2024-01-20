/* 
 * File:   hal_timer1.c
 * Author: mO
 *
 * Created on 18 ??????, 2023, 03:38 ?
 */

#include "hal_timer1.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TMR1_OverflowInterruptHandler)(void);
static void (*TMR1_CompareMatch_A_InterruptHandler)(void);
static void (*TMR1_CompareMatch_B_InterruptHandler)(void);
static void (*TMR1_InputCaptureInterruptHandler)(void);
#endif

static void Timer1_set_mode(const timer1_t *_timer);
static void Timer1_set_COM(const timer1_t *_timer);
static void Timer1_set_oc1_pin(const timer1_t *_timer);

Std_ReturnType Timer1_Init(const timer1_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    /* disable timer/counter*/
    TMR1_STOP_TIMER();
    /* select timer mode*/
    Timer1_set_mode(_timer);
    TMR1_SET_PRESCALER(_timer->prescale);
    Timer1_set_COM(_timer);
    TCNT1 = _timer->preload_value;
    Timer1_Set_compare_value(_timer , _timer->out_compare_value);
    Timer1_set_oc1_pin(_timer);
    ICR1 = _timer->input_capture_value;
    TMR1_INPUT_CAPTURE_EDGE(_timer->icp_edge);
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    sei();
    TIMER1_CompareMatch_A_InterruptEnable();
    TIMER1_CompareMatch_B_InterruptEnable();
    TIMER1_OverflowInterruptEnable();
    TIMER1_InputCaptureInterruptEnable();
    TMR1_OverflowInterruptHandler = _timer->TMR1_OverflowInterruptHandler;
    TMR1_CompareMatch_A_InterruptHandler =_timer->TMR1_CompareMatch_A_InterruptHandler;
    TMR1_CompareMatch_B_InterruptHandler = _timer->TMR1_CompareMatch_B_InterruptHandler;
    TMR1_InputCaptureInterruptHandler = _timer->TMR1_InputCaptureInterruptHandler;
#endif
    ret = E_OK;
  }
  return ret;
}

Std_ReturnType Timer1_DeInit(const timer1_t *_timer) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TMR1_STOP_TIMER();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    TIMER1_CompareMatch_A_InterruptDisable();
    TIMER1_CompareMatch_B_InterruptDisable();
    TIMER1_OverflowInterruptDisable();
    TIMER1_InputCaptureInterruptDisable();
#endif
    ret = E_OK;
  }
  return ret;
}

void Timer1_Set_compare_value(const timer1_t *_timer, uint16 _value) {
      if(_timer->cmp_out_Reg == TMR1_COM_A){
          OCR1A = _value;
      }
      else if(_timer->cmp_out_Reg == TMR1_COM_B){
          OCR1B = _value;
      }
}
static void Timer1_set_COM(const timer1_t *_timer){
    if(_timer->cmp_out_Reg == TMR1_COM_A){
          TMR1_SET_CMP_OUT_MODE_COM1A(_timer->cmp_out_mode);
      }
      else if(_timer->cmp_out_Reg == TMR1_COM_B){
          TMR1_SET_CMP_OUT_MODE_COM1B(_timer->cmp_out_mode);
      }
}
uint16 Timer1_GetCounterValue() { return TCNT1; }

void TIMER1_DutyCycle(const timer1_t *_timer, uint8 Duty_Cycle) {
  Duty_Cycle = Duty_Cycle / 100.0 * 65536.0;
  if (_timer->cmp_out_mode == TMR1_NON_INVERTING_MODE) {
    Timer1_Set_compare_value(_timer , Duty_Cycle);
  } else if (_timer->cmp_out_mode == TMR1_INVERTING_MODE) {
    Timer1_Set_compare_value(_timer , (uint8)(65536 - Duty_Cycle));
  }
}

static void Timer1_set_oc1_pin(const timer1_t *_timer) {
  if (_timer->timer_mode != TMR1_NORMAL_MODE) {
    if(_timer->cmp_out_Reg == TMR1_COM_A){
          SET_BIT(DDRD , PD5);
      }
      else if(_timer->cmp_out_Reg == TMR1_COM_B){
          SET_BIT(DDRD , PD4);
      }
  } else { /* Nothing */
  }
}

Std_ReturnType Timer1_Write_Value(const timer1_t *_timer, uint16 _value) {
  Std_ReturnType ret = E_NOT_OK;
  if (NULL == _timer) {
    ret = E_NOT_OK;
  } else {
    TCNT1 = _value;
    ret = E_OK;
  }
  return ret;
}

static void Timer1_set_mode(const timer1_t *_timer){
    switch (_timer->timer_mode) {
        case TMR1_NORMAL_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_CORRECT_PWM_8_BIT:
            SET_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_CORRECT_PWM_9_BIT:
            CLEAR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_CORRECT_PWM_10_BIT:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_CTC_MODE:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_FAST_PWM_8_BIT:
            SET_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_FAST_PWM_9_BIT:
            CLEAR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_FAST_PWM_10_BIT:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            CLEAR_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_AND_FREQ_CORRECT_PWM_ICR1:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_AND_FREQ_CORRECT_PWM_OCR1A:
            SET_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_CORRECT_PWM_ICR1:
            CLEAR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_PHASE_CORRECT_PWM_OCR1A:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            CLEAR_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_CTC_MODE_ICR1:
            CLEAR_BIT(TCCR1A,WGM10);
            CLEAR_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_FAST_PWM_ICR1:
            CLEAR_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        case TMR1_FAST_PWM_OCR1A:
            SET_BIT(TCCR1A,WGM10);
            SET_BIT(TCCR1A,WGM11);
            SET_BIT(TCCR1B,WGM12);
            SET_BIT(TCCR1B,WGM13);
            break;
        default:
            break;
    }
}

ISR(TIMER1_OVF_vect){
    if(TMR1_OverflowInterruptHandler){TMR1_OverflowInterruptHandler();}
}
ISR(TIMER1_COMPA_vect){
    if(TMR1_CompareMatch_A_InterruptHandler){TMR1_CompareMatch_A_InterruptHandler();}
}
ISR(TIMER1_COMPB_vect){
    if(TMR1_CompareMatch_B_InterruptHandler){TMR1_CompareMatch_B_InterruptHandler();}
}
ISR(TIMER1_CAPT_vect){
    if(TMR1_InputCaptureInterruptHandler){TMR1_InputCaptureInterruptHandler();}
}