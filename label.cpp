#include "menu.h"

LABEL::LABEL(int8_t number, std::string text):number_(number),text_(text){

}

void LABEL::setText(std::string string){
text_=string;
}

std::string LABEL::getText(){
    return text_;
}

void LABEL::setNumber(int8_t number){
number_=number;
}

int8_t LABEL::getNumber(){
    return number_;
}

LABEL::~LABEL(){
    
}
