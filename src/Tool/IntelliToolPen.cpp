#include "IntelliToolPen.h"
#include "Layer/PaintingArea.h"
#include "QDebug"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolPen::IntelliToolPen(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
		this->penWidth = QInputDialog::getInt(nullptr, "Pen width", "Width:", 1,0, 50, 1);
        this->ActiveType = Tooltype::PEN;
}

IntelliToolPen::~IntelliToolPen(){
        IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolPen::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPen::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolPen::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->previousPoint=QPoint(x,y);
        this->Canvas->image->drawPoint(previousPoint, colorPicker->getFirstColor(), penWidth);
		Canvas->image->calculateVisiblity();
}

void IntelliToolPen::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolPen::onMouseMoved(int x, int y){
		if(this->isDrawing) {
				QPoint newPoint(x,y);
				this->Canvas->image->drawLine(this->previousPoint, newPoint, colorPicker->getFirstColor(), penWidth);
				this->previousPoint=newPoint;
		}
		IntelliTool::onMouseMoved(x,y);
}

void IntelliToolPen::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		this->penWidth+=value;
		if(this->penWidth<=0) {
				this->penWidth=1;
		}
}
