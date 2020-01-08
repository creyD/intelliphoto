#include "IntelliToolsettings.h"

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

int IntelliToolsettings::getInnerAlpha(){
    return innerAlpha;
}

IntelliToolsettings::LineStyle IntelliToolsettings::getLinestyle(){
    return Linestyle;
}
