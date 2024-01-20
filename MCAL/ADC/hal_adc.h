/* 
 * File:   hal_adc.h
 * Author: mO
 *
 * Created on 14 ??????, 2023, 03:35 ?
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* ----------------- Includes -----------------*/

#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ----------------- Macro Declarations -----------------*/


#define ADC_LEFT_ADJUST     0x01U
#define ADC_RIGHT_ADJUST    0x00U


#define ADC_CONVERSION_COMPLETED  0x01U
#define ADC_CONVERSION_INPROGRESS 0x00U

/* ----------------- Macro Functions Declarations -----------------*/

/* A/D Conversion Status : A/D conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS()  (READ_BIT(ADCSRA,ADIF))

/**
 * @brief Start the Analog-To-Digital Conversion
 */
#define ADC_START_CONVERSION()  (SET_BIT(ADCSRA,ADSC))

/**
 * @brief  Analog-To-Digital Control
 * @note   ADC_CONVERTER_ENABLE()  : Enable the Analog-To-Digital
 *         ADC_CONVERTER_DISABLE() : Disable the Analog-To-Digital
 */
#define ADC_CONVERTER_ENABLE()  (SET_BIT(ADCSRA,ADEN))
#define ADC_CONVERTER_DISABLE() (CLEAR_BIT(ADCSRA,ADEN))

/**
 * @brief Set voltage reference
 */

#define ADC_REF_VOLTAGE(_vref)   (ADMUX |= _vref<<6)

/**
 * @brief Set Prescaler value
 */

#define ADC_PRESCALER(_prescale)   (ADCSRA |= _prescale)
/**
 * @brief  A/D Channel Select
 */
#define ADC_CHANNEL_SELECT(_ch)  (ADMUX |= _ch)

/**
 * @brief  A/D Result Format Select
 */
#define ADC_RESULT_FORMAT(_format)  (ADMUX |= _format<<5)
/**
 * @brief  A/D trigger Select
 */
#define ADC_AUTO_TRIGGER_SELECT(_trig)  (SFIOR |= _trig<<5)

/**
 * @brief  A/D trigger Enable/Disable
 */
#define ADC_AUTO_TRIGGER_DISABLE()  (CLEAR_BIT(ADCSRA,ADATE))
#define ADC_AUTO_TRIGGER_ENABLE()   (SET_BIT(ADCSRA,ADATE))

/* ----------------- Data Type Declarations -----------------*/

/**
 * @brief Analog Channel Select
 */
typedef enum{
    ADC_CHANNEL_ADC0 = 0,
    ADC_CHANNEL_ADC1,
    ADC_CHANNEL_ADC2,
    ADC_CHANNEL_ADC3,
    ADC_CHANNEL_ADC4,
    ADC_CHANNEL_ADC5,
    ADC_CHANNEL_ADC6,
    ADC_CHANNEL_ADC7
}adc_channel_t;


/**
 * @brief  A/D Conversion Clock Select
 * 
 */
typedef enum{
    ADC_PRESCALE_FOSC_DIV_2 = 1,
    ADC_PRESCALE_FOSC_DIV_4,
    ADC_PRESCALE_FOSC_DIV_8,
    ADC_PRESCALE_FOSC_DIV_16,
    ADC_PRESCALE_FOSC_DIV_32,
    ADC_PRESCALE_FOSC_DIV_64,
    ADC_PRESCALE_FOSC_DIV_128
}adc_prescaler_t;
/**
 * @brief  A/D Reference voltage select
 * 
 */
typedef enum{
	AREF,	
	AVCC,
    RESERVED,
	INTERNAL_2_56
	}adc_reference_t;
    
/**
 * @brief  A/D Trigger select
 * 
 */
typedef enum{
	ADC_FREE_RUNNING,
	ADC_ANALOG_COMP,
	ADC_EXT_INT0,
	ADC_COMP_MATCH_TMR0,
	ADC_OVERFLOW_TMR0,
	ADC_COMP_MATCH_TMR1B,
	ADC_OVERFLOW_TMR1,
	ADC_TMR1_CAP_EVENT
	}ADC_TRIGGER_t;
/**
 * ADC Configurations
 */
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
#endif
    adc_prescaler_t prescaler;                /* @ref adc_prescaler_t */
    adc_channel_t adc_channel;                /* @ref adc_channel_select_t */
    ADC_TRIGGER_t trigger;
    adc_reference_t v_ref : 2;                    /* Voltage Reference Configuration */
    uint8 result_format : 1;                  /* A/D Result Format Select */ 
    uint8 auto_trigger_en : 1;  
    uint8 ADC_Reserved : 4;
}adc_conf_t;

/**
 * Result size of an A/D conversion
 */
typedef uint16 adc_result_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType ADC_Init(const adc_conf_t *_adc);
Std_ReturnType ADC_DeInit(const adc_conf_t *_adc);
Std_ReturnType ADC_StartConversion(const adc_conf_t *_adc , adc_channel_t channel);
uint8 ADC_IsConversionDone(void);
adc_result_t ADC_GetConversionResult(const adc_conf_t *_adc);
adc_result_t ADC_GetConversion_Blocking(const adc_conf_t *_adc, adc_channel_t channel);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *_adc, adc_channel_t channel);

#endif	/* HAL_ADC_H */

