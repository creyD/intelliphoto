// ---------- PaintingArea.cpp ----------
#include "string.h"

#include <vector>

#include <QtWidgets>
#include <QPoint>
#include <QRect>

#include "PaintingArea.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"
#include "Tool/IntelliToolPen.h"
#include "Tool/IntelliToolPlain.h"
#include "Tool/IntelliToolLine.h"
#include "Tool/IntelliToolCircle.h"
#include "Tool/IntelliToolRectangle.h"
#include "Tool/IntelliToolFloodFill.h"
#include "Tool/IntelliToolPolygon.h"

PaintingArea::PaintingArea(int maxWidth, int maxHeight, QWidget*parent)
		: QWidget(parent){
		this->Tool = nullptr;
		this->setLayerDimensions(maxWidth, maxHeight);
		this->addLayer(200,200,0,0,IntelliImage::ImageType::SHAPEDIMAGE);
		layerBundle[0].image->drawPlain(QColor(0,0,255,255));
		std::vector<QPoint> polygon;
		polygon.push_back(QPoint(100,000));
		polygon.push_back(QPoint(200,100));
		polygon.push_back(QPoint(100,200));
		polygon.push_back(QPoint(000,100));
		layerBundle[0].image->setPolygon(polygon);

		this->addLayer(200,200,150,150,IntelliImage::ImageType::RASTERIMAGE);
		layerBundle[1].image->drawPlain(QColor(0,255,0,255));
		layerBundle[1].alpha=200;

		activeLayer=0;
}

PaintingArea::~PaintingArea(){
		delete Tool;
}

void PaintingArea::setRenderSettings(bool isFastRenderingOn){
		if(isFastRenderingOn != renderSettings.isFastRenderering()) {
				renderSettings.setFastRendering(isFastRenderingOn);
				for(auto& layer : layerBundle) {
						layer.image->updateRendererSetting(isFastRenderingOn);
				}
		}
}

void PaintingArea::setLayerDimensions(int maxWidth, int maxHeight){
		//set standart parameter
		this->maxWidth = maxWidth;
		this->maxHeight = maxHeight;
		Canvas = new QImage(maxWidth,maxHeight, QImage::Format_ARGB32);

		// Roots the widget to the top left even if resized
		setAttribute(Qt::WA_StaticContents);

}

int PaintingArea::addLayer(int width, int height, int widthOffset, int heightOffset, IntelliImage::ImageType type){
		LayerObject newLayer;
		newLayer.width = width;
		newLayer.height = height;
		newLayer.widthOffset = widthOffset;
		newLayer.heightOffset = heightOffset;
		if(type==IntelliImage::ImageType::RASTERIMAGE) {
				newLayer.image = new IntelliRasterImage(width,height,renderSettings.isFastRenderering());
		}else if(type==IntelliImage::ImageType::SHAPEDIMAGE) {
				newLayer.image = new IntelliShapedImage(width, height, renderSettings.isFastRenderering());
		}
		newLayer.alpha = 255;
		this->layerBundle.push_back(newLayer);
		activeLayer = static_cast<int>(layerBundle.size())-1;
		return activeLayer;
}


void PaintingArea::deleteLayer(int idx){
		if(idx<static_cast<int>(layerBundle.size())) {
				this->layerBundle.erase(layerBundle.begin()+idx);
				if(activeLayer>=idx) {
						activeLayer--;
				}
				if(activeLayer < 0 && layerBundle.size()) {
						activeLayer=0;
				}
		}
}

void PaintingArea::slotDeleteActiveLayer(){
		if(activeLayer>=0 && activeLayer < static_cast<int>(layerBundle.size())) {
				this->layerBundle.erase(layerBundle.begin()+activeLayer);
				activeLayer--;
		}
}

void PaintingArea::setLayerActive(int idx){
		if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
				this->activeLayer=idx;
		}
}

void PaintingArea::setLayerAlpha(int idx, int alpha){
		if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
				layerBundle[static_cast<size_t>(idx)].alpha=alpha;
		}
}
void PaintingArea::setPolygon(int idx){
        if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
                 if(layerBundle[static_cast<size_t>(idx)].image->getTypeOfImage()==IntelliImage::ImageType::SHAPEDIMAGE){
                        qDebug() << "Todo Implement here set Polygon";
                 }
        }
}

// Used to load the image and place it in the widget
bool PaintingArea::open(const QString &filePath){
		if(this->activeLayer==-1) {
				return false;
		}
		IntelliImage* active = layerBundle[static_cast<size_t>(activeLayer)].image;
		bool open = active->loadImage(filePath);
		active->calculateVisiblity();
		update();
		return open;
}

// Save the current image
bool PaintingArea::save(const QString &filePath, const char*fileFormat){
		if(layerBundle.size()==0) {
				return false;
		}
		this->drawLayers(true);

		if(!strcmp(fileFormat,"PNG")) {
				QImage visibleImage = Canvas->convertToFormat(QImage::Format_Indexed8);
				fileFormat = "png";
				if (visibleImage.save(filePath, fileFormat)) {
						return true;
				} else {
						return false;
				}
		}

		if (Canvas->save(filePath, fileFormat)) {
				return true;
		} else {
				return false;
		}
}

// Color the image area with white
void PaintingArea::floodFill(int r, int g, int b, int a){
		if(this->activeLayer==-1) {
				return;
		}
		IntelliImage* active = layerBundle[static_cast<size_t>(activeLayer)].image;
		active->drawPlain(QColor(r, g, b, a));
		update();
}

void PaintingArea::movePositionActive(int x, int y){
		if(Tool!=nullptr) {
				if(Tool->getIsDrawing()) {
						IntelliTool* temp = copyActiveTool();
						delete this->Tool;
						this->Tool = temp;
				}
		}
		layerBundle[static_cast<size_t>(activeLayer)].widthOffset += x;
		layerBundle[static_cast<size_t>(activeLayer)].heightOffset += y;
}

void PaintingArea::moveActiveLayer(int idx){
		if(Tool != nullptr) {
				if(Tool->getIsDrawing()) {
						IntelliTool* temp = copyActiveTool();
						delete this->Tool;
						this->Tool = temp;
				}
		}
		if(idx==1) {
				this->selectLayerUp();
		}else if(idx==-1) {
				this->selectLayerDown();
		}
}

void PaintingArea::slotActivateLayer(int a){
		if(Tool != nullptr) {
				if(Tool->getIsDrawing()) {
						IntelliTool* temp = copyActiveTool();
						delete this->Tool;
						this->Tool = temp;
				}
		}
		if(a>=0 && a < static_cast<int>(layerBundle.size())) {
				this->setLayerActive(a);
		}
}

void PaintingArea::colorPickerSetFirstColor(){
		QColor clr = QColorDialog::getColor(colorPicker.getFirstColor(), nullptr, "Main Color", QColorDialog::DontUseNativeDialog);
		this->colorPicker.setFirstColor(clr);
}

void PaintingArea::colorPickerSetSecondColor(){
		QColor clr = QColorDialog::getColor(colorPicker.getSecondColor(), nullptr, "Secondary Color", QColorDialog::DontUseNativeDialog);
		this->colorPicker.setSecondColor(clr);
}

void PaintingArea::colorPickerSwapColors(){
		this->colorPicker.swapColors();
}

void PaintingArea::createPenTool(){
		delete this->Tool;
		Tool = new IntelliToolPen(this, &colorPicker, &Toolsettings);
}

void PaintingArea::createPlainTool(){
		delete this->Tool;
		Tool = new IntelliToolPlainTool(this, &colorPicker, &Toolsettings);
}

void PaintingArea::createLineTool(){
		delete this->Tool;
		Tool = new IntelliToolLine(this, &colorPicker, &Toolsettings);
}

void PaintingArea::createRectangleTool(){
		delete this->Tool;
		Tool = new IntelliToolRectangle(this, &colorPicker, &Toolsettings);
}

void PaintingArea::createCircleTool(){
		delete this->Tool;
		Tool = new IntelliToolCircle(this, &colorPicker, &Toolsettings);
}
void PaintingArea::createPolygonTool(){
		delete this->Tool;
		Tool = new IntelliToolPolygon(this, &colorPicker, &Toolsettings);
}

void PaintingArea::createFloodFillTool(){
		delete this->Tool;
		Tool = new IntelliToolFloodFill(this, &colorPicker, &Toolsettings);
}

int PaintingArea::getWidthOfActive(){
		return this->layerBundle[static_cast<unsigned long long>(activeLayer)].width;
}

int PaintingArea::getHeightOfActive(){
		return this->layerBundle[static_cast<unsigned long long>(activeLayer)].height;
}

IntelliImage::ImageType PaintingArea::getTypeOfImageRealLayer(){
		return this->layerBundle[static_cast<unsigned long long>(activeLayer)].image->getTypeOfImage();
}

std::vector<QPoint> PaintingArea::getPolygonDataOfRealLayer(){
		return this->layerBundle[static_cast<unsigned long long>(activeLayer)].image->getPolygonData();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent*event){
		if(this->activeLayer < 0) {
				return;
		}
		if(Tool == nullptr)
				return;
		int x = event->x()-layerBundle[static_cast<unsigned long long>(activeLayer)].widthOffset;
		int y = event->y()-layerBundle[static_cast<unsigned long long>(activeLayer)].heightOffset;
		if(event->button() == Qt::LeftButton) {
				Tool->onMouseLeftPressed(x, y);
		}else if(event->button() == Qt::RightButton) {
				Tool->onMouseRightPressed(x, y);
		}
		update();
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void PaintingArea::mouseMoveEvent(QMouseEvent*event){
		if(this->activeLayer < 0) {
				return;
		}
		if(Tool == nullptr)
				return;
		int x = event->x()-layerBundle[static_cast<unsigned long long>(activeLayer)].widthOffset;
		int y = event->y()-layerBundle[static_cast<unsigned long long>(activeLayer)].heightOffset;
		Tool->onMouseMoved(x, y);
		update();
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent*event){
		if(this->activeLayer < 0)
				return;
		if(Tool == nullptr)
				return;
		int x = event->x()-layerBundle[static_cast<unsigned long long>(activeLayer)].widthOffset;
		int y = event->y()-layerBundle[static_cast<unsigned long long>(activeLayer)].heightOffset;
		if(event->button() == Qt::LeftButton) {
				Tool->onMouseLeftReleased(x, y);
		}else if(event->button() == Qt::RightButton) {
				Tool->onMouseRightReleased(x, y);
		}
		update();
}

void PaintingArea::wheelEvent(QWheelEvent*event){
		if(this->activeLayer < 0)
				return;
		if(this->Tool != nullptr) {
				QPoint numDegrees = event->angleDelta() / 8;
				if(!numDegrees.isNull()) {
						QPoint numSteps = numDegrees / 15;
						Tool->onWheelScrolled(numSteps.y()* -1);
				}
		}
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void PaintingArea::paintEvent(QPaintEvent*event){
		this->drawLayers();

		QPainter painter(this);
		QRect dirtyRec = event->rect();
		painter.drawImage(dirtyRec, *Canvas, dirtyRec);
		update();
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void PaintingArea::resizeEvent(QResizeEvent*event){
		//TODO wait till tool works
		update();
}

void PaintingArea::resizeLayer(QImage*image_res, const QSize &newSize){
		//TODO implement
}

void PaintingArea::selectLayerUp(){
		if(activeLayer!=-1 && static_cast<unsigned long long>(activeLayer)<layerBundle.size()-1) {
				std::swap(layerBundle[static_cast<unsigned long long>(activeLayer)], layerBundle[static_cast<unsigned long long>(activeLayer+1)]);
				activeLayer++;
		}
}

void PaintingArea::selectLayerDown(){
		if(activeLayer!=-1 && activeLayer>0) {
				std::swap(layerBundle[static_cast<unsigned long long>(activeLayer)], layerBundle[static_cast<unsigned long long>(activeLayer-1)]);
				activeLayer--;
		}
}

void PaintingArea::drawLayers(bool forSaving){
		if(forSaving) {
				Canvas->fill(Qt::GlobalColor::transparent);
		}else{
				Canvas->fill(Qt::GlobalColor::black);
		}
		for(size_t i=0; i<layerBundle.size(); i++) {
				LayerObject layer = layerBundle[i];
				QImage cpy = layer.image->getDisplayable(layer.alpha);
				QColor clr_0;
				QColor clr_1;
				for(int y=0; y<layer.height; y++) {
						if(layer.heightOffset+y<0) continue;
						if(layer.heightOffset+y>=maxHeight) break;
						for(int x=0; x<layer.width; x++) {
								if(layer.widthOffset+x<0) continue;
								if(layer.widthOffset+x>=maxWidth) break;
								clr_0=Canvas->pixelColor(layer.widthOffset+x, layer.heightOffset+y);
								clr_1=cpy.pixelColor(x,y);
								float t = static_cast<float>(clr_1.alpha())/255.f;
								int r =static_cast<int>(static_cast<float>(clr_1.red())*(t)+static_cast<float>(clr_0.red())*(1.f-t)+0.5f);
								int g =static_cast<int>(static_cast<float>(clr_1.green())*(t)+static_cast<float>(clr_0.green())*(1.f-t)+0.5f);
								int b =static_cast<int>(static_cast<float>(clr_1.blue())*(t)+static_cast<float>(clr_0.blue()*(1.f-t))+0.5f);
								int a =std::min(clr_0.alpha()+clr_1.alpha(), 255);
								clr_0.setRed(r);
								clr_0.setGreen(g);
								clr_0.setBlue(b);
								clr_0.setAlpha(a);

								Canvas->setPixelColor(layer.widthOffset+x, layer.heightOffset+y, clr_0);
						}
				}
		}
}

bool PaintingArea::createTempTopLayer(int idx){
		if(idx>=0) {
				LayerObject newLayer;
				newLayer.alpha = 255;
				newLayer.height = layerBundle[static_cast<unsigned long long>(idx)].height;
				newLayer.width = layerBundle[static_cast<unsigned long long>(idx)].width;
				newLayer.heightOffset = layerBundle[static_cast<unsigned long long>(idx)].heightOffset;
				newLayer.widthOffset = layerBundle[static_cast<unsigned long long>(idx)].widthOffset;
				newLayer.image = layerBundle[static_cast<unsigned long long>(idx)].image->getDeepCopy();
				layerBundle.insert(layerBundle.begin()+idx+1,newLayer);
				return true;
		}
		return false;
}

IntelliTool* PaintingArea::copyActiveTool(){
		switch(Tool->getTooltype()) {
		case IntelliTool::Tooltype::CIRCLE: return new IntelliToolCircle(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::FLOODFILL: return new IntelliToolFloodFill(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::LINE: return new IntelliToolLine(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::PEN: return new IntelliToolPen(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::PLAIN: return new IntelliToolPlainTool(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::POLYGON: return new IntelliToolPolygon(this,&colorPicker, &Toolsettings);
		case IntelliTool::Tooltype::RECTANGLE: return new IntelliToolRectangle(this,&colorPicker, &Toolsettings);
		default: return nullptr;
		}
}

int PaintingArea::getNumberOfActiveLayer(){
		return activeLayer;
}

IntelliImage* PaintingArea::getImageOfActiveLayer(){
		if(activeLayer<0) {
				return nullptr;
		}
		return layerBundle[activeLayer].image;
}
