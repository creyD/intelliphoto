#include "IntelliToolFloodFill.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolFloodFill::IntelliToolFloodFill(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
}

IntelliToolFloodFill::~IntelliToolFloodFill(){

}


void IntelliToolFloodFill::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolFloodFill::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolFloodFill::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->Canvas->image->get
    auto depthsearch = [](int x, int y, LayerObject* Canvas){

    };

    Canvas->image->calculateVisiblity();


}

void IntelliToolFloodFill::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolFloodFill::onWheelScrolled(int value){
    IntelliTool::onWheelScrolled(value);
    this->lineWidth+=value;
    if(this->lineWidth<=0){
        this->lineWidth=1;
    }
}

void IntelliToolFloodFill::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
    if(this->drawing){
        this->Canvas->image->drawPlain(Qt::transparent);
        QPoint next(x,y);
        switch(lineStyle){
            case LineStyle::SOLID_LINE:
                this->Canvas->image->drawLine(start,next,colorPicker->getFirstColor(),lineWidth);
                break;
            case LineStyle::DOTTED_LINE:
                QPoint p1 =start.x() <= next.x() ? start : next;
                QPoint p2 =start.x() < next.x() ? next : start;
                int m = (float)(p2.y()-p1.y())/(float)(p2.x()-p1.x())+0.5f;
                int c = start.y()-start.x()*m;

                break;
        }
    }
    IntelliTool::onMouseMoved(x,y);
}
