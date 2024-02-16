/*
 * menu.c
 *
 *  Created on: Feb 16, 2024
 *      Author: Przemysław
 */
#include "menu.h"


uint32_t ChangeArrayToInt(uint8_t InArr[]){
    int arraySize=sizeof(*InArr)/sizeof(uint8_t);
    uint32_t out=0;
    for(int i = 0; i< arraySize; i++){
        out+=(uint32_t)pow(10,i)*InArr[arraySize-1-i];
    }
    return out;
}

void zeroArray(uint8_t InArr[]){
    int arraySize=sizeof(*InArr)/sizeof(uint8_t);

    for(int i = 0; i< arraySize; i++){
        InArr[i]=0;
    }

}

void initStruct(menu *toInit, uint8_t id, char line1[], char line2[], char line3[], char line4[]){
    toInit->set_val1=0;
    toInit->set_val2=0;
    toInit->id=id;
    toInit->status = 0;
    strcpy(toInit->line1, line1);
    strcpy(toInit->line2, line2);
    strcpy(toInit->line3, line3);
    strcpy(toInit->line4, line4);
}

void setCurrentMenu(menu *CurrMenu, menu *MenuToSet){
    CurrMenu->set_val1=MenuToSet->set_val1;
    CurrMenu->set_val2=MenuToSet->set_val2;
    CurrMenu->id = MenuToSet -> id;
    strcpy(CurrMenu->line1, MenuToSet->line1);
    strcpy(CurrMenu->line2, MenuToSet->line2);
    strcpy(CurrMenu->line3, MenuToSet->line3);
    strcpy(CurrMenu->line4, MenuToSet->line4);
}

void displayMenu(menu *currMenu){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(currMenu->line1, Font_11x18, White);
	if(currMenu->status == false){
		ssd1306_SetCursor(95, 0);
		ssd1306_WriteString("OFF", Font_11x18, White);
	}else{
		ssd1306_SetCursor(106, 0);
		ssd1306_WriteString("ON", Font_11x18, White);
	}
	ssd1306_SetCursor(0, 18);
	ssd1306_WriteString(currMenu->line2, Font_7x10, White);
	ssd1306_SetCursor(0, 28);
	ssd1306_WriteString(currMenu->line3, Font_7x10, White);
	ssd1306_SetCursor(0, 38);
	ssd1306_WriteString(currMenu->line4, Font_7x10, White);
	ssd1306_UpdateScreen();

}

