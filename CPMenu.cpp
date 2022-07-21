#include "menu.h"


CPMenu::CPMenu(){
addLabel(1,"Set Power");
addLabel(2,"Set Time");
addLabel(3,"Start");
addLabel(4,"Back");
pointerPos=0;
}

void CPMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void CPMenu::drawMenu(Adafruit_SSD1306 &display){


display.setTextSize(1);
display.setTextColor(WHITE);

for(int i=0;i<labels_.size();i++){
display.setCursor(10, i*10);
display.println(labels_[i]->getText().c_str());
}

}
 

void CPMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


void CPMenu::createMenu(){

}

void CPMenu::drawPointer(int8_t position, Adafruit_SSD1306 &display){
display.drawRect(0, (position%labels_.size())*10, 10, 10, WHITE);
}

uint8_t CPMenu::returnLabelCount(){
    return labels_.size();
}

void CPMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

int8_t CPMenu::select(int8_t position){
return labels_[position]->getNumber();
}

CPMenu::~CPMenu(){
    
}