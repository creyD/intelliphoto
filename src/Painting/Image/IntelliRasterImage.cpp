#include"Image/IntelliRasterImage.h"
#include<QPainter>
#include<QRect>
#include<QDebug>

IntelliRasterImage::IntelliRasterImage(int weight, int height)
    :IntelliImage(weight, height){

}

IntelliRasterImage::~IntelliRasterImage(){

}

QImage IntelliRasterImage::getDisplayable(int alpha){
    return getDisplayable(imageData.size(), alpha);
}

QImage IntelliRasterImage::getDisplayable(const QSize& displaySize, int alpha){
    QImage copy = imageData;
    for(int y = 0; y<copy.height(); y++){
        for(int x = 0; x<copy.width(); x++){
            QColor clr = copy.pixelColor(x,y);
            clr.setAlpha(alpha);
            copy.setPixelColor(x,y, clr);
        }
    }
    return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliRasterImage::setPolygon(const std::vector<QPoint>& polygonData){
    qDebug() << "Raster Image has no polygon data " << polygonData.size() <<"\n";
    return;
}
