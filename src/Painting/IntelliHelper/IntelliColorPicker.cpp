#include "IntelliColorPicker.h"

IntelliColorPicker::IntelliColorPicker(PaintingArea* Area){
    firstColor = {255,0,0,255};
    secondColor = {0,0,255,255};
}

IntelliColorPicker::~IntelliColorPicker(){

}

void IntelliColorPicker::getColorbar(int firstOrSecondColor = 1){
    QString Titel;
    QColor newColor;
    if(firstOrSecondColor == 1){
        Titel = "Choose first Color";
        newColor = QColorDialog::getColor(this->firstColor,nullptr,Titel);
        setFirstColor(newColor);
    }
    else{
        Titel = "Choose second Color";
        newColor = QColorDialog::getColor(this->secondColor,nullptr,Titel);
        setFirstColor(newColor);
    }
}

void IntelliColorPicker::switchColors(){
    QColor temp = this->firstColor;
    this->firstColor = this->secondColor;
    this->secondColor = temp;
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
