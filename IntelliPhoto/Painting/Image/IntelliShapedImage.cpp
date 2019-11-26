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


QImage IntelliShapedImage::getDisplayable(const QSize& displaySize){
    QImage copy = imageData;
    QPoint extrem(copy.width()+1, 0);
    QPoint startPoint(0,0);
    //traverse through y direction
    for(int y = 0; y<copy.height(); y++){
        extrem.setY(y);
        startPoint.setY(y);
        //traverse through x dircetion
        for(int x=0; x<copy.width(); x++){
            startPoint.setX(x);
            //traverse all edges
            int cutNumber = 0;
            for(size_t i=0; i<polygonData.size()-1; i++){
                QPoint& start = polygonData[i];
                QPoint& end = polygonData[i+1];
                cutNumber += IntelliHelper::hasIntersection(startPoint, extrem, start, end);
            }
            //check if zhe cutNumber is Even -> not in Polygon
            if(!(cutNumber&1)){
                QColor tmpColor(copy.color(y*copy.width()+x));
                tmpColor.setAlpha(0);
                copy.setPixelColor(startPoint,tmpColor);
            }
        }
    }
    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliShapedImage::setPolygon(const std::vector<QPoint>& polygonData){
    this->polygonData=polygonData;
    return;
}
