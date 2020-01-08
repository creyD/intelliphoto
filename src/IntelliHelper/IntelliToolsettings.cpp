#include "IntelliToolsettings.h"

IntelliToolsettings::IntelliToolsettings()
{
    lineWidth = 1;
    innerAlpha = 255;
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
