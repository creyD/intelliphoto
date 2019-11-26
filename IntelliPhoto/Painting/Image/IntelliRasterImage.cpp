#include"Image/IntelliRasterImage.h"
#include<QPainter>
#include<QRect>
#include<QDebug>

IntelliRasterimage::IntelliRasterimage(int weight, int height)
    :IntelliImage(weight, height){

}

IntelliRasterimage::~IntelliRasterimage(){

}



QImage IntelliRasterimage::getDisplayable(const QSize& displaySize){
    QImage copy = imageData;
    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliRasterimage::setPolygon(const std::vector<QPoint>& polygonData){
    qDebug() << "Raster Image has no polygon data " << polygonData.size() <<"\n";
    return;
}
