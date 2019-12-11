#include "IntelliToolFloodFillTool.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"

IntelliToolFloodFillTool::IntelliToolFloodFillTool(PaintingArea* Area)
    :IntelliTool(Area){

    this->color = QColorDialog::getColor(Qt::blue,nullptr,"Flood Fill Color");
}

void IntelliToolFloodFillTool::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->Canvas->image->floodFill(color);
}

void IntelliToolFloodFillTool::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolFloodFillTool::onMouseRightReleased(int x, int y){
     IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolFloodFillTool::onMouseLeftReleased(int x, int y){
     IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolFloodFillTool::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
}
