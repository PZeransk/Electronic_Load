#include "menu.h"


CCMenu::CCMenu(){
addLabel(1,"Set Current");
addLabel(2,"Set Time");
addLabel(3,"Start");
addLabel(4,"Back");
pointerPos=0;
}

void CCMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void CCMenu::drawMenu(Adafruit_SSD1306 &display){


display.setTextSize(1);
display.setTextColor(WHITE);

for(int i=0;i<labels_.size();i++){
display.setCursor(10, i*10);
display.println(labels_[i]->getText().c_str());
}

}
 

void CCMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


void CCMenu::createMenu(){

}

void CCMenu::drawPointer(int8_t position, Adafruit_SSD1306 &display){
display.drawRect(0, (position%labels_.size())*10, 10, 10, WHITE);

}

uint8_t CCMenu::returnLabelCount(){
    return labels_.size();
}

void CCMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

int8_t CCMenu::select(int8_t position){ // method argument is irrelevant and shall be removed later
return pointerPos;
}

CCMenu::~CCMenu(){
    
}