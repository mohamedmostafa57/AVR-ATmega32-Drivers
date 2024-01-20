/* 
 * File:   ecu_led.h
 * Author: mO
 *
 * Created on 02 ??????, 2023, 05:59 ?
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Includes */
#include "../../MCAL/GPIO/hal_gpio.h"


/* Section: Macro Declarations */

#define LED_OFF       0x00
#define LED_ON        1x01

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */

typedef struct{
    uint8 port : 4;
    uint8 pin : 3;
    uint8 led_status : 1;
}led_t;

/* Section: Function Declarations */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

