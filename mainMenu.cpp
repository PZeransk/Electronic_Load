#include "menu.h"


mainMenu::mainMenu(){
addLabel(1,"CC");
addLabel(2,"Const Power");
addLabel(3,"Resistance");
addLabel(4,"Capacity");
addLabel(5,"Capacity");
addLabel(6,"Capacity");
pointerPos=0;
}

void mainMenu::beginDraw(Adafruit_SSD1306 &display){
display.clearDisplay();
}

void mainMenu::drawMenu(Adafruit_SSD1306 &display){


display.setTextSize(1);
display.setTextColor(WHITE);

for(int i=0;i<labels_.size();i++){
display.setCursor(10, i*10);
display.println(labels_[i]->getText().c_str());
}

}
 

void mainMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


void mainMenu::createMenu(){

}

void mainMenu::drawPointer(int8_t position, Adafruit_SSD1306 &display){


/*
if(position>0){


if(pointerPos>labels_.size())
    pointerPos=0;

if(pointerPos>=0 && pointerPos<labels_.size()){          
    display.drawRect(0, pointerPos*10, 10, 10, WHITE);
    pointerPos++; 
}


}else if(position<0){

    if(pointerPos<=0)
    pointerPos=labels_.size()-1;

    if(pointerPos>0 && pointerPos<labels_.size()){
                       
        display.drawRect(0, pointerPos*10, 10, 10, WHITE);
        pointerPos--; 
        
    }





}
*/
display.drawRect(0, (position%labels_.size())*10, 10, 10, WHITE);
}

uint8_t mainMenu::returnLabelCount(){
    return labels_.size();
}

void mainMenu::endDraw(Adafruit_SSD1306 &display){
display.display();
}

mainMenu::~mainMenu(){
    
}