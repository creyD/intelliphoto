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

LayerObject::LayerObject(){

}

LayerObject::LayerObject(const LayerObject& layer){
    if(layer.image->getTypeOfImage()==ImageType::RASTERIMAGE){
        this->image = new IntelliRasterImage(*dynamic_cast<IntelliRasterImage*>(layer.image));
    }else if(layer.image->getTypeOfImage()==ImageType::SHAPEDIMAGE){
        this->image = new IntelliShapedImage(*dynamic_cast<IntelliShapedImage*>(layer.image));
    }
    this->width = layer.width;
    this->height = layer.height;
    this->widthOffset = layer.widthOffset;
    this->heightOffset = layer.heightOffset;
    this->alpha = layer.alpha;
}

PaintingArea::PaintingArea(int maxWidth, int maxHeight, QWidget*parent)
		: QWidget(parent){
		this->Tool = nullptr;
		this->setLayerDimensions(maxWidth, maxHeight);

		activeLayer = -1;
}

PaintingArea::~PaintingArea(){
		delete Tool;
}

void PaintingArea::setRenderSettings(bool isFastRenderingOn){
		bool ToolIsActive;

		if(Tool!=nullptr) {
				ToolIsActive = Tool->getIsDrawing();
		}
		else{
				ToolIsActive = false;
		}
		if(isFastRenderingOn != renderSettings.isFastRenderering() && !ToolIsActive) {
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

int PaintingArea::addLayer(int width, int height, int widthOffset, int heightOffset, ImageType type){
		LayerObject newLayer;
		updateTools();
		newLayer.width = width;
		newLayer.height = height;
		newLayer.widthOffset = widthOffset;
		newLayer.heightOffset = heightOffset;
        if(type==ImageType::RASTERIMAGE) {
				newLayer.image = new IntelliRasterImage(width,height,renderSettings.isFastRenderering());
        }else if(type==ImageType::SHAPEDIMAGE) {
				newLayer.image = new IntelliShapedImage(width, height, renderSettings.isFastRenderering());
		}
		newLayer.alpha = 255;
		this->layerBundle.push_back(newLayer);
		activeLayer = static_cast<int>(layerBundle.size()) - 1;
        historyadd();
		return activeLayer;
}


void PaintingArea::deleteLayer(int idx, bool isTool){
		if(!isTool) {
				updateTools();
		}
		if(idx<static_cast<int>(layerBundle.size())&&idx>=0) {
				this->layerBundle.erase(layerBundle.begin() + idx);
				if(activeLayer>=idx) {
						activeLayer--;
				}
				if(activeLayer < 0 && layerBundle.size()) {
						activeLayer = 0;
				}
		}
}

void PaintingArea::slotDeleteActiveLayer(){
		if(activeLayer>=0 && activeLayer < static_cast<int>(layerBundle.size())) {
				this->layerBundle.erase(layerBundle.begin() + activeLayer);
				activeLayer--;
		}
        historyadd();
}

void PaintingArea::setLayerActive(int idx){
		updateTools();
		if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
				this->activeLayer = idx;
		}
}

void PaintingArea::setLayerAlpha(int idx, int alpha){
		if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
				if(alpha>=0 && alpha<=255) {
						layerBundle[static_cast<size_t>(idx)].alpha = alpha;
				}
		}
}
void PaintingArea::setPolygon(int idx){
		if(idx>=0&&idx<static_cast<int>(layerBundle.size())) {
                if(layerBundle[static_cast<size_t>(idx)].image->getTypeOfImage()==ImageType::SHAPEDIMAGE) {
						delete this->Tool;
						this->Tool = new IntelliToolPolygon(this,&colorPicker,&Toolsettings, true);
						isSettingPolygon = true;
						this->DummyGui->setToolWidth(5);
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

void PaintingArea::movePositionActive(int x, int y){
		updateTools();
		layerBundle[static_cast<size_t>(activeLayer)].widthOffset += x;
		layerBundle[static_cast<size_t>(activeLayer)].heightOffset += y;
        historyadd();
}

void PaintingArea::moveActiveLayer(int idx){
		updateTools();
		if(idx==1) {
				this->selectLayerUp();
		}else if(idx==-1) {
				this->selectLayerDown();
		}
		DummyGui->UpdateGui();
        historyadd();
}

void PaintingArea::slotActivateLayer(int a){
		updateTools();
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
        return this->layerBundle[static_cast<size_t>(activeLayer)].width;
}

int PaintingArea::getHeightOfActive(){
        return this->layerBundle[static_cast<size_t>(activeLayer)].height;
}

int PaintingArea::getMaxWidth(){
		return this->maxWidth;
}

int PaintingArea::getMaxHeight(){
		return this->maxHeight;
}

ImageType PaintingArea::getTypeOfImageRealLayer(){
        return this->layerBundle[static_cast<size_t>(activeLayer)].image->getTypeOfImage();
}

std::vector<QPoint> PaintingArea::getPolygonDataOfRealLayer(){
        return this->layerBundle[static_cast<size_t>(activeLayer)].image->getPolygonData();
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
        int x = event->x() - layerBundle[static_cast<size_t>(activeLayer)].widthOffset;
        int y = event->y() - layerBundle[static_cast<size_t>(activeLayer)].heightOffset;
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
        int x = event->x() - layerBundle[static_cast<size_t>(activeLayer)].widthOffset;
        int y = event->y() - layerBundle[static_cast<size_t>(activeLayer)].heightOffset;
		Tool->onMouseMoved(x, y);
		update();
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent*event){
		if(this->activeLayer < 0)
				return;
		if(Tool == nullptr)
				return;
        int x = event->x() - layerBundle[static_cast<size_t>(activeLayer)].widthOffset;
        int y = event->y() - layerBundle[static_cast<size_t>(activeLayer)].heightOffset;
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
						Tool->onWheelScrolled(numSteps.y() * -1);
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

void PaintingArea::selectLayerUp(){
		updateTools();
		if(activeLayer != -1 && static_cast<size_t>(activeLayer)<layerBundle.size() - 1) {
				std::swap(layerBundle[static_cast<size_t>(activeLayer)], layerBundle[static_cast<size_t>(activeLayer + 1)]);
				activeLayer++;
		}
}

void PaintingArea::selectLayerDown(){
		updateTools();
		if(activeLayer>0) {
                std::swap(layerBundle[static_cast<size_t>(activeLayer)], layerBundle[static_cast<size_t>(activeLayer - 1)]);
				activeLayer--;
		}
}

void PaintingArea::drawLayers(bool forSaving){
		if(forSaving) {
				Canvas->fill(Qt::GlobalColor::transparent);
		}else{
				Canvas->fill(Qt::GlobalColor::black);
		}
		for(size_t i = 0; i<layerBundle.size(); i++) {
				LayerObject layer = layerBundle[i];
				QImage cpy = layer.image->getDisplayable(layer.alpha);
				QColor clr_0;
				QColor clr_1;
				for(int y = 0; y<layer.height; y++) {
						if(layer.heightOffset + y<0) continue;
						if(layer.heightOffset + y>=maxHeight) break;
						for(int x = 0; x<layer.width; x++) {
								if(layer.widthOffset + x<0) continue;
								if(layer.widthOffset + x>=maxWidth) break;
								clr_0 = Canvas->pixelColor(layer.widthOffset + x, layer.heightOffset + y);
								clr_1 = cpy.pixelColor(x,y);
								float t = static_cast<float>(clr_1.alpha()) / 255.f;
								int r = static_cast<int>(static_cast<float>(clr_1.red()) * (t) + static_cast<float>(clr_0.red()) * (1.f - t) + 0.5f);
								int g = static_cast<int>(static_cast<float>(clr_1.green()) * (t) + static_cast<float>(clr_0.green()) * (1.f - t) + 0.5f);
								int b = static_cast<int>(static_cast<float>(clr_1.blue()) * (t) + static_cast<float>(clr_0.blue() * (1.f - t)) + 0.5f);
								int a = std::min(clr_0.alpha() + clr_1.alpha(), 255);
								clr_0.setRed(r);
								clr_0.setGreen(g);
								clr_0.setBlue(b);
								clr_0.setAlpha(a);

								Canvas->setPixelColor(layer.widthOffset + x, layer.heightOffset + y, clr_0);
						}
				}
		}
}

bool PaintingArea::createTempTopLayer(int idx){
		if(idx>=0) {
				LayerObject newLayer;
				newLayer.alpha = 255;
                newLayer.height = layerBundle[static_cast<size_t>(idx)].height;
                newLayer.width = layerBundle[static_cast<size_t>(idx)].width;
                newLayer.heightOffset = layerBundle[static_cast<size_t>(idx)].heightOffset;
                newLayer.widthOffset = layerBundle[static_cast<size_t>(idx)].widthOffset;
                newLayer.image = layerBundle[static_cast<size_t>(idx)].image->getDeepCopy();
				layerBundle.insert(layerBundle.begin() + idx + 1,newLayer);
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
		return layerBundle[static_cast<size_t>(activeLayer)].image;
}

QImage PaintingArea::getImageDataOfActiveLayer(){
		QImage returnImage;
		if(activeLayer<0) {
				returnImage = QImage(QSize(10,10),QImage::Format_ARGB32);
				returnImage.fill(QColor(255,255,255,255));
		}
		else{
				returnImage = layerBundle[static_cast<size_t>(activeLayer)].image->getImageData();
				if(renderSettings.isFastRenderering()) {
						returnImage = returnImage.convertToFormat(QImage::Format_ARGB32);
				}
		}
		return returnImage;
}

void PaintingArea::updateTools(){
		if(Tool!=nullptr) {
				if(Tool->getIsDrawing()) {
						IntelliTool* temp = copyActiveTool();
						delete this->Tool;
						this->Tool = temp;
				}
				if(isSettingPolygon) {
						delete this->Tool;
						this->Tool = nullptr;
						isSettingPolygon = false;
				}
		}
}

void PaintingArea::historyadd(){

    if (++historyPresent == 100){
        historyPresent = 0;
    }
    historyMaxFuture = historyPresent;
    if (historyPresent == historyMaxPast)
        if (++historyMaxPast == 100)
            historyMaxPast = 0;
    history[static_cast<size_t>(historyPresent)] = layerBundle;
}

void PaintingArea::historyGoBack(){
    if (historyPresent != historyMaxPast){
        if (--historyPresent == -1)
            historyPresent = 99;
        layerBundle = history[static_cast<size_t>(historyPresent)];
    }
}

void PaintingArea::historyGoForward(){
    if (historyPresent != historyMaxFuture){
        if (++historyPresent == 100)
            historyPresent = 0;
        layerBundle = history[static_cast<size_t>(historyPresent)];
    }
}
