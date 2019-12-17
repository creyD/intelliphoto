#include "IntelliToolPolygon.h"
#include "Layer/PaintingArea.h"
#include <QDebug>
#include <QCursor>

IntelliToolPolygon::IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
    lineWidth = 5;
    isDrawing = false;
    PointIsNearStart = false;
    drawingPoint.setX(0);
    drawingPoint.setY(0);
}

void IntelliToolPolygon::onMouseLeftPressed(int x, int y){
    qDebug() << x << y;
    if(!isDrawing && x > 0 && y > 0){
        isDrawing = true;
        drawingPoint.setX(x);
        drawingPoint.setY(y);
        QPointList.push_back(drawingPoint);
        IntelliTool::onMouseLeftPressed(x,y);
        this->Canvas->image->drawPlain(Qt::transparent);
        this->Canvas->image->drawPoint(QPointList.back(), colorPicker->getFirstColor(), lineWidth);
    }
    else if(isDrawing && isNearStart(x,y,QPointList.front())){
        PointIsNearStart = isNearStart(x,y,QPointList.front());
        this->Canvas->image->drawLine(QPointList.back(), QPointList.front(), colorPicker->getFirstColor(), lineWidth);s
    }
    else if(isDrawing){
        drawingPoint.setX(x);
        drawingPoint.setY(y);
        QPointList.push_back(drawingPoint);
        this->Canvas->image->drawLine(QPointList.operator[](QPointList.size() - 2), QPointList.back(), colorPicker->getFirstColor(), lineWidth);
    }
}

void IntelliToolPolygon::onMouseRightPressed(int x, int y){
    isDrawing = false;
    PointIsNearStart = false;
    QPointList.clear();
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPolygon::onMouseLeftReleased(int x, int y){
    if(PointIsNearStart && QPointList.size() > 1){
        PointIsNearStart = false;
        isDrawing = false;
        QPointList.clear();
        IntelliTool::onMouseLeftReleased(x,y);
    }
}

void IntelliToolPolygon::onMouseRightReleased(int x, int y){

}

void IntelliToolPolygon::onWheelScrolled(int value){
    if(!isDrawing){
        if(lineWidth + value < 10){
            lineWidth += value;
        }
        if(lineWidth < 1){
            lineWidth = 1;
        }
    }
}

void IntelliToolPolygon::onMouseMoved(int x, int y){

}

bool IntelliToolPolygon::isNearStart(int x, int y, QPoint Startpoint){
    bool isNear = false;
    int StartX = Startpoint.x();
    int StartY = Startpoint.y();
    int valueToNear = 10;

    for(int i = StartX - valueToNear; i < StartX + valueToNear; i++){
        for(int j = StartY - valueToNear; j < StartY + valueToNear; j++){
            if((i == x) && (j == y)){
                isNear = true;
            }
        }
    }
    return isNear;
}
