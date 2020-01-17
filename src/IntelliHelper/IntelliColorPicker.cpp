#include "IntelliColorPicker.h"

IntelliColorPicker::IntelliColorPicker(){
		initializeColors();
}

IntelliColorPicker::~IntelliColorPicker(){

}

void IntelliColorPicker::swapColors(){
		std::swap(firstColor, secondColor);
}

QColor IntelliColorPicker::getFirstColor() const {
		return this->firstColor;
}

QColor IntelliColorPicker::getSecondColor() const {
		return this->secondColor;
}

void IntelliColorPicker::setFirstColor(QColor Color){
		this->firstColor = Color;
}

void IntelliColorPicker::setSecondColor(QColor Color){
		this->secondColor = Color;
}

void IntelliColorPicker::initializeColors(){
		this->firstColor = QColor(255,0,0,255);
		this->secondColor =  QColor(0,0,0,255);
}
