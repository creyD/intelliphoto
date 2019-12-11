#include "IntelliToolPen.h"
#include "Layer/PaintingArea.h"
#include "QDebug"

IntelliToolPen::IntelliToolPen(PaintingArea* Area)
    :IntelliToolSetColorTool(Area){

}

IntelliToolPen::~IntelliToolPen(){

}

void IntelliToolPen::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
    //implement in here
}

void IntelliToolPen::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
    //implemnt in here
}

void IntelliToolPen::onMouseLeftPressed(int x, int y){
    //implement in here
    IntelliTool::onMouseLeftPressed(x,y);
    this->point=QPoint(x,y);
}

void IntelliToolPen::onMouseLeftReleased(int x, int y){
    //implement in here
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolPen::onMouseMoved(int x, int y){
    if(this->drawing){
        QPoint newPoint(x,y);
        Tool = Area->getTool();
        qDebug() << Tool->getFirstColor();
        this->Canvas->image->drawLine(this->point, newPoint, Tool->getFirstColor(), 2);
        this->point=newPoint;
    }
}
