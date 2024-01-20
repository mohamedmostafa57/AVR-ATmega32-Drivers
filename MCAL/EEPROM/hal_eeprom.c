/* 
 * File:   hal_eeprom.c
 * Author: Ahmed Abd El-Ghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on May 15, 2021, 11:09 PM
 */

#include "hal_eeprom.h"

/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3ff, 0);
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Global_Interrupt_Status = READ_BIT(SREG,SREG_I);
    /* Wait for register bits */
    while(READ_BIT(EECR,EEWE));
    while(READ_BIT(SPMCR,SPMEN));
    /* Update the Address Registers */
    EEARH = (uint8)((bAdd >> 8) & 0x03);
    EEARL = (uint8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDR = bData;
    /* Disable all interrupts "General Interrupt" */
    cli();
    /* Allows write cycles to Flash program/data EEPROM */
    CLEAR_BIT(EECR,EEWE);
    SET_BIT(EECR,EEMWE);
    SET_BIT(EECR,EEWE);
    /* Restore the Interrupt Status "Enabled or Disabled" */
    SREG |= (Global_Interrupt_Status << SREG_I);
    return ret;
}

/**
 * @Summary Reads a data byte from Data EEPROM
 * @Description This routine reads a data byte from given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location from which data has to be read
 * @param bData - Data byte read from given Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_ReadByte(0x3ff, &eeprom_read_val);
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else{
        /* Wait for register bits */
        while(READ_BIT(EECR,EEWE));
        /* Update the Address Registers */
        EEARH = (uint8)((bAdd >> 8) & 0x03);
        EEARL = (uint8)(bAdd & 0xFF);
        /* Initiates a data EEPROM read cycle */
        SET_BIT(EECR,EERE);
        /* Return data */
        *bData = EEDR;
        ret = E_OK;
    }
    return ret;
}
