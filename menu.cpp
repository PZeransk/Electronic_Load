#include "menu.h"

uint32_t ChangeArrayToInt(uint8_t InArr[]){
    int arraySize=sizeof(InArr)/sizeof(uint8_t);
    uint32_t out=0;
    for(int i = 0; i< arraySize; i++){
        out+=(uint32_t)pow(10,i)*InArr[arraySize-1-i];
    }
    return out;
}

void zeroArray(uint8_t InArr[]){
    int arraySize=sizeof(InArr)/sizeof(uint8_t);

    for(int i = 0; i< arraySize; i++){
        InArr[i]=0;
    }
    
}

void initStruct(menu *toInit, char line1[], char line2[], char line3[], char line4[]){
    toInit->set_val1=0;
    toInit->set_val2=0;
    strcpy(toInit->line1, line1);
    strcpy(toInit->line2, line2);
    strcpy(toInit->line3, line3);
    strcpy(toInit->line4, line4);
}

