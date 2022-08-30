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
