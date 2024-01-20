/*
 * I2C.c
 *
 * Created: 8/30/2023 12:49:34 PM
 *  Author: GTX
 */ 
#include "I2C.h"
static void (*I2C_INTERRUPT_HANDLER )(void)= NULL;

void I2C_Generate_Start(START_Condition Start){

		// Transmit START condition
		TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
		if (Start == Repeated_START)
		while(!I2C_Get_FlagStatus(REP_START_SENT));
		else
		while(!I2C_Get_FlagStatus(START_SENT));
}

void I2C_Generate_Stop(){
	
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2CWrite(uint8 pTxData) {
	
	TWDR = pTxData;

	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for data transmission to complete
	while (!(TWCR & (1 << TWINT)));
}

void I2CRead(uint8 ack,uint8 *pTxData) {
	// Enable or disable acknowledging of received data
	if (ack)
	TWCR |= (1 << TWEA);
	else
	TWCR &= ~(1 << TWEA);


	// Start data reception
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for data reception to complete
	while (!(TWCR & (1 << TWINT)));

	// Return received data
	*pTxData=TWDR;
}


void I2C_Send_Address(uint8 Device_Address,I2C_Direction Direction){
	uint8 temp = ((Device_Address<<1) |Direction);
	I2CWrite(temp);
	
}

void I2C_MASTER_TX( uint8 Device_Address, uint8 pTxData, STOP_Condition Stop, START_Condition Start){
	I2C_Generate_Start(Start);
	I2C_Send_Address(Device_Address,Transmitter);
	while(!I2C_Get_FlagStatus(MT_SLA_ACK));
	I2CWrite(pTxData);
	while(!I2C_Get_FlagStatus(MT_DATA_ACK));
	if (Stop == With_STOP)
	{
		I2C_Generate_Stop(Stop);
	}
	
	
}
void I2C_MASTER_RX( uint8 Device_Address, uint8 *pRxData, STOP_Condition Stop, START_Condition Start){
	I2C_Generate_Start(Start);
	I2C_Send_Address(Device_Address,Receiver);
    while(!I2C_Get_FlagStatus(TW_MR_SLA_ACK));
	I2CRead(1,pRxData);
    //while(!I2C_Get_FlagStatus(TW_MR_DATA_ACK));
	if (Stop == With_STOP)
	{
		I2C_Generate_Stop(Stop);
	}
}

uint8 I2C_MASTER_READ_REGISTER(uint8 Device_Address, uint8 reg , STOP_Condition Stop, START_Condition Start){
    uint8 ret_data = 0;
    I2C_Generate_Start(Start);
    I2C_Send_Address(Device_Address,Transmitter);
    while(!I2C_Get_FlagStatus(MT_SLA_ACK));
	I2CWrite(reg);
    while(!I2C_Get_FlagStatus(MT_DATA_ACK));
    I2C_Generate_Start(Repeated_START);
    I2C_Send_Address(Device_Address,Receiver);
    while(!I2C_Get_FlagStatus(TW_MR_SLA_ACK));
	I2CRead(1,&ret_data);
    if (Stop == With_STOP)
	{
		I2C_Generate_Stop(Stop);
	}
    return ret_data;
}



void I2C_Init(i2c_t *I2C_Config){
		I2C_INTERRUPT_HANDLER=I2C_Config->I2C_INT_Handler;
		// Set I2C clock frequency
		TWBR = ((F_CPU / I2C_Config->I2C_BUS_FREQUENCY) - 16) / 2;
		TWCR = (1 << TWEN);
		TWSR |= I2C_Config->I2C_PRESCALER & (uint8)0x3;
		TWAR = I2C_Config->I2C_SLAVE_ADDRESS<<1;
		if (I2C_Config->I2C_MODE==I2C_SLAVE_MODE)
		{
			TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
		}
		if (I2C_Config->I2C_GEN_CALL == I2C_GEN_CALL_EN)
		TWAR |= (1<<TWGCE);
		
		if (I2C_Config->I2C_INT == I2C_INT_EN)
		{
			
			SET_BIT(TWCR,TWIE);
			sei();
		}
		// Enable I2C

}

void I2C_DeInit(void){
	TWCR =0;
	TWSR =0;
	TWBR =0;
	TWAR =0;
}
I2C_Flagstatus I2C_Get_FlagStatus( uint8 Flag){
	I2C_Flagstatus Bit_Status = RESET;

	if (Flag == (TWSR&0xF8))
	{
		Bit_Status=SET;
	}
		
		return Bit_Status;
		
	}

uint8 I2C_FlagStatus( ){
	 
	return(TWSR&0xF8);
	

}




uint8 I2C_Slave_RX(){
//using interrupt
    static uint8 data = 0;

	switch (I2C_FlagStatus()) {
		case TW_SR_DATA_ACK:
		// Data received with acknowledgment
		data = TWDR;
		break;

		case TW_ST_DATA_NACK:
		case TW_SR_DATA_NACK:
		case TW_SR_STOP:
		default:
		// Error handling or other cases
		break;
	}

	// Clear interrupt flag
	TWCR |= (1 << TWINT);
	return data;
}

void I2C_Slave_TX(uint8 TxData){
    while(I2C_FlagStatus() != TW_ST_SLA_ACK);
		// Data requested by master with acknowledgment
		TWDR = TxData;

		// Send data
		TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    
}

ISR(TWI_vect) {
	I2C_INTERRUPT_HANDLER();
}

















