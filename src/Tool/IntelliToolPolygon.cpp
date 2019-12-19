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
    Point.setX(0);
    Point.setY(0);
}

void IntelliToolPolygon::onMouseLeftPressed(int x, int y){
    if(!isDrawing){
        width = Area->getWidthActiveLayer();
        height = Area->getHeightActiveLayer();
    }
    if(!isDrawing && x > 0 && y > 0 && x < width && y < height){
        isDrawing = true;
        drawingPoint.setX(x);
        drawingPoint.setY(y);
        QPointList.push_back(drawingPoint);
        IntelliTool::onMouseLeftPressed(x,y);
        this->Canvas->image->drawPlain(Qt::transparent);
        this->Canvas->image->drawPoint(QPointList.back(), colorPicker->getFirstColor(), lineWidth);
        this->Canvas->image->calculateVisiblity();
    }
    else if(isDrawing && isNearStart(x,y,QPointList.front())){
        PointIsNearStart = isNearStart(x,y,QPointList.front());
        this->Canvas->image->drawLine(QPointList.back(), QPointList.front(), colorPicker->getFirstColor(), lineWidth);
        this->Canvas->image->calculateVisiblity();
    }
    else if(isDrawing){
        drawingPoint.setX(x);
        drawingPoint.setY(y);
        QPointList.push_back(drawingPoint);
        this->Canvas->image->drawLine(QPointList.operator[](QPointList.size() - 2), QPointList.back(), colorPicker->getFirstColor(), lineWidth);
        this->Canvas->image->calculateVisiblity();
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
        this->Canvas->image->calculateVisiblity();
        PointIsNearStart = false;
        isDrawing = false;
        Triangles = IntelliHelper::calculateTriangles(QPointList);
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                Point.setX(i);
                Point.setY(j);
                if(IntelliHelper::isInPolygon(Triangles,Point)){
                    this->Canvas->image->drawPixel(QPoint(i,j), colorPicker->getFirstColor());
                }
            }
        }
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
