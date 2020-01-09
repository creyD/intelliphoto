#include "IntelliToolFloodFill.h"
#include "Layer/PaintingArea.h"
#include "QColorDialog"
#include "QInputDialog"
#include <functional>
#include <queue>

IntelliToolFloodFill::IntelliToolFloodFill(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings)
		: IntelliTool(Area, colorPicker, Toolsettings){
		this->ActiveType = Tooltype::FLOODFILL;
}

IntelliToolFloodFill::~IntelliToolFloodFill(){
		IntelliTool::onMouseRightPressed(0,0);
}

void IntelliToolFloodFill::onMouseRightPressed(int x, int y){
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolFloodFill::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolFloodFill::onMouseLeftPressed(int x, int y){
		if(!(x>=0 && x<Area->getWidthOfActive() && y>=0 && y<Area->getHeightOfActive())) {
				return;
		}
		IntelliTool::onMouseLeftPressed(x,y);

		QPoint start(x,y);
		std::queue<QPoint> Q;
		Q.push(start);

		QColor oldColor = this->activeLayer->image->getPixelColor(start);
		QColor newColor = this->colorPicker->getFirstColor();
		Canvas->image->drawPixel(start,newColor);

		QPoint left, right, top, down;
		while(!Q.empty()) {
				QPoint Current = Q.front();
				Q.pop();

				left  = QPoint(Current.x()-1,Current.y()  );
				right = QPoint(Current.x()+1,Current.y()  );
				top   = QPoint(Current.x(),Current.y()-1);
				down  = QPoint(Current.x(),Current.y()+1);
				if((right.x() < Canvas->width) && (Canvas->image->getPixelColor(right) != newColor) && (activeLayer->image->getPixelColor(right) == oldColor)) {
						Canvas->image->drawPixel(right,newColor);
						Q.push(right);
				}
				if((left.x() >= 0) && (Canvas->image->getPixelColor(left) != newColor) && (activeLayer->image->getPixelColor(left) == oldColor)) {
						Canvas->image->drawPixel(left,newColor);
						Q.push(left);
				}
				if((top.y() >= 0) && (Canvas->image->getPixelColor(top) != newColor) && (activeLayer->image->getPixelColor(top) == oldColor)) {
						Canvas->image->drawPixel(top,newColor);
						Q.push(top);
				}
				if((down.y() < Canvas->height) && (Canvas->image->getPixelColor(down) != newColor) && (activeLayer->image->getPixelColor(down) == oldColor)) {
						Canvas->image->drawPixel(down,newColor);
						Q.push(down);
				}
		}

		Canvas->image->calculateVisiblity();
}

void IntelliToolFloodFill::onMouseLeftReleased(int x, int y){
		IntelliTool::onMouseLeftReleased(x,y);
}

void IntelliToolFloodFill::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);

}

void IntelliToolFloodFill::onMouseMoved(int x, int y){
		IntelliTool::onMouseMoved(x,y);
}
