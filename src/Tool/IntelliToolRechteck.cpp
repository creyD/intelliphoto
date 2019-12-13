#include"IntelliToolRechteck.h"
#include "Layer/PaintingArea.h"
#include "QInputDialog"

IntelliToolRechteck::IntelliToolRechteck(PaintingArea* Area, IntelliColorPicker* colorPicker)
    :IntelliTool(Area, colorPicker){
    this->alphaInner = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 0,0,255,1);
    this->edgeWidth = QInputDialog::getInt(nullptr,"Outer edge width", "Value:", 0,1,255,1);
}

IntelliToolRechteck::~IntelliToolRechteck(){

}

void IntelliToolRechteck::drawRechteck(QPoint otherCornor){
    int xMin = std::min(originCornor.x(), otherCornor.x());
    int xMax = std::max(originCornor.x(), otherCornor.x());

    int yMin = std::min(originCornor.y(), otherCornor.y());
    int yMax = std::max(originCornor.y(), otherCornor.y());

    QColor clr = colorPicker->getSecondColor();
    clr.setAlpha(alphaInner);
    for(int y=yMin; y<=yMax; y++){
        this->Canvas->image->drawLine(QPoint(xMin,y), QPoint(xMax, y), clr, 1);
    }
    this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), edgeWidth);
    this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), edgeWidth);
    this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), edgeWidth);
    this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), edgeWidth);
}

void IntelliToolRechteck::onMouseRightPressed(int x, int y){
    IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolRechteck::onMouseRightReleased(int x, int y){
    IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolRechteck::onMouseLeftPressed(int x, int y){
    IntelliTool::onMouseLeftPressed(x,y);
    this->originCornor=QPoint(x,y);
    drawRechteck(originCornor);
    Canvas->image->calculateVisiblity();
}

void IntelliToolRechteck::onMouseLeftReleased(int x, int y){
    IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolRechteck::onMouseMoved(int x, int y){
    IntelliTool::onMouseMoved(x,y);
    if(this->drawing){
        this->Canvas->image->drawPlain(Qt::transparent);
        QPoint next(x,y);
        drawRechteck(next);
    }
    IntelliTool::onMouseMoved(x,y);
}
