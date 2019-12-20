#include "IntelliToolLine.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"

IntelliToolLine::IntelliToolLine(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
		this->lineWidth = QInputDialog::getInt(nullptr,"Line Width Input", "Width",1,1,50,1);
		//create checkbox or scroll dialog to get line style
		this->lineStyle = LineStyle::SOLID_LINE;
}

IntelliToolLine::~IntelliToolLine(){

}

void IntelliToolLine::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolLine::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolLine::onMouseLeftPressed(int x, int y){
		IntelliTool::onMouseLeftPressed(x,y);
		this->lineStartingPoint=QPoint(x,y);
		this->Canvas->image->drawPoint(lineStartingPoint, colorPicker->getFirstColor(),lineWidth);
		Canvas->image->calculateVisiblity();
}

void IntelliToolLine::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolLine::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		this->lineWidth+=value;
		if(this->lineWidth<=0) {
				this->lineWidth=1;
		}
}

void IntelliToolLine::onMouseMoved(int x, int y){
		if(this->isDrawing) {
				this->Canvas->image->drawPlain(Qt::transparent);
				QPoint next(x,y);
				switch(lineStyle) {
				case LineStyle::SOLID_LINE:
						this->Canvas->image->drawLine(lineStartingPoint,next,colorPicker->getFirstColor(),lineWidth);
						break;
				case LineStyle::DOTTED_LINE:
						QPoint p1 =lineStartingPoint.x() <= next.x() ? lineStartingPoint : next;
						QPoint p2 =lineStartingPoint.x() < next.x() ? next : lineStartingPoint;
            int m = static_cast<int>(static_cast<float>(p2.y()-p1.y())/static_cast<float>(p2.x()-p1.x())+0.5f);
						int c = lineStartingPoint.y()-lineStartingPoint.x()*m;

						break;
				}
		}
		IntelliTool::onMouseMoved(x,y);
}
