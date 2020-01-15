#include "IntelliToolPolygon.h"
#include "Layer/PaintingArea.h"
#include <QCursor>
#include <QInputDialog>
#include <QDebug>

IntelliToolPolygon::IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings, bool isSettingPolygon)
		: IntelliTool(Area, colorPicker, Toolsettings){
		isPointNearStart = false;
		isDrawing = false;
		isInside = false;
        this->isSettingPolygon = isSettingPolygon;
		this->ActiveType = Tooltype::POLYGON;
}

IntelliToolPolygon::~IntelliToolPolygon(){
		if(isDrawing) {
				IntelliTool::onMouseRightPressed(0,0);
		}
}

void IntelliToolPolygon::onMouseLeftPressed(int x, int y){
        if(!isDrawing && Area->getTypeOfImageRealLayer() == IntelliImage::ImageType::SHAPEDIMAGE && x > 0 && y > 0 && x<Area->getWidthOfActive() && y<Area->getHeightOfActive()) {
				std::vector<Triangle> Triangles = IntelliTriangulation::calculateTriangles(Area->getPolygonDataOfRealLayer());
				QPoint Point(x,y);
				isInside = IntelliTriangulation::isInPolygon(Triangles,Point);
                if(isSettingPolygon){
                    isInside = true;
                }
		}
		else if(!isDrawing && Area->getTypeOfImageRealLayer() == IntelliImage::ImageType::RASTERIMAGE && x > 0 && y > 0 && x<Area->getWidthOfActive() && y<Area->getHeightOfActive()) {
				isInside = true;
		}

		if(isInside && !isDrawing) {
				IntelliTool::onMouseLeftPressed(x,y);
				QPoint drawingPoint = QPoint(x,y);

				isDrawing = true;
				QPointList.push_back(drawingPoint);

				this->Canvas->image->drawPoint(QPointList.back(), colorPicker->getFirstColor(), Toolsettings->getLineWidth());
                if(!isSettingPolygon){
                                    this->Canvas->image->calculateVisiblity();
                }
		}
		else if(isDrawing && isNearStart(x,y,QPointList.front())) {
				if(QPointList.size() > 2) {
						isPointNearStart = true;
						this->Canvas->image->drawLine(QPointList.back(), QPointList.front(), colorPicker->getFirstColor(), Toolsettings->getLineWidth());
                        if(!isSettingPolygon){
                                            this->Canvas->image->calculateVisiblity();
                        }
                }
				else{
						isInside = false;
						isDrawing = false;
						QPointList.clear();
						IntelliTool::onMouseRightPressed(x,y);
				}

		}
		else if(isDrawing) {
				QPoint drawingPoint(x,y);
				QPointList.push_back(drawingPoint);
				this->Canvas->image->drawLine(QPointList[QPointList.size() - 2], QPointList[QPointList.size() - 1], colorPicker->getFirstColor(), Toolsettings->getLineWidth());
                if(!isSettingPolygon){
                                    this->Canvas->image->calculateVisiblity();
                }
		}
}

void IntelliToolPolygon::onMouseRightPressed(int x, int y){
		isInside = false;
		isDrawing = false;
		isPointNearStart = false;
		QPointList.clear();
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPolygon::onMouseLeftReleased(int x, int y){
		if(isPointNearStart) {
				isInside = false;
				isPointNearStart = false;
				isDrawing = false;
                if(!isSettingPolygon){
                    std::vector<Triangle> Triangles = IntelliTriangulation::calculateTriangles(QPointList);
                    QPoint Point;
                    QColor colorTwo(colorPicker->getSecondColor());
                    colorTwo.setAlpha(Toolsettings->getInnerAlpha());
                    for(int i = 0; i < activeLayer->width; i++) {
                            for(int j = 0; j < activeLayer->height; j++) {
                                    Point = QPoint(i,j);
                                    if(IntelliTriangulation::isInPolygon(Triangles,Point)) {
                                            this->Canvas->image->drawPixel(Point, colorTwo);
                                    }
                            }
                    }
                    for(int i=0; i<static_cast<int>(QPointList.size()); i++) {
                            int next = static_cast<int>((i+static_cast<int>(1))%static_cast<int>(QPointList.size()));
                            this->Canvas->image->drawLine(QPointList[static_cast<unsigned long long>(i)], QPointList[static_cast<unsigned long long>(next)], colorPicker->getFirstColor(), Toolsettings->getLineWidth());
                    }

                }
                else{
                    Canvas->image->setPolygon(QPointList);
                    Canvas->image->setImageData(Area->getImageDataOfActiveLayer());
                }
                IntelliTool::onMouseLeftReleased(x,y);
                QPointList.clear();
		}
}

void IntelliToolPolygon::onMouseRightReleased(int x, int y){
		IntelliTool::onMouseRightReleased(x,y);
}

void IntelliToolPolygon::onWheelScrolled(int value){
		IntelliTool::onWheelScrolled(value);
		if(!isDrawing) {
				Toolsettings->setLineWidth(Toolsettings->getLineWidth() + value);
		}
}

void IntelliToolPolygon::onMouseMoved(int x, int y){
		IntelliTool::onMouseMoved(x,y);
}

bool IntelliToolPolygon::isNearStart(int x, int y, QPoint Startpoint){
		bool isNear = false;
		int StartX = Startpoint.x();
		int StartY = Startpoint.y();
		int valueToNear = 5;

		for(int i = StartX - valueToNear; i < StartX + valueToNear; i++) {
				for(int j = StartY - valueToNear; j < StartY + valueToNear; j++) {
						if((i == x) && (j == y)) {
								isNear = true;
						}
				}
		}
		return isNear;
}
