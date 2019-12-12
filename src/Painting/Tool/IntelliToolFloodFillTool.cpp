#include "IntelliToolFloodFillTool.h"
#include "Layer/PaintingArea.h"

IntelliToolFloodFillTool::IntelliToolFloodFillTool(PaintingArea* Area)
    :IntelliTool(Area)
{
    Tool = Area->getColorTool();
    isPressed = false;
}

void IntelliToolFloodFillTool::onMouseLeftPressed(int x, int y){
    if(!isPressed){
        isPressed = true;
        IntelliTool::onMouseLeftPressed(x,y);
        Tool = Area->getColorTool();
        this->Canvas->image->floodFill(Tool->getFirstColor());
    }
}

void IntelliToolFloodFillTool::onMouseRightPressed(int x, int y){
    if(!isPressed){
        isPressed = true;
        IntelliTool::onMouseLeftPressed(x,y);
        Tool = Area->getColorTool();
        this->Canvas->image->floodFill(Tool->getSecondColor());
    }
}

void IntelliToolFloodFillTool::onMouseRightReleased(int x, int y){
     IntelliTool::onMouseLeftReleased(x,y);
     if(isPressed) isPressed = false;
}

void IntelliToolFloodFillTool::onMouseLeftReleased(int x, int y){
     IntelliTool::onMouseLeftReleased(x,y);
     if(isPressed) isPressed = false;
}

void IntelliToolFloodFillTool::onMouseMoved(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}
