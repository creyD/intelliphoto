#include "Image/IntelliRasterImage.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

IntelliRasterImage::IntelliRasterImage(int width, int height, bool fastRendererOn)
		: IntelliImage(width, height, fastRendererOn){
		TypeOfImage = ImageType::RASTERIMAGE;
		this->fastRenderering = fastRendererOn;
}


IntelliRasterImage* IntelliRasterImage::copy(const IntelliRasterImage& image){
		this->TypeOfImage = ImageType::RASTERIMAGE;
		IntelliRasterImage* raster = new IntelliRasterImage(imageData.width(), imageData.height(), this->fastRenderering);
		raster->imageData.copy(0,0,image.getWidth(),image.getWidth());
		return raster;
}


IntelliRasterImage::~IntelliRasterImage(){

}

IntelliImage* IntelliRasterImage::getDeepCopy(){
        IntelliRasterImage* raster = new IntelliRasterImage(imageData.width(), imageData.height(), false);
		raster->imageData.fill(Qt::transparent);
		raster->TypeOfImage = ImageType::RASTERIMAGE;
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
		if(fastRenderering) {
				copy = copy.convertToFormat(QImage::Format_ARGB32);
		}
		for(int y = 0; y<copy.height(); y++) {
				for(int x = 0; x<copy.width(); x++) {
						QColor clr = copy.pixelColor(x,y);
						clr.setAlpha(std::min(alpha, clr.alpha()));
						copy.setPixelColor(x,y, clr);
				}
		}
		if(fastRenderering) {
				copy = copy.convertToFormat(QImage::Format_Indexed8);
		}
		return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliRasterImage::setPolygon(const std::vector<QPoint>& polygonData){
		return;
}

std::vector<QPoint> IntelliRasterImage::getPolygon(){
		return std::vector<QPoint>();
}
