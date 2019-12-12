#include "IntelliToolPlain.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"

IntelliToolPlainTool::IntelliToolPlainTool(PaintingArea* Area)
    :IntelliTool(Area){

    this->color = QColorDialog::getColor(Qt::blue,nullptr,"Flood Fill Color");
}

void IntelliToolPlainTool::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->Canvas->image->floodFill(color);
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
