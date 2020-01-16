#include "IntelliToolsettings.h"
#include <QInputDialog>

IntelliToolsettings::IntelliToolsettings()
{
		lineWidth = 1;
		innerAlpha = 255;
}

IntelliToolsettings::~IntelliToolsettings(){

}

int IntelliToolsettings::getLineWidth(){
		return lineWidth;
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

void IntelliToolsettings::setInnerAlpha(int innerAlpha){
        if(innerAlpha < 0){
            innerAlpha = 0;
        }
        else if(innerAlpha > 255){
            innerAlpha = 255;
        }
        this->innerAlpha = innerAlpha;
}
