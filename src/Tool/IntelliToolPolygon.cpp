#include "IntelliToolPolygon.h"
#include "Layer/PaintingArea.h"
#include <QCursor>
#include <QInputDialog>
#include <QDebug>
#include <cmath>

IntelliToolPolygon::IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings, bool isSettingPolygon)
		: IntelliTool(Area, colorPicker, Toolsettings){
		isPointNearStart = false;
		drawingOfPolygon = false;
		isInside = false;
		this->isSettingPolygon = isSettingPolygon;
		if(isSettingPolygon) {
				Toolsettings->setLineWidth(5);
		}
		this->ActiveType = Tooltype::POLYGON;
}

IntelliToolPolygon::~IntelliToolPolygon(){
		if(drawingOfPolygon) {
				IntelliTool::onMouseRightPressed(0,0);
		}
}

void IntelliToolPolygon::onMouseLeftPressed(int x, int y){
        if(!drawingOfPolygon && Area->getTypeOfImageRealLayer() == IntelliImage::ImageType::SHAPEDIMAGE && x > 0 && y > 0 && x<Area->getWidthOfActive() && y<Area->getHeightOfActive()) {
				if(Area->getPolygonDataOfRealLayer().size()>2) {
						std::vector<Triangle> Triangles = IntelliTriangulation::calculateTriangles(Area->getPolygonDataOfRealLayer());
						QPoint Point(x,y);
						isInside = IntelliTriangulation::isInPolygon(Triangles,Point);
				}
				else{
						isInside = true;
				}
				if(isSettingPolygon) {
						isInside = true;
				}
		}
		else if(!drawingOfPolygon && Area->getTypeOfImageRealLayer() == IntelliImage::ImageType::RASTERIMAGE && x >= 0 && y >= 0 && x<Area->getWidthOfActive() && y<Area->getHeightOfActive()) {
				isInside = true;
		}

		if(isInside && !drawingOfPolygon) {
				IntelliTool::onMouseLeftPressed(x,y);
				QPoint drawingPoint = QPoint(x,y);

				drawingOfPolygon = true;
				QPointList.push_back(drawingPoint);

				this->Canvas->image->drawPoint(QPointList.back(), colorPicker->getFirstColor(), Toolsettings->getLineWidth());
				if(!isSettingPolygon) {
						this->Canvas->image->calculateVisiblity();
				}
		}
        else if(drawingOfPolygon && QPointList.size() > 0 && isNearStart(x,y,QPointList.front())) {
				if(QPointList.size() > 2) {
						isPointNearStart = true;
						this->Canvas->image->drawLine(QPointList.back(), QPointList.front(), colorPicker->getFirstColor(), Toolsettings->getLineWidth());
						if(!isSettingPolygon) {
								this->Canvas->image->calculateVisiblity();
						}
				}
				else{
						isInside = false;
						drawingOfPolygon = false;
						QPointList.clear();
						IntelliTool::onMouseRightPressed(x,y);
						IntelliTool::onMouseRightReleased(x,y);
				}

		}
		else if(drawingOfPolygon) {
				QPoint drawingPoint(x,y);
				QPointList.push_back(drawingPoint);
				this->Canvas->image->drawLine(QPointList[QPointList.size() - 2], QPointList[QPointList.size() - 1], colorPicker->getFirstColor(), Toolsettings->getLineWidth());
				if(!isSettingPolygon) {
						this->Canvas->image->calculateVisiblity();
				}
		}
}

void IntelliToolPolygon::onMouseRightPressed(int x, int y){
        drawingOfPolygon = false;
		isInside = false;
		isPointNearStart = false;
		QPointList.clear();
		IntelliTool::onMouseRightPressed(x,y);
}

void IntelliToolPolygon::onMouseLeftReleased(int x, int y){
		if(isPointNearStart) {
				isInside = false;
				isPointNearStart = false;
                drawingOfPolygon = false;
				if(!isSettingPolygon) {
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
						for(int i = 0; i<static_cast<int>(QPointList.size()); i++) {
								int next = static_cast<int>((i + static_cast<int>(1)) % static_cast<int>(QPointList.size()));
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
		if(!isSettingPolygon) {
				IntelliTool::onWheelScrolled(value);
				if(!isDrawing) {
						Toolsettings->setLineWidth(Toolsettings->getLineWidth() + value);
				}
		}
}

void IntelliToolPolygon::onMouseMoved(int x, int y){
		if(!isSettingPolygon) {
				IntelliTool::onMouseMoved(x,y);
		}
}

bool IntelliToolPolygon::isNearStart(int x, int y, QPoint Startpoint){
		int StartX = Startpoint.x();
		int StartY = Startpoint.y();
		int valueToNear = 5;

        float euklid = sqrt(pow(static_cast<float>(StartX-x),2.f)+pow(static_cast<float>(StartY-y),2.f));

        return static_cast<int>(euklid)<valueToNear;
}
