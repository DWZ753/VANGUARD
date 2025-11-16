#include "RM.h"
#include "I2C.h"

void Start(void)
{
	SDA_High();
	SCL_High();
	
	HAL_Delay(5);
	
	SDA_Low(); 
	
	HAL_Delay(5);
	
	SCL_Low();
}

void Stop(void)
{
	SCL_Low();
	SDA_Low();
	
	HAL_Delay(5);
	
	SDA_High();
	
	HAL_Delay(5);
	
	SCL_High();
}

void SendByte(uint8_t data)
{
	for(int i = 0;i < 8;i++){
		SCL_Low();
		HAL_Delay(2);
		
		if(data & 0x80){
			SDA_High();
		}
		else{
			SDA_Low();
		}
		HAL_Delay(2);
		
		SCL_High();
		HAL_Delay(2);
		
		data<<;
	}
	
}

uint8_t ReceiveAck(void)
{
	uint8_t ack;
	
	SCL_Low();
	SDA_High();
	HAL_Delay(2);
		
	SCL_High();
	HAL_Delay(2);
	
	ack = SDA_Read();
	HAL_Delay(2);
	
	SCL_Low();
	HAL_Delay(2);
	
	return ack;
}

void SendData(uint8_t data)
{
	Start();
	SendByte(data);
	ReceiveAck();
	Stop();
}