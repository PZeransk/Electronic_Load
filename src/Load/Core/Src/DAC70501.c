#include "DAC70501.h"


uint8_t DAC70501_init(DAC70501 *dev, I2C_HandleTypeDef *i2cHandle){

	uint8_t err_cnt=0;
	dev->i2cHandle = i2cHandle;
	dev->binVoltage = 0 >> 2; // it should be 14 bit value
	HAL_SPI_StateTypeDef status;
	uint8_t regData=0;

	status = DAC70501_readRegister(dev, reg, regData);
	if(status!=HAL_OK)
		return 10;

	return err_cnt;
}

HAL_StatusTypeDef DAC70501_writeVoltage(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len);


HAL_StatusTypeDef DAC70501_writeRegister(DAC70501 *dev, uint8_t reg, uint8_t *data){
	return HAL_I2C_Mem_Write(dev->i2cHandle, DAC_addr, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef DAC70501_readRegister(DAC70501 *dev, uint8_t reg, uint8_t *data){
	return HAL_I2C_Mem_Read(dev->i2cHandle, DAC_addr, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef DAC70501_writeRegisters(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len){

	return HAL_I2C_Mem_Write(dev->i2cHandle, DAC_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}



HAL_StatusTypeDef DAC70501_readRegisters(DAC70501 *dev, uint8_t reg, uint8_t *data, uint8_t len){
	return HAL_I2C_Mem_Read(dev->i2cHandle, DAC_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
}
