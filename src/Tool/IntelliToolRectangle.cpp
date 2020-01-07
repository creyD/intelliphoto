#include "IntelliToolRectangle.h"
#include "Layer/PaintingArea.h"
#include "QInputDialog"

IntelliToolRectangle::IntelliToolRectangle(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
		this->innerAlpha = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 0,0,255,1);
		this->borderWidth = QInputDialog::getInt(nullptr,"Outer edge width", "Value:", 0,1,255,1);
        this->ActiveType = Tooltype::RECTANGLE;
}

IntelliToolRectangle::~IntelliToolRectangle(){
        IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolRectangle::drawRectangle(QPoint otherCorner){
        int xMin = std::min(originCorner.x(), otherCorner.x());
        int xMax = std::max(originCorner.x(), otherCorner.x());

        int yMin = std::min(originCorner.y(), otherCorner.y());
        int yMax = std::max(originCorner.y(), otherCorner.y());

		QColor clr = colorPicker->getSecondColor();
		clr.setAlpha(innerAlpha);
		for(int y=yMin; y<=yMax; y++) {
				this->Canvas->image->drawLine(QPoint(xMin,y), QPoint(xMax, y), clr, 1);
		}
		this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), borderWidth);
		this->Canvas->image->drawLine(QPoint(xMin, yMin),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), borderWidth);
		this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMin, yMax), this->colorPicker->getFirstColor(), borderWidth);
		this->Canvas->image->drawLine(QPoint(xMax, yMax),QPoint(xMax, yMin), this->colorPicker->getFirstColor(), borderWidth);
}

void IntelliToolRectangle::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolRectangle::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolRectangle::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->originCorner=QPoint(x,y);
		drawRectangle(originCorner);
		Canvas->image->calculateVisiblity();
}

void IntelliToolRectangle::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolRectangle::onMouseMoved(int x, int y){
		if(this->isDrawing) {
				this->Canvas->image->drawPlain(Qt::transparent);
				QPoint next(x,y);
				drawRectangle(next);
		}
		IntelliTool::onMouseMoved(x,y);
}

void IntelliToolRectangle::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		this->borderWidth+=value;
		if(this->borderWidth<=0) {
				this->borderWidth=1;
		}
}
