#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

void Start(void);
void Stop(void);
void SendByte(uint8_t data);
uint8_t ReceiveAck(void);
void SendData(uint8_t data);

#endif