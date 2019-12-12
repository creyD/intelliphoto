#include "IntelliToolPlain.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"

IntelliToolPlainTool::IntelliToolPlainTool(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
}

void IntelliToolPlainTool::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->Canvas->image->drawPlain(colorPicker->getFirstColor());
    Canvas->image->calculateVisiblity();
}

void IntelliToolPlainTool::onMouseLeftReleased(int x, int y){
     IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolPlainTool::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPlainTool::onMouseRightReleased(int x, int y){
     IntelliTool::onMouseRightReleased(x,y);
}


void IntelliToolPlainTool::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
}
