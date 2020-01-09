#include "Image/IntelliShapedImage.h"
#include "IntelliHelper/IntelliTriangulation.h"
#include <QPainter>
#include <QRect>
#include <QDebug>

IntelliShapedImage::IntelliShapedImage(int width, int height, bool fastRendererOn)
        : IntelliRasterImage(width, height, fastRendererOn){
        TypeOfImage = IntelliImage::ImageType::SHAPEDIMAGE;
        this->fastRenderering = fastRendererOn;
}

IntelliShapedImage::~IntelliShapedImage(){

}

QImage IntelliShapedImage::getDisplayable(int alpha){
		return getDisplayable(imageData.size(),alpha);
}

IntelliImage* IntelliShapedImage::getDeepCopy(){
        IntelliShapedImage* shaped = new IntelliShapedImage(imageData.width(), imageData.height(), false);
		shaped->setPolygon(this->polygonData);
		shaped->imageData.fill(Qt::transparent);
		shaped->TypeOfImage = IntelliImage::ImageType::SHAPEDIMAGE;
		return shaped;
}

void IntelliShapedImage::calculateVisiblity(){
        if(fastRenderering){
            this->imageData = imageData.convertToFormat(QImage::Format_ARGB32);
        }

        if(polygonData.size()<=2) {
				QColor clr;
				for(int y=0; y<imageData.height(); y++) {
						for(int x=0; x<imageData.width(); x++) {
								clr = imageData.pixel(x,y);
								clr.setAlpha(255);
								imageData.setPixelColor(x,y,clr);
						}
				}
                if(fastRenderering){
                     this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
                }
				return;
		}
		QColor clr;
		for(int y=0; y<imageData.height(); y++) {
				for(int x=0; x<imageData.width(); x++) {
						QPoint ptr(x,y);
						clr = imageData.pixelColor(x,y);
                        bool isInPolygon = IntelliTriangulation::isInPolygon(triangles, ptr);
						if(isInPolygon) {
								clr.setAlpha(std::min(255, clr.alpha()));
						}else{
								clr.setAlpha(0);
						}
						imageData.setPixelColor(x,y,clr);
				}
		}
        if(fastRenderering){
             this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
        }
}

QImage IntelliShapedImage::getDisplayable(const QSize& displaySize, int alpha){
		QImage copy = imageData;
        if(fastRenderering){
             copy = copy.convertToFormat(QImage::Format_ARGB32);
        }
		for(int y = 0; y<copy.height(); y++) {
				for(int x = 0; x<copy.width(); x++) {
						QColor clr = copy.pixelColor(x,y);
						clr.setAlpha(std::min(alpha,clr.alpha()));
						copy.setPixelColor(x,y, clr);
				}
		}
        if(fastRenderering){
             copy = copy.convertToFormat(QImage::Format_Indexed8);
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
                triangles = IntelliTriangulation::calculateTriangles(polygonData);
		}
		calculateVisiblity();
		return;
}
