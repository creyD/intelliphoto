#include"Image/IntelliShapedImage.h"
#include"IntelliHelper/IntelliHelper.h"
#include<QPainter>
#include<QRect>
#include<QDebug>

IntelliShapedImage::IntelliShapedImage(int weight, int height)
    :IntelliRasterImage(weight, height){
}

IntelliShapedImage::~IntelliShapedImage(){

}

QImage IntelliShapedImage::getDisplayable(int alpha){
    return getDisplayable(imageData.size(),alpha);
}

IntelliImage* IntelliShapedImage::getDeepCopy(){
    IntelliShapedImage* shaped = new IntelliShapedImage(imageData.width(), imageData.height());
    shaped->setPolygon(this->polygonData);
    shaped->imageData.fill(Qt::transparent);
    return shaped;
}

void IntelliShapedImage::calculateVisiblity(){
    if(polygonData.size()<=2){
        QColor clr;
        for(int y=0; y<imageData.height(); y++){
            for(int x=0; x<imageData.width(); x++){
                clr = imageData.pixel(x,y);
                clr.setAlpha(255);
                imageData.setPixelColor(x,y,clr);
            }
        }
        return;
    }
    QPoint A = polygonData[0];
    QColor clr;
    for(int y=0; y<imageData.height(); y++){
        for(int x=0; x<imageData.width(); x++){
            int cutNumeber=0;
            for(int i=1; i<static_cast<int>(polygonData.size()-1); i++){
                QPoint B = polygonData[static_cast<size_t>(i)];
                QPoint C = polygonData[static_cast<size_t>(i+1)];
                QPoint P(x,y);
                cutNumeber+=IntelliHelper::isInTriangle(A,B,C,P);
            }
            if(cutNumeber%2==0){
                clr = imageData.pixelColor(x,y);
                clr.setAlpha(0);
                imageData.setPixelColor(x,y,clr);
            }else{
                clr = imageData.pixelColor(x,y);
                clr.setAlpha(std::min(255, clr.alpha()));
                imageData.setPixelColor(x,y,clr);
            }
        }
    }
}

QImage IntelliShapedImage::getDisplayable(const QSize& displaySize, int alpha){
    QImage copy = imageData;
    for(int y = 0; y<copy.height(); y++){
        for(int x = 0; x<copy.width(); x++){
            QColor clr = copy.pixelColor(x,y);
            clr.setAlpha(std::min(alpha,clr.alpha()));
            copy.setPixelColor(x,y, clr);
        }
    }
    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliShapedImage::setPolygon(const std::vector<QPoint>& polygonData){
    if(polygonData.size()<3){
        this->polygonData.clear();
    }else{
        this->polygonData.clear();
        for(auto element:polygonData){
            this->polygonData.push_back(QPoint(element.x(), element.y()));
        }
    }
    calculateVisiblity();
    return;
}
