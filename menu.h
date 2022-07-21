#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "AiEsp32RotaryEncoder.h"
#include <vector>
#include <memory>
#include <string>

extern int16_t menu_level[6];

class LABEL{
private:
int8_t number_;
std::string text_;
public:
LABEL(int8_t number, std::string text);
void setText(std::string string);
std::string getText();
int8_t getNumber();
void setNumber(int8_t number);
~LABEL();
};

class Menu{
private:

public:
virtual void beginDraw(Adafruit_SSD1306 &display)=0;
virtual void drawMenu(Adafruit_SSD1306 &display)=0;
virtual void createMenu()=0;
virtual void addLabel(int8_t number, std::string text)=0;
virtual void drawPointer(int8_t position, Adafruit_SSD1306 &display)=0;
virtual uint8_t returnLabelCount()=0;
virtual void endDraw(Adafruit_SSD1306 &display)=0;
virtual int8_t select(int8_t position)=0;
virtual ~Menu(){};
};



class CCMenu: public Menu{
private:
std::vector<std::shared_ptr<LABEL>> labels_;
uint8_t pointerPos;

public:
CCMenu();
void beginDraw(Adafruit_SSD1306 &display);
void drawMenu(Adafruit_SSD1306 &display);
void createMenu();
void addLabel(int8_t number, std::string text);
void drawPointer(int8_t position, Adafruit_SSD1306 &display);
uint8_t returnLabelCount();
void endDraw(Adafruit_SSD1306 &display);
int8_t select(int8_t position);
~CCMenu();
};

class CRMenu: public Menu{
private:
std::vector<std::shared_ptr<LABEL>> labels_;
uint8_t pointerPos;

public:
CRMenu();
void beginDraw(Adafruit_SSD1306 &display);
void drawMenu(Adafruit_SSD1306 &display);
void createMenu();
void addLabel(int8_t number, std::string text);
void drawPointer(int8_t position, Adafruit_SSD1306 &display);
uint8_t returnLabelCount();
void endDraw(Adafruit_SSD1306 &display);
int8_t select(int8_t position);
~CRMenu();
};

class CPMenu: public Menu{
private:
std::vector<std::shared_ptr<LABEL>> labels_;
uint8_t pointerPos;

public:
CPMenu();
void beginDraw(Adafruit_SSD1306 &display);
void drawMenu(Adafruit_SSD1306 &display);
void createMenu();
void addLabel(int8_t number, std::string text);
void drawPointer(int8_t position, Adafruit_SSD1306 &display);
uint8_t returnLabelCount();
void endDraw(Adafruit_SSD1306 &display);
int8_t select(int8_t position);
~CPMenu();
};


class mainMenu{
private:
std::vector<std::shared_ptr<Menu>> menus_;

uint8_t pointerPos_;

public:
mainMenu();
void beginDraw(Adafruit_SSD1306 &display);
void drawMenu(Adafruit_SSD1306 &display, uint8_t selected);
void createMenu();
void getPointer(int8_t position);
void endDraw(Adafruit_SSD1306 &display);
int8_t select(int8_t position);
~mainMenu();
};
