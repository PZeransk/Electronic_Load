/*
 * menu.h
 *
 *  Created on: Feb 16, 2024
 *      Author: Przemysław
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "ssd1306.h"
#include "ssd1306_conf_template.h"
#include "ssd1306_fonts.h"
#include "ssd1306_tests.h"
#include "stdbool.h"

typedef struct{
    uint32_t set_val1;
    uint32_t set_val2;
    bool status;
    uint8_t id;
    char menuName[20];
    char setValName[20];
    char measVal1[20];
    char measVal2[20];
    char val_line1[5];
    char val_line2[5];
}menu;


uint32_t ChangeArrayToInt(char InArr[], uint8_t arraySize);
void zeroArray(uint8_t InArr[]);
void initStruct(menu *toInit, char menuName[], char setValName[], char measVal1[], char measVal2[]);
void setCurrentMenu(menu *CurrMenu, menu *MenuToSet);
void displayMenu(menu *currMenu);

#endif /* INC_MENU_H_ */
