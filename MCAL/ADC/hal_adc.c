/* 
 * File:   hal_adc.c
 * Author: mO
 *
 * Created on 14 ??????, 2023, 03:35 ?
 */

#include "hal_adc.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

Std_ReturnType ADC_Init(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
        ADC_CHANNEL_SELECT(_adc->adc_channel);
        ADC_PRESCALER(_adc->prescaler);
        ADC_RESULT_FORMAT(_adc->result_format);
        ADC_REF_VOLTAGE(_adc->v_ref);
        if(_adc->auto_trigger_en){
            ADC_AUTO_TRIGGER_ENABLE();
            ADC_AUTO_TRIGGER_SELECT(_adc->trigger);
        }
        else{
            ADC_AUTO_TRIGGER_DISABLE();
        }
#if ADC_INTERRUPT_FEATURE_ENABLE== INTERRUPT_FEATURE_ENABLE
        sei();
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        ADC_InterruptHandler = _adc->ADC_InterruptHandler;
#endif
        ADC_CONVERTER_ENABLE();
        ret = E_OK;
    }
    return ret;
}
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CONVERTER_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE== INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc , adc_channel_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_CHANNEL_SELECT(channel);
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
}
uint8 ADC_IsConversionDone(void){
    
    return ADC_CONVERSION_STATUS();
        
}
adc_result_t ADC_GetConversionResult(const adc_conf_t *_adc){
    
    if(_adc->result_format == ADC_LEFT_ADJUST){
        return (uint8)ADCH;
    }
    else if(_adc->result_format == ADC_RIGHT_ADJUST){
        return ADC;
    }
    else{
        return ADC;
    }

}
adc_result_t ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_t channel){
    ADC_StartConversion(_adc , channel);
    while(!ADC_CONVERSION_STATUS());
    return ADC_GetConversionResult(_adc);
}
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_InterruptFlagClear();
        /* Start the conversion */
        ret = ADC_StartConversion(_adc , channel);
        ret = E_OK;
    }
    return ret;
}

ISR(ADC_vect){
    if(ADC_InterruptHandler){ADC_InterruptHandler();}
}