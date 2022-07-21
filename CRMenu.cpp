#include "menu.h"


CRMenu::CRMenu(){
addLabel(1,"Set Resistance");
addLabel(2,"Set Time");
addLabel(3,"Start");
addLabel(4,"Back");
pointerPos=0;
}

void CRMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void CRMenu::drawMenu(Adafruit_SSD1306 &display){


display.setTextSize(1);
display.setTextColor(WHITE);

for(int i=0;i<labels_.size();i++){
display.setCursor(10, i*10);
display.println(labels_[i]->getText().c_str());
}

}
 

void CRMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


void CRMenu::createMenu(){

}

void CRMenu::drawPointer(int8_t position, Adafruit_SSD1306 &display){
display.drawRect(0, (position%labels_.size())*10, 10, 10, WHITE);
}

uint8_t CRMenu::returnLabelCount(){
    return labels_.size();
}

void CRMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

int8_t CRMenu::select(int8_t position){
return labels_[position]->getNumber();
}

CRMenu::~CRMenu(){
    
}