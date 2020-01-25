#include "IntelliToolGradient.h"
#include <QDebug>

IntelliToolGradient::IntelliToolGradient(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings)
        : IntelliTool(Area, colorPicker, Toolsettings){
        this->LineColor = QColor(0,0,0,255);
        this->hasMoved = false;

        A = QPoint(0,0);
        B = QPoint(0,3);
        VectorAB = QPoint(0,3);
        computePixelColor(QPoint(2,1));
}

IntelliToolGradient::~IntelliToolGradient(){
        IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolGradient::onMouseLeftPressed(int x, int y){
        IntelliTool::onMouseLeftPressed(x,y);
        A = QPoint(x,y);
        B = QPoint(x,y);
        VectorAB = QPoint(0,0);
        //Canvas->image->drawPlain(colorPicker->getFirstColor);
        //Canvas->image->drawPixel(A,LineColor);
}

void IntelliToolGradient::onMouseRightPressed(int x, int y){
        IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolGradient::onMouseLeftReleased(int x, int y){
        if(!hasMoved && A != B){
            //Canvas->image->drawPlain(colorPicker->getFirstColor);
        }
        IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolGradient::onMouseRightReleased(int x, int y){
        IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolGradient::onMouseMoved(int x, int y){
        hasMoved = true;
        B = QPoint(x,y);
        IntelliTool::onMouseMoved(x,y);
}

void IntelliToolGradient::onWheelScrolled(int value){
        IntelliTool::onWheelScrolled(value);
}

void IntelliToolGradient::computePixelColor(QPoint Point){
        QPoint NormalVector = QPoint(VectorAB.y(),(-1*VectorAB.x()));
        Point = Point - (dotProduct((Point - A),NormalVector) / dotProduct(NormalVector,NormalVector)) * NormalVector;
        qDebug() << Point.y();
}

float IntelliToolGradient::dotProduct(QPoint Vector1, QPoint Vector2){
        return static_cast<float>(Vector1.x()*Vector2.x()+Vector1.y()*Vector2.y());
}
