#include "menu.h"



mainMenu::mainMenu(){
menus_.push_back(std::make_shared <CCMenu>());
menus_.push_back(std::make_shared <CRMenu>());
menus_.push_back(std::make_shared <CPMenu>());

pointerPos_=0;
}

void mainMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void mainMenu::drawMenu(Adafruit_SSD1306 &display, uint8_t selected){
display.clearDisplay();
menus_[selected]->drawMenu(display);
menus_[selected]->drawPointer(pointerPos_,display);
display.display();
}
 

void mainMenu::createMenu(){

}

void mainMenu::getPointer(int8_t position){
pointerPos_=position;
}



void mainMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

int8_t mainMenu::select(int8_t position){

}

mainMenu::~mainMenu(){
    
}