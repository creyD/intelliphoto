#include "Image/IntelliRasterImage.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

IntelliRasterImage::IntelliRasterImage(int width, int height, bool fastRendererOn)
        : IntelliImage(width, height, fastRendererOn){
        TypeOfImage = IntelliImage::ImageType::Raster_Image;
        this->fastRenderer = fastRendererOn;
}

IntelliRasterImage::~IntelliRasterImage(){

}

IntelliImage* IntelliRasterImage::getDeepCopy(){
        IntelliRasterImage* raster = new IntelliRasterImage(imageData.width(), imageData.height(), false);
		raster->imageData.fill(Qt::transparent);
        raster->TypeOfImage = IntelliImage::ImageType::Raster_Image;
		return raster;
}

void IntelliRasterImage::calculateVisiblity(){
		// not used in raster image
}

QImage IntelliRasterImage::getDisplayable(int alpha){
		return getDisplayable(imageData.size(), alpha);
}

QImage IntelliRasterImage::getDisplayable(const QSize& displaySize, int alpha){
		QImage copy = imageData;
        if(fastRenderer){
            copy = copy.convertToFormat(QImage::Format_ARGB32);
        }
		for(int y = 0; y<copy.height(); y++) {
				for(int x = 0; x<copy.width(); x++) {
						QColor clr = copy.pixelColor(x,y);
						clr.setAlpha(std::min(alpha, clr.alpha()));
						copy.setPixelColor(x,y, clr);
				}
		}
        if(fastRenderer){
            copy = copy.convertToFormat(QImage::Format_Indexed8);
        }
		return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliRasterImage::setPolygon(const std::vector<QPoint>& polygonData){
		qDebug() << "Raster Image has no polygon data " << polygonData.size() <<"\n";
		return;
}
