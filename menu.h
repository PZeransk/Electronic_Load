#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "AiEsp32RotaryEncoder.h"
#include <vector>
#include <memory>
#include <string.h>

class LABEL{

private:
int8_t number_;
std::string text_;
public:
LABEL(int8_t number, std::string text);
void setText(std::string string);
void setNumber(int8_t number);
~LABEL();
};

class Menu{
private:

public:
virtual void drawMenu()=0;
virtual void createMenu()=0;
virtual void addLabel()=0;
virtual ~Menu(){};
};

class mainMenu:public Menu{
private:
std::vector<std::shared_ptr<LABEL>> labels_;
public:
mainMenu();
void drawMenu();
void addLabel();
void createMenu();
~mainMenu();
};