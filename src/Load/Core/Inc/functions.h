/*
 * functions.h
 *
 *  Created on: Feb 25, 2024
 *      Author: Przemysław
 */

#ifndef INC_FUNCTIONS_H_
#define INC_FUNCTIONS_H_

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "ssd1306.h"
#include "ssd1306_conf_template.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"
#include "stdbool.h"
#include "stdbool.h"

void checkLongPress(GPIO_TypeDef *GPIOx, uint16_t GPIO_NAME, bool *mode, uint8_t *toggles);


#endif /* INC_FUNCTIONS_H_ */
