#include "IntelliColorPicker.h"

IntelliColorPicker::IntelliColorPicker(){
    firstColor = {255,0,0,255};
    secondColor = {0,255,255,255};
}

IntelliColorPicker::~IntelliColorPicker(){

}

void IntelliColorPicker::switchColors(){
    std::swap(firstColor, secondColor);
}

QColor IntelliColorPicker::getFirstColor(){
    return this->firstColor;
}

QColor IntelliColorPicker::getSecondColor(){
    return this->secondColor;
}

void IntelliColorPicker::setFirstColor(QColor Color){
    this->firstColor = Color;
}

void IntelliColorPicker::setSecondColor(QColor Color){
    this->secondColor = Color;
}
