#include "IntelliToolGradient.h"
#include "Layer/PaintingArea.h"
#include "math.h"
#include <QDebug>

IntelliToolGradient::IntelliToolGradient(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings)
        : IntelliTool(Area, colorPicker, Toolsettings){
        this->ActiveType = Tooltype::GRADIENT;
        this->LineColor = QColor(0,0,0,255);
        this->hasMoved = false;
}

IntelliToolGradient::~IntelliToolGradient(){
        IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolGradient::onMouseLeftPressed(int x, int y){
        IntelliTool::onMouseLeftPressed(x,y);
        startPoint_double[0] = static_cast<double>(x);
        startPoint_double[1] = static_cast<double>(y);
        startPoint = QPoint(x,y);
        endPoint = QPoint(x,y);
        endPoint_double[0] = 0;
        endPoint_double[1] = 0;
        Canvas->image->drawPixel(startPoint,LineColor);
}

void IntelliToolGradient::onMouseRightPressed(int x, int y){
        IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolGradient::onMouseLeftReleased(int x, int y){
        if(hasMoved && this->isDrawing){
            computeGradientLayer();
            IntelliTool::onMouseLeftReleased(x,y);
        }
}

void IntelliToolGradient::onMouseRightReleased(int x, int y){
        IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolGradient::onMouseMoved(int x, int y){
        if(this->isDrawing){
            hasMoved = true;
            endPoint = QPoint(x,y);
            endPoint_double[0] = static_cast<float>(endPoint.x() - startPoint.x());
            endPoint_double[1] = static_cast<float>(endPoint.y() - startPoint.y());
            NormalVector[0] = endPoint_double[1];
            NormalVector[1] = (-1*endPoint_double[0]);
            NormalDotNormal = dotProduct(NormalVector,NormalVector);
            this->Canvas->image->drawPlain(Qt::transparent);
            computeGradientLayer();
            Canvas->image->drawLine(startPoint,endPoint,LineColor,1);
        }
        IntelliTool::onMouseMoved(x,y);
}

void IntelliToolGradient::onWheelScrolled(int value){
        IntelliTool::onWheelScrolled(value);
}

void IntelliToolGradient::computeAndDrawPixelColor(QPoint Point){
        double doublePoint[2];
        doublePoint[0] = static_cast<double>(Point.x());
        doublePoint[1] = static_cast<double>(Point.y());
        double doublePointSubA[2];
        doublePointSubA[0] = doublePoint[0] - startPoint_double[0];
        doublePointSubA[1] = doublePoint[1] - startPoint_double[1];
        double Perpendicular[2];
        double PointSubADotNormal = dotProduct(doublePointSubA,NormalVector);
        Perpendicular[0] = doublePoint[0] - (PointSubADotNormal / NormalDotNormal) * NormalVector[0];
        Perpendicular[1] = doublePoint[1] - (PointSubADotNormal / NormalDotNormal) * NormalVector[1];
        double VectorAPoint[2];
        VectorAPoint[0] = static_cast<double>(Perpendicular[0] - startPoint_double[0]);
        VectorAPoint[1] = static_cast<double>(Perpendicular[1] - startPoint_double[1]);
        double ratio;
        if(((VectorAPoint[0] < 0 && endPoint_double[0] < 0) || (VectorAPoint[0] > 0 && endPoint_double[0] > 0)) && ((VectorAPoint[1] < 0 && endPoint_double[1] < 0) || (VectorAPoint[1] > 0 && endPoint_double[1] > 0)))
               ratio = lenghtVector(VectorAPoint)/lenghtVector(endPoint_double);
        else{
               ratio = -1;
        }
        QColor computedColor;
        if(ratio < 0){
            computedColor = colorPicker->getFirstColor();
        }
        else if(ratio > 1){
            computedColor = colorPicker->getSecondColor();
        }
        else{
            int red;
            int green;
            int blue;
            int alpha;
            int red2;
            int green2;
            int blue2;
            int alpha2;
            colorPicker->getFirstColor().getRgb(&red,&green,&blue,&alpha);
            colorPicker->getSecondColor().getRgb(&red2,&green2,&blue2,&alpha2);
            computedColor.setRed(static_cast<int>(ratio * red2 + (1 - ratio) * red));
            computedColor.setGreen(static_cast<int>(ratio * green2 + (1 - ratio) * green));
            computedColor.setBlue(static_cast<int>(ratio * blue2 + (1 - ratio) * blue));
            computedColor.setAlpha(static_cast<int>(ratio * alpha2 + (1 - ratio) * alpha));
        }
        Canvas->image->drawPixel(Point,computedColor);
}

double IntelliToolGradient::dotProduct(double Vector1[2], double Vector2[2]){
        return static_cast<double>(Vector1[0]*Vector2[0]+Vector1[1]*Vector2[1]);
}

double IntelliToolGradient::lenghtVector(double Vector[2]){
        return static_cast<double>((sqrt(Vector[0] * Vector[0] + Vector[1] * Vector[1])));
}

void IntelliToolGradient::computeGradientLayer(){
    bool switched = false;
    if(Canvas->image->isFastRendering()){
        switched = true;
        Canvas->image->updateRendererSetting(false);
    }
    for(int i = 0; i < activeLayer->height; i++){
        for(int j = 0; j < activeLayer->width; j++){
            computeAndDrawPixelColor(QPoint(j,i));
        }
    }
    if(switched){
        Canvas->image->updateRendererSetting(true);
    }
}
