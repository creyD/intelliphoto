// ---------- PaintingArea.cpp ----------

#include <QtWidgets>
#include <QRect>
#include "string.h"
#include "PaintingArea.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"

#include <vector>
#include <QPoint>


PaintingArea::PaintingArea(int maxWidth, int maxHeight, QWidget *parent)
    :QWidget(parent){
    this->setUp(maxWidth, maxHeight);
    //tetsing
    this->addLayer(200,200,0,0,ImageType::Shaped_Image);
    layerStructure[0].image->floodFill(QColor(255,0,0,255));
    std::vector<QPoint> polygon;
    polygon.push_back(QPoint(100,000));
    polygon.push_back(QPoint(200,100));
    polygon.push_back(QPoint(100,200));
    polygon.push_back(QPoint(000,100));
    layerStructure[0].image->setPolygon(polygon);

    this->addLayer(200,200,150,150);
    layerStructure[1].image->floodFill(QColor(0,255,0,255));
    layerStructure[1].alpha=200;

    activeLayer=1;
}

void PaintingArea::setUp(int maxWidth, int maxHeight){
    //set standart parameter
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    Canvas = new QImage(maxWidth,maxHeight, QImage::Format_ARGB32);

    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
}

int PaintingArea::addLayer(int width, int height, int widthOffset, int heightOffset, ImageType type){
    LayerObject newLayer;
    newLayer.width = width;
    newLayer.height = height;
    newLayer.widthOffset = widthOffset;
    newLayer.heightOffset = heightOffset;
    if(type==ImageType::Raster_Image){
        newLayer.image = new IntelliRasterImage(width,height);
    }else if(type==ImageType::Shaped_Image){
        newLayer.image = new IntelliShapedImage(width, height);
    }
    newLayer.alpha = 255;
    this->layerStructure.push_back(newLayer);
    return static_cast<int>(layerStructure.size())-1;
}

void PaintingArea::deleteLayer(int index){
    if(index<static_cast<int>(layerStructure.size())){
        this->layerStructure.erase(layerStructure.begin()+index);
        if(activeLayer>=index){
            activeLayer--;
        }
    }
}

void PaintingArea::deleteActiveLayer(){
    if(activeLayer>=0 && activeLayer < static_cast<int>(layerStructure.size())){
        this->layerStructure.erase(layerStructure.begin()+activeLayer);
        activeLayer--;
    }
}

void PaintingArea::setLayerToActive(int index) {
    if(index>=0&&index<static_cast<int>(layerStructure.size())){
        this->activeLayer=index;
    }
}

void PaintingArea::setAlphaToLayer(int index, int alpha){
    if(index>=0&&index<static_cast<int>(layerStructure.size())){
        layerStructure[static_cast<size_t>(index)].alpha=alpha;
    }
}


// Used to load the image and place it in the widget
bool PaintingArea::openImage(const QString &fileName)
{
    if(this->activeLayer==-1){
        return false;
    }
    IntelliImage* active = layerStructure[static_cast<size_t>(activeLayer)].image;
    bool open = active->loadImage(fileName);
    update();
    return open;
}

// Save the current image
bool PaintingArea::saveImage(const QString &fileName, const char *fileFormat)
{
    if(layerStructure.size()==0){
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

// Used to change the pen color
void PaintingArea::setPenColor(const QColor &newColor)
{
    //TODO give to Tool
}

// Used to change the pen width
void PaintingArea::setPenWidth(int newWidth)
{
    //TODO give to Tool
}

// Color the image area with white
void PaintingArea::clearImage(int r, int g, int b){
    if(this->activeLayer==-1){
        return;
    }
    IntelliImage* active = layerStructure[static_cast<size_t>(activeLayer)].image;
    active->floodFill(QColor(r, g, b, 255));

    update();
}

void PaintingArea::activate(int a){
    if(a>=0 && a < static_cast<int>(layerStructure.size())){
        this->setLayerToActive(a);
    }
}

void PaintingArea::setAlpha(int a){
    if(activeLayer>=0){
        layerStructure[static_cast<size_t>(activeLayer)].alpha=a;
    }
}

void PaintingArea::getMoveUp(int a){
    layerStructure[static_cast<size_t>(activeLayer)].heightOffset-=a;
}

void PaintingArea::getMoveDown(int a){
    layerStructure[static_cast<size_t>(activeLayer)].heightOffset+=a;
}

void PaintingArea::getMoveRight(int a){
    layerStructure[static_cast<size_t>(activeLayer)].widthOffset+=a;
}

void PaintingArea::getMoveLeft(int a){
    layerStructure[static_cast<size_t>(activeLayer)].widthOffset-=a;
}

void PaintingArea::getMoveLayerUp(){
    if(activeLayer<static_cast<int>(layerStructure.size()-1) && activeLayer>=0){
        std::swap(layerStructure[static_cast<size_t>(activeLayer)], layerStructure[static_cast<size_t>(activeLayer+1)]);
        activeLayer++;
    }
}

void PaintingArea::getMoveLayerDown(){
    if(activeLayer>0){
        std::swap(layerStructure[static_cast<size_t>(activeLayer)], layerStructure[static_cast<size_t>(activeLayer-1)]);
        activeLayer--;
    }
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    //TODO implement in tool
}


// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    //TODO implement in Tool
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    //TODO implement in tool
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void PaintingArea::paintEvent(QPaintEvent *event)
{
    this->assembleLayers();

    QPainter painter(this);
    QRect dirtyRec = event->rect();
    painter.drawImage(dirtyRec, *Canvas, dirtyRec);
    update();
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void PaintingArea::resizeEvent(QResizeEvent *event)
{
    //TODO Doesnt quit work
    update();
}

void PaintingArea::drawLineTo(const QPoint &endPoint)
{

}

void PaintingArea::resizeImage(QImage *image_res, const QSize &newSize){
    //TODO implement
}

void PaintingArea::assembleLayers(bool forSaving){
    if(forSaving){
        Canvas->fill(Qt::GlobalColor::transparent);
    }else{
        Canvas->fill(Qt::GlobalColor::black);
    }
    //TODO interpolation of alpha for saving
    for(size_t i=0; i<layerStructure.size(); i++){
        LayerObject layer = layerStructure[i];
        QImage cpy = layer.image->getDisplayable(layer.alpha);
        QColor clr_0;
        QColor clr_1;
        for(int y=0; y<layer.height; y++){
            if(layer.heightOffset+y<0) continue;
            if(layer.heightOffset+y>=maxHeight) break;
            for(int x=0; x<layer.width; x++){
                if(layer.widthOffset+x<0) continue;
                if(layer.heightOffset+y>=maxWidth) break;
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
