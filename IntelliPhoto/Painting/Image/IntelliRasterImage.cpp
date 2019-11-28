#include"Image/IntelliRasterImage.h"
#include<QPainter>
#include<QRect>
#include<QDebug>

IntelliRasterImage::IntelliRasterImage(int weight, int height)
    :IntelliImage(weight, height){

}

IntelliRasterImage::~IntelliRasterImage(){

}

QImage IntelliRasterImage::getDisplayable(){
    return getDisplayable(imageData.size());
}

QImage IntelliRasterImage::getDisplayable(const QSize& displaySize){
    QImage copy = imageData;
    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliRasterImage::setPolygon(const std::vector<QPoint>& polygonData){
    qDebug() << "Raster Image has no polygon data " << polygonData.size() <<"\n";
    return;
}
