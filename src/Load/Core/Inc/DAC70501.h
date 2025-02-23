#ifndef DAC70501_I2C_H
#define DAC70501_I2C_H

#include "stm32f4xx_hal.h"

//Defines

uint8_t DAC_addr = 0b100100 << 1; //address defined by A0 pin
uint16_t DAC_data = 0b00000000010000;
uint8_t DAC_data_send = 0b1000;
uint32_t DAC_command;

//Registers

#define DAC70501_NOOP 		0b00000000
#define DAC70501_DEVID		0b00000001
#define DAC70501_SYNC  		0b00000010
#define DAC70501_CONFIG 	0b00000011
#define DAC70501_GAIN		0b00000100
#define DAC70501_TRIGGER	0b00000101
#define DAC70501_STATUS		0b00000111
#define DAC70501_DAC_DATA	0b00001000


typedef struct{
	I2C_HandleTypeDef *i2cHandle;
	uint16_t binVoltage;
}DAC70501;

uint8_t DAC70501_init(DAC70501 *dev, I2C_HandleTypeDef *i2cHandle);

HAL_StatusTypeDef DAC70501_writeVoltage(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len);

HAL_StatusTypeDef DAC70501_writeRegister(DAC70501 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef DAC70501_readRegister(DAC70501 *dev, uint8_t reg, uint8_t *data);

HAL_StatusTypeDef DAC70501_writeRegisters(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len);
HAL_StatusTypeDef DAC70501_readRegisters(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len);
#endif
