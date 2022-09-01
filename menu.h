#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "AiEsp32RotaryEncoder.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdint>

typedef struct{
    uint32_t set_val1;
    uint32_t set_val2;
    uint8_t id;
    char line1[20];
    char line2[20];
    char line3[20];
    char line4[20];
}menu;


uint32_t ChangeArrayToInt(uint8_t InArr[]);
void zeroArray(uint8_t InArr[]);
void initStruct(menu *toInit, uint8_t id, char line1[], char line2[], char line3[], char line4[]);
void setCurrentMenu(menu *CurrMenu, menu *MenuToSet);
