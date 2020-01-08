#include "IntelliToolsettings.h"
#include <QInputDialog>

IntelliToolsettings::IntelliToolsettings()
{
    lineWidth = 1;
    innerAlpha = 255;
    Linestyle = LineStyle::SOLID_LINE;
}

IntelliToolsettings::~IntelliToolsettings(){

}

int IntelliToolsettings::getLineWidth(){
    return lineWidth;
}

void IntelliToolsettings::setLineWidth(){
    lineWidth = QInputDialog::getInt(nullptr,"Line Width Input", "Width",1,1,50,1);
}

void IntelliToolsettings::setLineWidth(int LineWidth){
    if(LineWidth < 1){
        LineWidth = 1;
    }
    else if(LineWidth > 50){
        LineWidth = 50;
    }
    lineWidth = LineWidth;
}

int IntelliToolsettings::getInnerAlpha(){
    return this->innerAlpha;
}

void IntelliToolsettings::setInnerAlpha(){
    this->innerAlpha = QInputDialog::getInt(nullptr,"Inner Aplha Input", "Value",0,0,255,1);
}

void IntelliToolsettings::setInnerAlpha(int innerAlpha){
    if(innerAlpha < 0){
        innerAlpha = 0;
    }
    else if(innerAlpha > 255){
        innerAlpha = 255;
    }
    this->innerAlpha = innerAlpha;
}

IntelliToolsettings::LineStyle IntelliToolsettings::getLinestyle(){
    return Linestyle;
}
