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

PaintingArea::PaintingArea(int maxWidth, int maxHeight, QWidget *parent)
    :QWidget(parent){
    this->Tool = nullptr;
    this->setUp(maxWidth, maxHeight);
    this->addLayer(200,200,0,0,ImageType::Shaped_Image);
    layerBundle[0].image->drawPlain(QColor(0,0,255,255));
    std::vector<QPoint> polygon;
    polygon.push_back(QPoint(100,000));
    polygon.push_back(QPoint(200,100));
    polygon.push_back(QPoint(100,200));
    polygon.push_back(QPoint(000,100));
    layerBundle[0].image->setPolygon(polygon);

    this->addLayer(200,200,150,150);
    layerBundle[1].image->drawPlain(QColor(0,255,0,255));
    layerBundle[1].alpha=200;

    activeLayer=0;
}

PaintingArea::~PaintingArea(){
    delete Tool;
}

void PaintingArea::setUp(int maxWidth, int maxHeight){
    //set standart parameter
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    Canvas = new QImage(maxWidth,maxHeight, QImage::Format_ARGB32);

    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

}

int PaintingArea::addLayer(int width, int height, int widthOffset, int heightOffset, ImageType type){
    LayerObject newLayer;
    newLayer.width = width;
    newLayer.height = height;
    newLayer.widthOffset = widthOffset;
    newLayer.hightOffset = heightOffset;
    if(type==ImageType::Raster_Image){
        newLayer.image = new IntelliRasterImage(width,height);
    }else if(type==ImageType::Shaped_Image){
        newLayer.image = new IntelliShapedImage(width, height);
    }
    newLayer.alpha = 255;
    this->layerBundle.push_back(newLayer);
    return static_cast<int>(layerBundle.size())-1;
}


void PaintingArea::deleteLayer(int index){
    if(index<static_cast<int>(layerBundle.size())){
        this->layerBundle.erase(layerBundle.begin()+index);
        if(activeLayer>=index){
            activeLayer--;
        }
    }
}

void PaintingArea::slotDeleteActiveLayer(){
    if(activeLayer>=0 && activeLayer < static_cast<int>(layerBundle.size())){
        this->layerBundle.erase(layerBundle.begin()+activeLayer);
        activeLayer--;
    }
}

void PaintingArea::setLayerToActive(int index){
    if(index>=0&&index<static_cast<int>(layerBundle.size())){
        this->activeLayer=index;
    }
}

void PaintingArea::setAlphaOfLayer(int index, int alpha){
    if(index>=0&&index<static_cast<int>(layerBundle.size())){
        layerBundle[static_cast<size_t>(index)].alpha=alpha;
    }
}

// Used to load the image and place it in the widget
bool PaintingArea::open(const QString &fileName){
    if(this->activeLayer==-1){
        return false;
    }
    IntelliImage* active = layerBundle[static_cast<size_t>(activeLayer)].image;
    bool open = active->loadImage(fileName);
    active->calculateVisiblity();
    update();
    return open;
}

// Save the current image
bool PaintingArea::save(const QString &fileName, const char *fileFormat){
    if(layerBundle.size()==0){
        return false;
    }
    this->assembleLayers(true);

    if(!strcmp(fileFormat,"PNG")){
        QImage visibleImage = Canvas->convertToFormat(QImage::Format_Indexed8);
        fileFormat = "png";
        if (visibleImage.save(fileName, fileFormat)) {
            return true;
        } else {
            return false;
        }
    }

    if (Canvas->save(fileName, fileFormat)) {
        return true;
    } else {
        return false;
    }
}

// Color the image area with white
void PaintingArea::floodFill(int r, int g, int b, int a){
    if(this->activeLayer==-1){
        return;
    }
    IntelliImage* active = layerBundle[static_cast<size_t>(activeLayer)].image;
    active->drawPlain(QColor(r, g, b, a));
    update();
}

void PaintingArea::movePositionActive(int x, int y){
    layerBundle[static_cast<size_t>(activeLayer)].widthOffset += x;
    layerBundle[static_cast<size_t>(activeLayer)].hightOffset += y;
}

void PaintingArea::moveActiveLayer(int idx){
    if(idx==1){
        this->activateUpperLayer();
    }else if(idx==-1){
        this->activateLowerLayer();
    }
}

void PaintingArea::slotActivateLayer(int a){
    if(a>=0 && a < static_cast<int>(layerBundle.size())){
        this->setLayerToActive(a);
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

void PaintingArea::colorPickerSwitchColor(){
    this->colorPicker.switchColors();
}

void PaintingArea::createPenTool(){
    delete this->Tool;
    Tool = new IntelliToolPen(this, &colorPicker);
}

void PaintingArea::createPlainTool(){
    delete this->Tool;
    Tool = new IntelliToolPlainTool(this, &colorPicker);
}

void PaintingArea::createLineTool(){
    delete this->Tool;
    Tool = new IntelliToolLine(this, &colorPicker);
}

void PaintingArea::createRectangleTool(){
    delete this->Tool;
    Tool = new IntelliToolRectangle(this, &colorPicker);
}

void PaintingArea::createCircleTool(){
    delete this->Tool;
    Tool = new IntelliToolCircle(this, &colorPicker);
}
void PaintingArea::createPolygonTool(){
    delete this->Tool;
    Tool = new IntelliToolPolygon(this, &colorPicker);
}

void PaintingArea::createFloodFillTool(){
    delete this->Tool;
    Tool = new IntelliToolFloodFill(this, &colorPicker);
}

int PaintingArea::getWidthOfActive(){
    return this->layerBundle[activeLayer].width;
}

int PaintingArea::getHeightOfActive(){
    return this->layerBundle[activeLayer].height;
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent *event){
    if(Tool == nullptr)
        return;
    int x = event->x()-layerBundle[activeLayer].widthOffset;
    int y = event->y()-layerBundle[activeLayer].hightOffset;
    if(event->button() == Qt::LeftButton){
        Tool->onMouseLeftPressed(x, y);
    }else if(event->button() == Qt::RightButton){
        Tool->onMouseRightPressed(x, y);
    }
    update();
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void PaintingArea::mouseMoveEvent(QMouseEvent *event){
    if(Tool == nullptr)
        return;
    int x = event->x()-layerBundle[activeLayer].widthOffset;
    int y = event->y()-layerBundle[activeLayer].hightOffset;
    Tool->onMouseMoved(x, y);
    update();
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent *event){
    if(Tool == nullptr)
        return;
    int x = event->x()-layerBundle[activeLayer].widthOffset;
    int y = event->y()-layerBundle[activeLayer].hightOffset;
    if(event->button() == Qt::LeftButton){
        Tool->onMouseLeftReleased(x, y);
    }else if(event->button() == Qt::RightButton){
        Tool->onMouseRightReleased(x, y);
    }
    update();
}

void PaintingArea::wheelEvent(QWheelEvent *event){
    QPoint numDegrees = event->angleDelta() / 8;
    if(!numDegrees.isNull()){
        QPoint numSteps = numDegrees / 15;
        Tool->onWheelScrolled(numSteps.y()*-1);
    }
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void PaintingArea::paintEvent(QPaintEvent *event){
    this->assembleLayers();

    QPainter painter(this);
    QRect dirtyRec = event->rect();
    painter.drawImage(dirtyRec, *Canvas, dirtyRec);
    update();
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void PaintingArea::resizeEvent(QResizeEvent *event){
    //TODO wait till tool works
    update();
}

void PaintingArea::resizeImage(QImage *image_res, const QSize &newSize){
    //TODO implement
}

void PaintingArea::activateUpperLayer(){
    if(activeLayer!=-1 && activeLayer<layerBundle.size()-1){
        std::swap(layerBundle[activeLayer], layerBundle[activeLayer+1]);
        activeLayer++;
    }
}

void PaintingArea::activateLowerLayer(){
    if(activeLayer!=-1 && activeLayer>0){
        std::swap(layerBundle[activeLayer], layerBundle[activeLayer-1]);
        activeLayer--;
    }
}

void PaintingArea::assembleLayers(bool forSaving){
    if(forSaving){
        Canvas->fill(Qt::GlobalColor::transparent);
    }else{
        Canvas->fill(Qt::GlobalColor::black);
    }
    for(size_t i=0; i<layerBundle.size(); i++){
        LayerObject layer = layerBundle[i];
        QImage cpy = layer.image->getDisplayable(layer.alpha);
        QColor clr_0;
        QColor clr_1;
        for(int y=0; y<layer.height; y++){
            if(layer.hightOffset+y<0) continue;
            if(layer.hightOffset+y>=maxHeight) break;
            for(int x=0; x<layer.width; x++){
                if(layer.widthOffset+x<0) continue;
                if(layer.widthOffset+x>=maxWidth) break;
                clr_0=Canvas->pixelColor(layer.widthOffset+x, layer.hightOffset+y);
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

                Canvas->setPixelColor(layer.widthOffset+x, layer.hightOffset+y, clr_0);
            }
        }
    }
}

void PaintingArea::createTempLayerAfter(int idx){
    if(idx>=0){
        LayerObject newLayer;
        newLayer.alpha = 255;
        newLayer.height = layerBundle[idx].height;
        newLayer.width = layerBundle[idx].width;
        newLayer.hightOffset = layerBundle[idx].hightOffset;
        newLayer.widthOffset = layerBundle[idx].widthOffset;
        newLayer.image = layerBundle[idx].image->getDeepCopy();
        layerBundle.insert(layerBundle.begin()+idx+1,newLayer);
    }
}
