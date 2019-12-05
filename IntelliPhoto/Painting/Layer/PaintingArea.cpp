// ---------- PaintingArea.cpp ----------

#include <QtWidgets>
#include<QRect>
#include "PaintingArea.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"

#include<vector>
#include<QPoint>

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget(parent)
{
    //create standart image
    this->image = new IntelliRasterImage(400,400);
    std::vector<QPoint> poly;
    poly.push_back(QPoint(200,0));
    poly.push_back(QPoint(400,300));
    poly.push_back(QPoint(0,300));
    poly.push_back(QPoint(200,0));
    image->setPolygon(poly);

    //tetsing
    this->addLayer(200,200,0,0,ImageType::Shaped_Image);
    layerStructure[0].image->floodFill(QColor(255,0,0,255));
    std::vector<QPoint> polygon;
    polygon.push_back(QPoint(100,0));
    polygon.push_back(QPoint(200,200));
    polygon.push_back(QPoint(0,200));
    polygon.push_back(QPoint(100,0));
    layerStructure[0].image->setPolygon(polygon);

    this->addLayer(200,200,150,150);
    layerStructure[1].image->floodFill(QColor(0,255,0,255));
    layerStructure[1].alpha=200;
    activeLayer=1;
}

void PaintingArea::setUp(){
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;

}

PaintingArea::PaintingArea(int width, int height, ImageType type, QWidget *parent)
    : QWidget(parent){
    if(type==ImageType::Raster_Image){
        this->image = new IntelliRasterImage(width, height);
    }else if(type==ImageType::Shaped_Image){
        newLayer.image = new IntelliShapedImage(width, height);
    }
    newLayer.alpha = 255;
    this->layerStructure.push_back(newLayer);

}

void PaintingArea::deleteLayer(int index){
    if(index<layerStructure.size()){
        this->layerStructure.erase(layerStructure.begin()+index);
        if(activeLayer>=index){
            activeLayer--;
        }
    }
    this->setUp();
}


QPixmap PaintingArea::getAsPixmap(){
    assembleLayers();
    return QPixmap::fromImage(*Canvas);
}

// Used to load the image and place it in the widget
bool PaintingArea::openImage(const QString &fileName)
{
    bool open = image->loadImage(fileName);
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

    if (Canvas->save(fileName, fileFormat)) {
        return true;
    } else {
        return false;
    }
}

// Used to change the pen color
void PaintingArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

// Used to change the pen width
void PaintingArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Color the image area with white
void PaintingArea::clearImage(int r, int g, int b){
    if(this->activeLayer==-1){
        return;
    }
    IntelliImage* active = layerStructure[activeLayer].image;
    active->floodFill(QColor(r, g, b, 255));

    update();
}

void PaintingArea::activate(int a){
    this->setLayerToActive(a);
}

void PaintingArea::setAlpha(int a){
    if(activeLayer>=0){
        layerStructure[activeLayer].alpha=a;
    }
}

void PaintingArea::getMoveUp(int a){
    layerStructure[activeLayer].heightOffset-=a;
}

void PaintingArea::getMoveDown(int a){
    layerStructure[activeLayer].heightOffset+=a;
}

void PaintingArea::getMoveRight(int a){
    layerStructure[activeLayer].widthOffset+=a;
}

void PaintingArea::getMoveLeft(int a){
    layerStructure[activeLayer].widthOffset-=a;
}

void PaintingArea::getMoveLayerUp(){
    if(activeLayer<layerStructure.size() && activeLayer>=0){
        std::swap(layerStructure[activeLayer], layerStructure[activeLayer+1]);
        activeLayer++;
    }
}

void PaintingArea::getMoveLayerDown(){
    if(activeLayer>0){
        std::swap(layerStructure[activeLayer], layerStructure[activeLayer-1]);
        activeLayer--;
    }
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(this->activeLayer==-1){
            return;
        }
        LayerObject& active = layerStructure[activeLayer];

        int x = event->x()-active.widthOffset;
        int y = event->y()-active.heightOffset;
        //TODO CALCULATE LAST POINT
        lastPoint=QPoint(x,y);
        scribbling = true;
    }
}


// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling){
        if(this->activeLayer==-1){
            return;
        }
        LayerObject& active = layerStructure[activeLayer];

        int x = event->x()-active.widthOffset;
        int y = event->y()-active.heightOffset;

        //TODO CALCULATE NEW POINT
        drawLineTo(QPoint(x,y));
        update();
    }
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        if(this->activeLayer==-1){
            return;
        }
        LayerObject& active = layerStructure[activeLayer];

        int x = event->x()-active.widthOffset;
        int y = event->y()-active.heightOffset;

        //TODO CALCULATE NEW POINT
        drawLineTo(QPoint(x,y));
        update();
        scribbling = false;
    }
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
    QPainter painter(this);
    QRect dirtyRec(QPoint(0,0), event->size());
    painter.drawImage(dirtyRec, image->getDisplayable(event->size()), dirtyRec);
    update();
    //QWidget::resizeEvent(event);
}

void PaintingArea::drawLineTo(const QPoint &endPoint)
{
    // Used to draw on the widget
    image->drawLine(lastPoint, endPoint,myPenColor, myPenWidth);
    lastPoint = endPoint;
    update();
}

void PaintingArea::resizeImage(QImage *image_res, const QSize &newSize){
    image_res->scaled(newSize,Qt::IgnoreAspectRatio);
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
            for(int x=0; x<layer.width; x++){
                clr_0=Canvas->pixelColor(layer.widthOffset+x, layer.heightOffset+y);
                clr_1=cpy.pixelColor(x,y);
                float t = (float)clr_1.alpha()/255.f;
                int r =(float)clr_1.red()*(t)+(float)clr_0.red()*(1.-t);
                int g =(float)clr_1.green()*(t)+(float)clr_0.green()*(1.-t);
                int b =(float)clr_1.blue()*(t)+(float)clr_0.blue()*(1.-t);
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

