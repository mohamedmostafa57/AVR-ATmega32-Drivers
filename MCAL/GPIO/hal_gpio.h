/* 
 * File:   hal_gpio.h
 * Author: mO
 *
 * Created on 02 ??????, 2023, 05:23 ?
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Includes */

#include "../MCAL_STD_TYPES.h"
#include "../device_config.h"

/* Section: Macro Declarations */
#define BIT_MASK  (uint8)1

#define PORT_PIN_MAX_NUMBER    8
#define PORT_MAX_NUMBER        5

#define GPIO_LOW               0
#define GPIO_HIGH              1

#define GPIO_DIRECTION_INPUT   0
#define GPIO_DIRECTION_OUTPUT  1

/* Section: Macro Functions Declarations */

#define SET_BIT(REG, BIT_POSN)     (REG |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)   (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)  (REG ^= (BIT_MASK << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)    ((REG >> BIT_POSN) & BIT_MASK)

/* Section: Data Types Declaration      */

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
}port_index_t;

typedef struct{
    uint8 port      : 2;       /* @ref port_index_t */
    uint8 pin       : 3;       /* @ref pin_index_t */
    uint8 direction : 1; 
    uint8 logic     : 1;     
}pin_config_t;

/* Section: Function Declarations */
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, uint8 *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, uint8 logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, uint8 *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif