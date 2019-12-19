#include "IntelliToolRectangle.h"
#include "Layer/PaintingArea.h"
#include "QInputDialog"

IntelliToolRectangle::IntelliToolRectangle(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
		this->alphaInner = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 0,0,255,1);
		this->edgeWidth = QInputDialog::getInt(nullptr,"Outer edge width", "Value:", 0,1,255,1);
}

IntelliToolRectangle::~IntelliToolRectangle(){

}

void IntelliToolRectangle::drawRectangle(QPoint otherCornor){
		int xMin = std::min(originCornor.x(), otherCornor.x());
		int xMax = std::max(originCornor.x(), otherCornor.x());

		int yMin = std::min(originCornor.y(), otherCornor.y());
		int yMax = std::max(originCornor.y(), otherCornor.y());

		QColor clr = colorPicker->getSecondColor();
		clr.setAlpha(alphaInner);
		for(int y=yMin; y<=yMax; y++) {
				this->Canvas->image->drawLine(QPoint(xMin,y), QPoint(xMax, y), clr, 1);
		}
		this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), edgeWidth);
		this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), edgeWidth);
		this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), edgeWidth);
		this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), edgeWidth);
}

void IntelliToolRectangle::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolRectangle::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolRectangle::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->originCornor=QPoint(x,y);
		drawRectangle(originCornor);
		Canvas->image->calculateVisiblity();
}

void IntelliToolRectangle::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolRectangle::onMouseMoved(int x, int y){
		if(this->drawing) {
				this->Canvas->image->drawPlain(Qt::transparent);
				QPoint next(x,y);
				drawRectangle(next);
		}
		IntelliTool::onMouseMoved(x,y);
}

void IntelliToolRectangle::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		this->edgeWidth+=value;
		if(this->edgeWidth<=0) {
				this->edgeWidth=1;
		}
}
