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

void IntelliToolsettings::setLineWidth(int LineWidth){
        lineWidth = LineWidth;
}

int IntelliToolsettings::getInnerAlpha(){
		return this->innerAlpha;
}

void IntelliToolsettings::setInnerAlpha(int innerAlpha){
        this->innerAlpha = innerAlpha;
}

IntelliToolsettings::LineStyle IntelliToolsettings::getLinestyle(){
		return Linestyle;
}
