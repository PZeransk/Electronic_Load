#include "menu.h"


mainMenu::mainMenu(){

}

void mainMenu::drawMenu(){

}


void mainMenu::addLabel(int8_t number, std::string text){
labels_.push_back(std::make_shared <LABEL>(number,text));
}


mainMenu::~mainMenu(){
    
}