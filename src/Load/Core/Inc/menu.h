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
    char line1[20];
    char line2[20];
    char line3[20];
    char line4[20];
    char val_line1[5];
    char val_line2[5];
}menu;


uint32_t ChangeArrayToInt(uint8_t InArr[]);
void zeroArray(uint8_t InArr[]);
void initStruct(menu *toInit, char line1[], char line2[], char line3[], char line4[]);
void setCurrentMenu(menu *CurrMenu, menu *MenuToSet);
void displayMenu(menu *currMenu);

#endif /* INC_MENU_H_ */
