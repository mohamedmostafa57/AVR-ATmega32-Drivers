/*
 * I2C.h
 *
 * Created: 8/30/2023 12:50:23 PM
 *  Author: GTX
 */ 


#ifndef I2C_H_
#define I2C_H_

/* =========================== Includes =========================== */

#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../mcal_std_types.h"

/* =============== Macros Configuration References ================ */
#define I2C_MASTER_MODE				1
#define I2C_SLAVE_MODE				0

#define I2C_INT_EN					1
#define I2C_INT_DIS					0

#define I2C_GEN_CALL_EN				1
#define I2C_GEN_CALL_DIS			0

/* defining of Status Codes for Master Transmitter Mode */
/* defining of Status Codes for Master Transmitter Mode */
#define START_SENT                0x08
#define REP_START_SENT            0x10
#define MT_SLA_ACK                0x18
#define MT_SLA_NACK               0x20
#define MT_DATA_ACK      	      0x28
#define MT_DATA_NACK      	      0x30
#define Arbitration_lost		  0x38

/** \ingroup util_twi
    \def TW_MR_SLA_ACK
    SLA+R transmitted, ACK received */
#define TW_MR_SLA_ACK		0x40

/** \ingroup util_twi
    \def TW_MR_SLA_NACK
    SLA+R transmitted, NACK received */
#define TW_MR_SLA_NACK		0x48

/** \ingroup util_twi
    \def TW_MR_DATA_ACK
    data received, ACK returned */
#define TW_MR_DATA_ACK		0x50

/** \ingroup util_twi
    \def TW_MR_DATA_NACK
    data received, NACK returned */
#define TW_MR_DATA_NACK		0x58

/* Slave Transmitter */
/** \ingroup util_twi
    \def TW_ST_SLA_ACK
    SLA+R received, ACK returned */
#define TW_ST_SLA_ACK		0xA8

/** \ingroup util_twi
    \def TW_ST_ARB_LOST_SLA_ACK
    arbitration lost in SLA+RW, SLA+R received, ACK returned */
#define TW_ST_ARB_LOST_SLA_ACK	0xB0

/** \ingroup util_twi
    \def TW_ST_DATA_ACK
    data transmitted, ACK received */
#define TW_ST_DATA_ACK		0xB8

/** \ingroup util_twi
    \def TW_ST_DATA_NACK
    data transmitted, NACK received */
#define TW_ST_DATA_NACK		0xC0

/** \ingroup util_twi
    \def TW_ST_LAST_DATA
    last data byte transmitted, ACK received */
#define TW_ST_LAST_DATA		0xC8

/* Slave Receiver */
/** \ingroup util_twi
    \def TW_SR_SLA_ACK
    SLA+W received, ACK returned */
#define TW_SR_SLA_ACK		0x60

/** \ingroup util_twi
    \def TW_SR_ARB_LOST_SLA_ACK
    arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_ARB_LOST_SLA_ACK	0x68

/** \ingroup util_twi
    \def TW_SR_GCALL_ACK
    general call received, ACK returned */
#define TW_SR_GCALL_ACK		0x70

/** \ingroup util_twi
    \def TW_SR_ARB_LOST_GCALL_ACK
    arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK 0x78

/** \ingroup util_twi
    \def TW_SR_DATA_ACK
    data received, ACK returned */
#define TW_SR_DATA_ACK		0x80

/** \ingroup util_twi
    \def TW_SR_DATA_NACK
    data received, NACK returned */
#define TW_SR_DATA_NACK		0x88

/** \ingroup util_twi
    \def TW_SR_GCALL_DATA_ACK
    general call data received, ACK returned */
#define TW_SR_GCALL_DATA_ACK	0x90

/** \ingroup util_twi
    \def TW_SR_GCALL_DATA_NACK
    general call data received, NACK returned */
#define TW_SR_GCALL_DATA_NACK	0x98

/** \ingroup util_twi
    \def TW_SR_STOP
    stop or repeated start condition received while selected */
#define TW_SR_STOP		0xA0

/* Misc */
/** \ingroup util_twi
    \def TW_NO_INFO
    no state information available */
#define TW_NO_INFO		0xF8

/** \ingroup util_twi
    \def TW_BUS_ERROR
    illegal start or stop condition */
#define TW_BUS_ERROR		0x00


typedef enum{
	I2C_PRESCALER_1,
	I2C_PRESCALER_4,
	I2C_PRESCALER_16,
	I2C_PRESCALER_64
	}I2C_PRESCALE_t;
	
typedef enum{
		RESET,
		SET
	}I2C_Flagstatus;
	
typedef enum
	{
		Disable,
		Enable
	}Functional_State;


typedef enum
	{
		Transmitter,
		Receiver
	}I2C_Direction;
	
typedef enum
{
	START,
	Repeated_START
}START_Condition;

typedef enum
{
	With_STOP,
	Without_STOP
}STOP_Condition;

#define GEN_START_COND()      SET_BIT(TWCR,TWSTA)
#define GEN_STOP_COND()       SET_BIT(TWCR,TWSTO)
#define CLEAR_I2C_INT_FLAG()  SET_BIT(TWCR,TWINT)

/* ============= User type definitions (structures) =============== */
typedef struct{
	uint8 I2C_MODE;				 // master or slave 
	uint32 I2C_BUS_FREQUENCY;				 // to select the division factor for the bit rate generator
	I2C_PRESCALE_t I2C_PRESCALER;	 // to specify state of the I2C Prescaler Bits
	uint8 I2C_INT;					 // to enable interrupt
	uint8 I2C_SLAVE_ADDRESS;			 // to determine the slave address of the controller in case if it becomes slave in the network
	uint8 I2C_GEN_CALL;			 // to enable/disable the recognition of a General Call given over the Two-wire Serial Bus
	void (*I2C_INT_Handler)(void);
	}i2c_t;

/* =========== APIs Supported by "MCAL SPI DRIVER" ================ */
void I2C_Init(i2c_t *I2C_Config);
void I2C_DeInit(void);


/*
 * Master Polling Mechanism
 */
void I2C_MASTER_TX(uint8 Device_Address, uint8 pTxData, STOP_Condition Stop, START_Condition Start);
void I2C_MASTER_RX(uint8 Device_Address, uint8 *pRxData, STOP_Condition Stop, START_Condition Start);

void I2C_MASTER_WRITE_REGISTER(uint8 Device_Address, uint8 reg , uint8 pTxData, STOP_Condition Stop, START_Condition Start);
uint8 I2C_MASTER_READ_REGISTER(uint8 Device_Address, uint8 reg , STOP_Condition Stop, START_Condition Start);

/*
 * 
 */
void I2C_Slave_TX(uint8 TxData);
uint8 I2C_Slave_RX();


/*
 * Generic APIs
 */
I2C_Flagstatus I2C_Get_FlagStatus(uint8 Flag);

void I2C_Generate_Start(START_Condition Start);
void I2C_Send_Address(uint8 Device_Address,I2C_Direction Direction);
void I2C_ACKConfig(i2c_t *I2C_Config, Functional_State State);
void I2C_Generate_Stop();




#endif /* I2C_H_ */