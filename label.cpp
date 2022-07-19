#include "menu.h"

LABEL::LABEL(int8_t number, std::string text):number_(number),text_(text){

}

void LABEL::setText(std::string string){
text_=string;
}

void LABEL::setNumber(int8_t number){
number_=number;
}

LABEL::~LABEL(){
    
}