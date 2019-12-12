#include "IntelliToolPen.h"
#include "Layer/PaintingArea.h"
#include "QDebug"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolPen::IntelliToolPen(PaintingArea* Area)
    :IntelliTool(Area){
    this->color = QColorDialog::getColor(Qt::blue,nullptr,"Flood Fill Color");
    this->penWidth = QInputDialog::getInt(nullptr, "Pen width", "Number:", 1,0, 50, 1);
}

IntelliToolPen::~IntelliToolPen(){

}

void IntelliToolPen::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPen::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolPen::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->point=QPoint(x,y);
}

void IntelliToolPen::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolPen::onMouseMoved(int x, int y){
    if(this->drawing){
        QPoint newPoint(x,y);
        this->Canvas->image->drawLine(this->point, newPoint, color, penWidth);
        this->point=newPoint;
    }
}
