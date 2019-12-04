#include"Image/IntelliShapedImage.h"
#include"IntelliHelper/IntelliHelper.h"
#include<QPainter>
#include<QRect>
#include<QDebug>

IntelliShapedImage::IntelliShapedImage(int weight, int height)
    :IntelliImage(weight, height){
}

IntelliShapedImage::~IntelliShapedImage(){

}

QImage IntelliShapedImage::getDisplayable(int alpha){
    return getDisplayable(imageData.size());
}

QImage IntelliShapedImage::getDisplayable(const QSize& displaySize, int alpha){
    QImage copy = imageData;
    QPoint startPoint;
    QPoint extrem(0,copy.width()+1);
    for(int y = 0; y<copy.height(); y++){
        extrem.setY(y);
        startPoint.setY(y);
        //traverse through x dircetion
        for(int x=0; x<copy.width(); x++){
            startPoint.setX(x);
            //traverse all edges
            int cutNumberX = 0;
            for(size_t i=0; i<polygonData.size()-1; i++){
                QPoint& start = polygonData[i];
                QPoint& end = polygonData[i+1];
                cutNumberX+=IntelliHelper::hasIntersection(startPoint, extrem, start, end);
            }
            //check if zhe cutNumber is Even -> not in Polygon
            if(!(cutNumberX&1)){
                QColor tmpColor(0,0,0);
                tmpColor.setAlpha(0);
                copy.setPixelColor(startPoint,tmpColor);
            }else{
                QColor clr = copy.pixelColor(x,y);
                clr.setAlpha(alpha);
                copy.setPixelColor(x,y,clr);
            }
        }
    }

    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliShapedImage::setPolygon(const std::vector<QPoint>& polygonData){
    for(auto element:polygonData){
        this->polygonData.push_back(QPoint(element.x(), element.y()));
    }
    return;
}
