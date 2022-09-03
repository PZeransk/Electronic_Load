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

#define CC_Button 16
#define CP_Button 17
#define BAT_Button 0
#define IS_CC_ON 0
#define IS_CP_ON 1
#define IS_BAT_ON 2

#define LP_PWM_PIN 4
#define PWM_Freq 4000
#define PWM_Channel 4
#define PWM_bit_Res 14

#if defined(ESP8266)
#define ROTARY_ENCODER_A_PIN D6
#define ROTARY_ENCODER_B_PIN D5
#define ROTARY_ENCODER_BUTTON_PIN D7
#else
#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 5
#define ROTARY_ENCODER_BUTTON_PIN 25
#endif
#define ROTARY_ENCODER_STEPS 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 


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
