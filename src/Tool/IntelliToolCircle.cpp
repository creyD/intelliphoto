#include "IntelliToolCircle.h"
#include "Layer/PaintingArea.h"
#include "QInputDialog"
#include <cmath>

IntelliToolCircle::IntelliToolCircle(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
		this->innerAlpha = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 0,0,255,1);
		this->borderWidth = QInputDialog::getInt(nullptr,"Outer edge width", "Value:", 0,1,255,1);
}

IntelliToolCircle::~IntelliToolCircle(){

}

void IntelliToolCircle::drawCircle(int radius){
		int outer = radius+20;
		QColor inner = this->colorPicker->getSecondColor();
		inner.setAlpha(innerAlpha);
		int yMin, yMax, xMin, xMax;
		yMin = centerPoint.y()-radius;
		yMax = centerPoint.y()+radius;
		// x = x0+-sqrt(r2-(y-y0)2)
		for(int i=yMin; i<=yMax; i++) {
        xMin = static_cast<int>(centerPoint.x()-sqrt(pow(radius,2)-pow(i-centerPoint.y(),2)));
        xMax = static_cast<int>(centerPoint.x()+sqrt(pow(radius,2)-pow(i-centerPoint.y(),2)));
				this->Canvas->image->drawLine(QPoint(xMin,i), QPoint(xMax,i),inner,1);
		}

		//TODO implement circle drawing algorithm bresenham
    radius = static_cast<int>(radius +(this->borderWidth/2.)-1.);
		yMin = (centerPoint.y()-radius);
		yMax = (centerPoint.y()+radius);
		for(int i=yMin; i<=yMax; i++) {
        xMin = static_cast<int>(centerPoint.x()-sqrt(pow(radius,2)-pow(i-centerPoint.y(),2)));
        xMax = static_cast<int>(centerPoint.x()+sqrt(pow(radius,2)-pow(i-centerPoint.y(),2)));
				this->Canvas->image->drawPoint(QPoint(xMin,i), colorPicker->getFirstColor(),borderWidth);
				this->Canvas->image->drawPoint(QPoint(xMax,i), colorPicker->getFirstColor(),borderWidth);
		}

		xMin = (centerPoint.x()-radius);
		xMax = (centerPoint.x()+radius);
		for(int i=xMin; i<=xMax; i++) {
        int yMin = static_cast<int>(centerPoint.y()-sqrt(pow(radius,2)-pow(i-centerPoint.x(),2)));
        int yMax = static_cast<int>(centerPoint.y()+sqrt(pow(radius,2)-pow(i-centerPoint.x(),2)));
				this->Canvas->image->drawPoint(QPoint(i, yMin), colorPicker->getFirstColor(),borderWidth);
				this->Canvas->image->drawPoint(QPoint(i, yMax), colorPicker->getFirstColor(),borderWidth);
		}
}

void IntelliToolCircle::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolCircle::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolCircle::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->centerPoint=QPoint(x,y);
		int radius = 1;
		drawCircle(radius);
		Canvas->image->calculateVisiblity();
}

void IntelliToolCircle::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolCircle::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		this->borderWidth+=value;
		if(this->borderWidth<=0) {
				this->borderWidth=1;
		}
}

void IntelliToolCircle::onMouseMoved(int x, int y){
		if(this->isDrawing) {
				this->Canvas->image->drawPlain(Qt::transparent);
				QPoint next(x,y);
				int radius = static_cast<int>(sqrt(pow((centerPoint.x()-x),2)+pow((centerPoint.y()-y),2)));
				drawCircle(radius);
		}
		IntelliTool::onMouseMoved(x,y);
}
