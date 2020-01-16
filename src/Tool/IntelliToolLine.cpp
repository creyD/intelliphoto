#include "IntelliToolLine.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolLine::IntelliToolLine(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings)
		: IntelliTool(Area, colorPicker, Toolsettings){
		this->ActiveType = Tooltype::LINE;
}

IntelliToolLine::~IntelliToolLine(){
		IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolLine::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolLine::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolLine::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->lineStartingPoint = QPoint(x,y);
		this->Canvas->image->drawPoint(lineStartingPoint, colorPicker->getFirstColor(),Toolsettings->getLineWidth());
		Canvas->image->calculateVisiblity();
}

void IntelliToolLine::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolLine::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		Toolsettings->setLineWidth(Toolsettings->getLineWidth() + value);
}

void IntelliToolLine::onMouseMoved(int x, int y){
		if(this->isDrawing) {
				this->Canvas->image->drawPlain(Qt::transparent);
				QPoint next(x,y);
				this->Canvas->image->drawLine(lineStartingPoint,next,colorPicker->getFirstColor(),Toolsettings->getLineWidth());
		}
		IntelliTool::onMouseMoved(x,y);
}
