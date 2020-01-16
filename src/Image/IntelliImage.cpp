#include "Image/IntelliImage.h"
#include <QSize>
#include <QPainter>

IntelliImage::IntelliImage(int width, int height, bool fastRendererOn)
		: imageData(QSize(width, height), fastRendererOn ? QImage::Format_Indexed8 : QImage::Format_ARGB32){
		if(fastRendererOn) {
				imageData = imageData.convertToFormat(QImage::Format_ARGB32);
		}
		imageData.fill(QColor(255,255,255,255));
		if(fastRendererOn) {
				imageData = imageData.convertToFormat(QImage::Format_Indexed8);
		}
		this->fastRenderering = fastRendererOn;

}

IntelliImage::~IntelliImage(){

}

bool IntelliImage::loadImage(const QString &filePath){
		// Holds the image
		QImage loadedImage;

		// If the image wasn't loaded leave this function
		if (!loadedImage.load(filePath))
				return false;

		// scaled Image to size of Layer
		loadedImage = loadedImage.scaled(imageData.size(),Qt::IgnoreAspectRatio);

		imageData = loadedImage.convertToFormat(fastRenderering ? QImage::Format_Indexed8 : QImage::Format_ARGB32);
		return true;
}

void IntelliImage::resizeImage(QImage*image, const QSize &newSize){
		// Check if we need to redraw the image
		if (image->size() == newSize)
				return;

		// Create a new image to display and fill it with white
		QImage newImage(newSize, QImage::Format_ARGB32);
		newImage.fill(qRgb(255, 255, 255));

		// Draw the image
		QPainter painter(&newImage);
		painter.drawImage(QPoint(0, 0), *image);
		if(fastRenderering) {
				*image = newImage.convertToFormat(QImage::Format_Indexed8);
		}
		else{
				*image = newImage;
		}
}

void IntelliImage::drawPixel(const QPoint &p1, const QColor& color){
		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_ARGB32);
		}
		// Used to draw on the widget
		QPainter* painter = new QPainter(&imageData);

		// Set the current settings for the pen
		painter->setPen(QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		// Draw a line from the last registered point to the current
		painter->drawPoint(p1);
		delete painter;
		painter = nullptr;

		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
		}
}

void IntelliImage::drawPoint(const QPoint &p1, const QColor& color, const int& penWidth){
		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_ARGB32);
		}
		// Used to draw on the widget
		QPainter* painter = new QPainter(&imageData);

		// Set the current settings for the pen
		painter->setPen(QPen(color, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		// Draw a line from the last registered point to the current
		painter->drawPoint(p1);
		delete painter;

		painter = nullptr;
		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
		}
}

void IntelliImage::drawLine(const QPoint &p1, const QPoint& p2, const QColor& color, const int& penWidth){
		if(fastRenderering) {
				this->imageData =  this->imageData.convertToFormat(QImage::Format_ARGB32);
		}
		// Used to draw on the widget
		QPainter* painter = new QPainter(&imageData);

		// Set the current settings for the pen
		painter->setPen(QPen(color, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

		// Draw a line from the last registered point to the current
		painter->drawLine(p1, p2);
		delete painter;
		painter = nullptr;

		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
		}
}

void IntelliImage::drawPlain(const QColor& color){
		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_ARGB32);
		}
		imageData.fill(color);
		if(fastRenderering) {
				this->imageData = this->imageData.convertToFormat(QImage::Format_Indexed8);
		}
}

QColor IntelliImage::getPixelColor(QPoint& point){
		if(fastRenderering) {
				QImage copy = this->imageData.convertToFormat(QImage::Format_ARGB32);
				return copy.pixelColor(point);
		}
		return imageData.pixelColor(point);
}

QImage IntelliImage::getImageData(){
		QImage copy = imageData;
		if(fastRenderering) {
				copy = copy.convertToFormat(QImage::Format_ARGB32);
		}
		return copy;
}

void IntelliImage::setImageData(const QImage& newData){
		imageData = newData;
		if(fastRenderering) {
				this->imageData = imageData.convertToFormat(QImage::Format_Indexed8);
		}
		else {
				this->imageData = imageData.convertToFormat(QImage::Format_ARGB32);
		}
}

void IntelliImage::updateRendererSetting(bool fastRendererOn){
		this->fastRenderering = fastRendererOn;
		if(fastRenderering) {
				this->imageData = imageData.convertToFormat(QImage::Format_Indexed8);
		}
		else {
				this->imageData = imageData.convertToFormat(QImage::Format_ARGB32);
		}
}
