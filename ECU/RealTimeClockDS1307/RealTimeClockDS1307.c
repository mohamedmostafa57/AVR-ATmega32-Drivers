/* 
 * File:   RealTimeClockDS1307.c
 * Author: Ahmed Abd El-Ghafar
 * Created on February 18, 2023, 1:48 PM
 */

#include "RealTimeClockDS1307.h"

static RealTimeClockDS1307_T RealTimeClockDS1307;
#define DS1307_ADDRESS   0x68
/* "_Year" - "_Month" - "_Day" */
static uint8 RealTimeClockDS1307_Pack[18]; 
static uint8 Try_RealTimeClockDS1307_Pack[3]; 
RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void){
    RealTimeClockDS1307._Seconds = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x00, With_STOP , START);
    RealTimeClockDS1307._Minutes = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x01, With_STOP , START);
    RealTimeClockDS1307._Hours   = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x02, With_STOP , START);
    RealTimeClockDS1307._Day     = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x04, With_STOP , START);
    RealTimeClockDS1307._Month   = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x05, With_STOP , START);
    RealTimeClockDS1307._Year    = I2C_MASTER_READ_REGISTER(DS1307_ADDRESS, 0x06, With_STOP , START);
    
    return RealTimeClockDS1307;
}

void Print_RealTimeClockDS1307(void){ 
    RealTimeClockDS1307_Pack[0] = ((RealTimeClockDS1307._Day >> 4) + 0x30);
    RealTimeClockDS1307_Pack[1] = ((RealTimeClockDS1307._Day & 0x0F) + 0x30);
    RealTimeClockDS1307_Pack[2] = '-';
    RealTimeClockDS1307_Pack[3] = ((RealTimeClockDS1307._Month >> 4) + 0x30);
    RealTimeClockDS1307_Pack[4] = ((RealTimeClockDS1307._Month & 0x0F) + 0x30);
    RealTimeClockDS1307_Pack[5] = '-';
    RealTimeClockDS1307_Pack[6] = ((RealTimeClockDS1307._Year >> 4) + 0x30);
    RealTimeClockDS1307_Pack[7] = ((RealTimeClockDS1307._Year & 0x0F) + 0x30);
    
    RealTimeClockDS1307_Pack[8] = '/';
    
    RealTimeClockDS1307_Pack[9]  = ((RealTimeClockDS1307._Hours >> 4) + 0x30);
    RealTimeClockDS1307_Pack[10] = ((RealTimeClockDS1307._Hours & 0x0F) + 0x30);
    RealTimeClockDS1307_Pack[11] = '-';
    RealTimeClockDS1307_Pack[12] = ((RealTimeClockDS1307._Minutes >> 4) + 0x30);
    RealTimeClockDS1307_Pack[13] = ((RealTimeClockDS1307._Minutes & 0x0F) + 0x30);
    RealTimeClockDS1307_Pack[14] = '-';
    RealTimeClockDS1307_Pack[15] = ((RealTimeClockDS1307._Seconds >> 4) + 0x30);
    RealTimeClockDS1307_Pack[16] = ((RealTimeClockDS1307._Seconds & 0x0F) + 0x30);
    
    RealTimeClockDS1307_Pack[17] = '\r';
    uint8 str[8] = "Data : ";
    USART_WriteStringBlocking(str, 8);
    USART_WriteStringBlocking(RealTimeClockDS1307_Pack, 18);
}

void Try_Print_RealTimeClockDS1307(void){
    Try_RealTimeClockDS1307_Pack[0] = (RealTimeClockDS1307._Minutes + 0x30);
    Try_RealTimeClockDS1307_Pack[2] = '\r';
    uint8 str[8] = "Data : ";
    USART_WriteStringBlocking(str, 8);
    USART_WriteStringBlocking(Try_RealTimeClockDS1307_Pack, 4);
}