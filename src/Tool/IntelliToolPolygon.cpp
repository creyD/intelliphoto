#include "IntelliToolPolygon.h"
#include "Layer/PaintingArea.h"
#include <QDebug>
#include <QCursor>
#include <QInputDialog>

IntelliToolPolygon::IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker)
		: IntelliTool(Area, colorPicker){
        this->innerAlpha = QInputDialog::getInt(nullptr,"Inner Alpha Value", "Value:", 255,0,255,1);
        lineWidth = QInputDialog::getInt(nullptr,"Line Width Input", "Width",5,1,10,1);
		isPointNearStart = false;
		isDrawing = false;
        this->ActiveType = Tooltype::POLYGON;
}

IntelliToolPolygon::~IntelliToolPolygon(){
    if(isDrawing){
        IntelliTool::onMouseRightPressed(0,0);
    }
}

void IntelliToolPolygon::onMouseLeftPressed(int x, int y){
		if(!isDrawing && x > 0 && y > 0 && x<Area->getWidthOfActive() && y<Area->getHeightOfActive()) {
				IntelliTool::onMouseLeftPressed(x,y);
				QPoint drawingPoint = QPoint(x,y);

				isDrawing = true;
				QPointList.push_back(drawingPoint);

				this->Canvas->image->drawPoint(QPointList.back(), colorPicker->getFirstColor(), lineWidth);
				this->Canvas->image->calculateVisiblity();
		}
		else if(isDrawing && isNearStart(x,y,QPointList.front())) {
                if(QPointList.size() > 2){
                    isPointNearStart = true;
                    this->Canvas->image->drawLine(QPointList.back(), QPointList.front(), colorPicker->getFirstColor(), lineWidth);
                    this->Canvas->image->calculateVisiblity();
                }
                else{
                    isDrawing = false;
                    QPointList.clear();
                    IntelliTool::onMouseRightPressed(x,y);
                }

		}
		else if(isDrawing) {
				QPoint drawingPoint(x,y);
				QPointList.push_back(drawingPoint);
				this->Canvas->image->drawLine(QPointList[QPointList.size() - 2], QPointList[QPointList.size() - 1], colorPicker->getFirstColor(), lineWidth);
				this->Canvas->image->calculateVisiblity();
		}
}

void IntelliToolPolygon::onMouseRightPressed(int x, int y){
		isDrawing = false;
		isPointNearStart = false;
		QPointList.clear();
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPolygon::onMouseLeftReleased(int x, int y){
        if(isPointNearStart) {
				isPointNearStart = false;
				isDrawing = false;
				std::vector<Triangle> Triangles = IntelliHelper::calculateTriangles(QPointList);
				QPoint Point;
				QColor colorTwo(colorPicker->getSecondColor());
				colorTwo.setAlpha(innerAlpha);
				for(int i = 0; i < activeLayer->width; i++) {
						for(int j = 0; j < activeLayer->height; j++) {
								Point = QPoint(i,j);
								if(IntelliHelper::isInPolygon(Triangles,Point)) {
										this->Canvas->image->drawPixel(Point, colorTwo);
								}
						}
				}
                for(int i=0; i<static_cast<int>(QPointList.size()); i++) {
                        int next = static_cast<int>((i+static_cast<int>(1))%static_cast<int>(QPointList.size()));
                        this->Canvas->image->drawLine(QPointList[static_cast<unsigned long long>(i)], QPointList[static_cast<unsigned long long>(next)], colorPicker->getFirstColor(), lineWidth);
				}
				QPointList.clear();
				IntelliTool::onMouseLeftReleased(x,y);
		}
}

void IntelliToolPolygon::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolPolygon::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		if(!isDrawing) {
				if(lineWidth + value < 10) {
						lineWidth += value;
				}
				if(lineWidth < 1) {
						lineWidth = 1;
				}
		}
}

void IntelliToolPolygon::onMouseMoved(int x, int y){
		IntelliTool::onMouseMoved(x,y);
}

bool IntelliToolPolygon::isNearStart(int x, int y, QPoint Startpoint){
		bool isNear = false;
		int StartX = Startpoint.x();
		int StartY = Startpoint.y();
		int valueToNear = 10;

		for(int i = StartX - valueToNear; i < StartX + valueToNear; i++) {
				for(int j = StartY - valueToNear; j < StartY + valueToNear; j++) {
						if((i == x) && (j == y)) {
								isNear = true;
						}
				}
		}
		return isNear;
}
