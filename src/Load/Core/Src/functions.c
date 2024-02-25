/*
 * functions.c
 *
 *  Created on: Feb 25, 2024
 *      Author: Przemysław
 */


#include "functions.h"

// checks if set pin was held for a certain time, then sets right mode, or increments right int
void checkLongPress(GPIO_TypeDef *GPIOx, uint16_t GPIO_NAME, bool *mode, uint8_t *toggles){

    if(HAL_GPIO_ReadPin(GPIOx, GPIO_NAME) == 1){
    	uint32_t time = 0;
    	uint32_t time2 = 0;

    	time = HAL_GetTick();
    	while(HAL_GPIO_ReadPin(GPIOx, GPIO_NAME) == 1){
    		time2 = HAL_GetTick();
    	}
    	time2 = HAL_GetTick();
    	if(time2-time >= 1000){
    		*mode = !(*mode);
    	}else{
    		*toggles = *toggles + 1;
    	}
    }
}
