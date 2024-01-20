/* 
 * File:   RealTimeClockDS1307.h
 * Author: Ahmed Abd El-Ghafar
 * Created on February 18, 2023, 1:48 PM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

#include "../../MCAL/I2C/I2C.h"
#include "../../MCAL/usart/usart.h"
#include "../../MCAL/GPIO/hal_gpio.h"
typedef struct{
    uint8 _Hours;
    uint8 _Minutes;
    uint8 _Seconds;
    uint8 _Year;
    uint8 _Month;
    uint8 _Day;
}RealTimeClockDS1307_T;

RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void);
void Print_RealTimeClockDS1307(void);
void Try_Print_RealTimeClockDS1307(void);
#endif	/* REALTIMECLOCKDS1307_H */

