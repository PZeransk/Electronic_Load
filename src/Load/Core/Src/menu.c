/*
 * menu.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Przemysław
 */
#include "menu.h"


uint32_t ChangeArrayToInt(char InArr[], uint8_t arraySize){
	uint32_t mult = 1;
    uint32_t out = 0;
    for(int i = 0; i< arraySize; i++){
        out+=(uint32_t)(InArr[arraySize-1-i]-'0')*mult;
        mult*=10;
    }
    return out;
}

void zeroArray(uint8_t InArr[]){
    int arraySize=sizeof(*InArr)/sizeof(uint8_t);

    for(int i = 0; i< arraySize; i++){
        InArr[i]=0;
    }

}

void initStruct(menu *toInit, char menuName[], char setValName[], char measVal1[], char measVal2[]){
	char zero_temp[5] = "00000";
    toInit->set_val1=0;
    toInit->set_val2=0;
    toInit->status = 0;
    strcpy(toInit->menuName, menuName);
    strcpy(toInit->setValName, setValName);
    strcpy(toInit->measVal1, measVal1);
    strcpy(toInit->measVal2, measVal2);
    strcpy(toInit->val_line1, zero_temp);
    strcpy(toInit->val_line2, zero_temp);
}

void setCurrentMenu(menu *CurrMenu, menu *MenuToSet){
    CurrMenu->set_val1=MenuToSet->set_val1;
    CurrMenu->set_val2=MenuToSet->set_val2;
    CurrMenu->id = MenuToSet -> id;
    strcpy(CurrMenu->menuName, MenuToSet->menuName);
    strcpy(CurrMenu->setValName, MenuToSet->setValName);
    strcpy(CurrMenu->measVal1, MenuToSet->measVal1);
    strcpy(CurrMenu->measVal2, MenuToSet->measVal2);
}

void displayMenu(menu *currMenu){
	uint8_t size = sizeof(currMenu->val_line1)/sizeof(currMenu->val_line1[0]);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(currMenu->menuName, Font_11x18, White);
	if(currMenu->status == false){
		ssd1306_SetCursor(95, 0);
		ssd1306_WriteString("OFF", Font_11x18, White);
	}else{
		ssd1306_SetCursor(106, 0);
		ssd1306_WriteString("ON", Font_11x18, White);
	}
	ssd1306_SetCursor(0, 18);
	ssd1306_WriteString(currMenu->setValName, Font_7x10, White);
	ssd1306_SetCursor(42, 18);
	ssd1306_WriteString(currMenu->val_line1, Font_7x10, White);
	ssd1306_SetCursor(size*7+42, 18);
	ssd1306_SetCursor(0, 28);
	ssd1306_WriteString(currMenu->measVal1, Font_7x10, White);
	ssd1306_SetCursor(0, 38);
	ssd1306_WriteString(currMenu->measVal2, Font_7x10, White);
	ssd1306_UpdateScreen();

}

