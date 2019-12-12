#include "IntelliColorPicker.h"
#include "QDebug"

IntelliColorPicker::IntelliColorPicker(PaintingArea* Area)
    :IntelliTool(Area){
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
        this->firstColor = newColor;
        qDebug() << "Firstcolor" << this->firstColor;
    }
    else{
        Titel = "Choose second Color";
        newColor = QColorDialog::getColor(this->secondColor,nullptr,Titel);
        this->secondColor = newColor;
    }
}

QColor IntelliColorPicker::getFirstColor(){
    return firstColor;
}

QColor IntelliColorPicker::getSecondColor(){
    return secondColor;
}
