#include "IntelliToolLine.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolLine::IntelliToolLine(PaintingArea* Area)
    :IntelliTool(Area){
    this->color = QColorDialog::getColor(Qt::blue, nullptr, "Line Color");
    this->lineWidth = QInputDialog::getInt(nullptr,"Line Width Input", "Width",1,1,50,1);
    //create checkbox or scroll dialog to get line style
    this->lineStyle = LineStyle::SOLID_LINE;
}

IntelliToolLine::~IntelliToolLine(){

}


void IntelliToolLine::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolLine::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolLine::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->start=QPoint(x,y);
    this->Canvas->image->drawLine(start, start, this->color, this->lineWidth);
}

void IntelliToolLine::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolLine::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
    if(this->drawing){
        this->Canvas->image->floodFill(Qt::transparent);
        QPoint next(x,y);
        switch(lineStyle){
            case LineStyle::SOLID_LINE :
                this->Canvas->image->drawLine(start,next,color,lineWidth);
                break;
        }
    }

}
