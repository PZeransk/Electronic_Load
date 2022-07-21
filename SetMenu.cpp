#include "menu.h"


SetMenu::SetMenu(std::string Unit):Unit_(Unit){
addLabel(0,"");
addLabel(0,"");
addLabel(0,"");
addLabel(0,"");
pointerPos=0;
}

void SetMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void SetMenu::drawMenu(Adafruit_SSD1306 &display){


display.setTextSize(1);
display.setTextColor(WHITE);

for(int i=0;i<labels_.size();i++){
display.setCursor(i*10, 10);
display.println(labels_[i]->getNumber());
}

display.setCursor(labels_.size()*10, 10);
display.println(Unit_.c_str());

}
 

void SetMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


void SetMenu::createMenu(){

}

void SetMenu::drawPointer(int8_t position, Adafruit_SSD1306 &display){
display.drawRect(0, (position%labels_.size())*10, 10, 10, WHITE);
}

uint8_t SetMenu::returnLabelCount(){
    return labels_.size();
}

void SetMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

int8_t SetMenu::select(int8_t position){
return labels_[position]->getNumber();
}

SetMenu::~SetMenu(){
    
}