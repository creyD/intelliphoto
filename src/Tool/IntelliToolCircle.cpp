#include "IntelliToolCircle.h"
#include "Layer/PaintingArea.h"
#include "QInputDialog"
#include <cmath>

IntelliToolCircle::IntelliToolCircle(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
    this->alphaInner = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 0,0,255,1);
    this->edgeWidth = QInputDialog::getInt(nullptr,"Outer edge width", "Value:", 0,1,255,1);
}

IntelliToolCircle::~IntelliToolCircle(){

}

void IntelliToolCircle::drawCyrcle(int radius){
    int outer = radius+20;
    QColor inner = this->colorPicker->getSecondColor();
    inner.setAlpha(alphaInner);
    int yMin, yMax, xMin, xMax;
    yMin = Middle.y()-radius;
    yMax = Middle.y()+radius;
    // x = x0+-sqrt(r2-(y-y0)2)
    for(int i=yMin; i<=yMax; i++){
        xMin = Middle.x()-sqrt(pow(radius,2)-pow(i-Middle.y(),2));
        xMax = Middle.x()+sqrt(pow(radius,2)-pow(i-Middle.y(),2));
        this->Canvas->image->drawLine(QPoint(xMin,i), QPoint(xMax,i),inner,1);
    }

    //TODO implement circle drawing algorithm bresenham
    radius = radius +(this->edgeWidth/2.)-1.;
    yMin = (Middle.y()-radius);
    yMax = (Middle.y()+radius);
    for(int i=yMin; i<=yMax; i++){
        xMin = Middle.x()-sqrt(pow(radius,2)-pow(i-Middle.y(),2));
        xMax = Middle.x()+sqrt(pow(radius,2)-pow(i-Middle.y(),2));
        this->Canvas->image->drawPoint(QPoint(xMin,i), colorPicker->getFirstColor(),edgeWidth);
        this->Canvas->image->drawPoint(QPoint(xMax,i), colorPicker->getFirstColor(),edgeWidth);
    }

    xMin = (Middle.x()-radius);
    xMax = (Middle.x()+radius);
    for(int i=xMin; i<=xMax; i++){
        int yMin = Middle.y()-sqrt(pow(radius,2)-pow(i-Middle.x(),2));
        int yMax = Middle.y()+sqrt(pow(radius,2)-pow(i-Middle.x(),2));
        this->Canvas->image->drawPoint(QPoint(i, yMin), colorPicker->getFirstColor(),edgeWidth);
        this->Canvas->image->drawPoint(QPoint(i, yMax), colorPicker->getFirstColor(),edgeWidth);
    }
}

void IntelliToolCircle::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolCircle::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolCircle::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->Middle=QPoint(x,y);
    int radius = 1;
    drawCyrcle(radius);
    Canvas->image->calculateVisiblity();
}

void IntelliToolCircle::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolCircle::onWheelScrolled(int value){
    IntelliTool::onWheelScrolled(value);
    this->edgeWidth+=value;
    if(this->edgeWidth<=0){
        this->edgeWidth=1;
    }
}

void IntelliToolCircle::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
    if(this->drawing){
        this->Canvas->image->drawPlain(Qt::transparent);
        QPoint next(x,y);
        int radius = static_cast<int>(sqrt(pow((Middle.x()-x),2)+pow((Middle.y()-y),2)));
        drawCyrcle(radius);
    }
    IntelliTool::onMouseMoved(x,y);
}
