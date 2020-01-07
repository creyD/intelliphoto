#include "Image/IntelliShapedImage.h"
#include "IntelliHelper/IntelliHelper.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

IntelliShapedImage::IntelliShapedImage(int weight, int height)
		: IntelliRasterImage(weight, height){
        TypeOfImage = IntelliImage::ImageType::Shaped_Image;
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
        shaped->TypeOfImage = IntelliImage::ImageType::Shaped_Image;
		return shaped;
}

void IntelliShapedImage::calculateVisiblity(){
		if(polygonData.size()<=2) {
				QColor clr;
				for(int y=0; y<imageData.height(); y++) {
						for(int x=0; x<imageData.width(); x++) {
								clr = imageData.pixel(x,y);
								clr.setAlpha(255);
								imageData.setPixelColor(x,y,clr);
						}
				}
				return;
		}
		QColor clr;
		for(int y=0; y<imageData.height(); y++) {
				for(int x=0; x<imageData.width(); x++) {
						QPoint ptr(x,y);
						clr = imageData.pixelColor(x,y);
						bool isInPolygon = IntelliHelper::isInPolygon(triangles, ptr);
						if(isInPolygon) {
								clr.setAlpha(std::min(255, clr.alpha()));
						}else{
								clr.setAlpha(0);
						}
						imageData.setPixelColor(x,y,clr);
				}
		}
}

QImage IntelliShapedImage::getDisplayable(const QSize& displaySize, int alpha){
		QImage copy = imageData;
		for(int y = 0; y<copy.height(); y++) {
				for(int x = 0; x<copy.width(); x++) {
						QColor clr = copy.pixelColor(x,y);
						clr.setAlpha(std::min(alpha,clr.alpha()));
						copy.setPixelColor(x,y, clr);
				}
		}
		return copy.scaled(displaySize,Qt::IgnoreAspectRatio);
}

void IntelliShapedImage::setPolygon(const std::vector<QPoint>& polygonData){
		if(polygonData.size()<3) {
				this->polygonData.clear();
		}else{
				this->polygonData.clear();
				for(auto element:polygonData) {
						this->polygonData.push_back(QPoint(element.x(), element.y()));
				}
				triangles = IntelliHelper::calculateTriangles(polygonData);
		}
		calculateVisiblity();
		return;
}
