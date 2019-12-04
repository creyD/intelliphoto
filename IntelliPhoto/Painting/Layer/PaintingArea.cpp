// ---------- PaintingArea.cpp ----------

#include <QtWidgets>
#include <QRect>
#include "PaintingArea.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"

#include <vector>
#include <QPoint>

PaintingArea::PaintingArea(int maxWidth, int maxHeight, QWidget *parent)
    :QWidget(parent){
    this->setUp(maxWidth, maxHeight);

    //tetsing
    this->addLayer(200,200,0,0);
    this->addLayer(200,200,201,201);
}




void PaintingArea::setUp(int maxWidth, int maxHeight){

    //set standart parameter
    this->maxWidth = maxWidth;
    this->maxHeight = maxHeight;
    Canvas = new QImage(maxWidth,maxHeight, QImage::Format_ARGB32);
    Canvas->fill(Qt::GlobalColor::white);

    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
}

void PaintingArea::addLayer(int width, int height, int widthOffset, int heightOffset, ImageType type){
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
}

void PaintingArea::deleteLayer(int index){
    if(index<layerStructure.size()){
        this->layerStructure.erase(layerStructure.begin()+index);
        if(activeLayer>=index){
            activeLayer--;
        }
    }
}

void PaintingArea::setLayerToActive(int index) {
    if(index<layerStructure.size()){
        this->activeLayer=index;
    }
}

void PaintingArea::setAlphaToLayer(int index, int alpha){
    if(index<layerStructure.size()){
        layerStructure[index].alpha=alpha;
    }
}

// Used to load the image and place it in the widget
bool PaintingArea::openImage(const QString &fileName)
{
    if(this->activeLayer==-1){
        return false;
    }
    IntelliImage* active = layerStructure[activeLayer].image;
    bool open = active->loadImage(fileName);
    update();
    return open;
}

// Save the current image
bool PaintingArea::saveImage(const QString &fileName, const char *fileFormat)
{
    if(this->activeLayer==-1){
        return false;
    }
    // Created to hold the image

    for(size_t i=0; i<layerStructure.size(); i++){
        LayerObject layer;
        QImage cpy = layer.image->getDisplayable(layer.alpha);
        //TODO draw cpy to CANVAS
    }

    //if (Canvas.save(fileName, fileFormat)) {
    //    return true;
    //} else {
    //    return false;
    //}
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
void PaintingArea::clearImage()
{
   if(this->activeLayer==-1){
       return;
   }
   IntelliImage* active = layerStructure[activeLayer].image;
   active->floodFill(qRgb(255, 255, 255));

   update();
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
        IntelliImage* active = layerStructure[activeLayer].image;

        int x = static_cast<int>(event->x()*static_cast<float>(active->x())/static_cast<float>(size().width()));
        int y = static_cast<int>(event->y()*static_cast<float>(active->y())/static_cast<float>(size().height()));
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
        IntelliImage* active = layerStructure[activeLayer].image;

        int x = static_cast<int>(event->x()*static_cast<float>(active->x())/static_cast<float>(size().width()));
        int y = static_cast<int>(event->y()*static_cast<float>(active->y())/static_cast<float>(size().height()));

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
        IntelliImage* active = layerStructure[activeLayer].image;

        int x = static_cast<int>(event->x()*static_cast<float>(active->x())/static_cast<float>(size().width()));
        int y = static_cast<int>(event->y()*static_cast<float>(active->y())/static_cast<float>(size().height()));

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
    if(this->activeLayer==-1){
        return;
    }
    LayerObject active = layerStructure[activeLayer];

    QPainter painter(this);
    QRect dirtyRec = event->rect();
    painter.drawImage(dirtyRec, active.image->getDisplayable(dirtyRec.size(), active.alpha), dirtyRec);
    update();
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void PaintingArea::resizeEvent(QResizeEvent *event)
{
    if(this->activeLayer==-1){
        return;
    }
    LayerObject active = layerStructure[activeLayer];

    QPainter painter(this);
    QRect dirtyRec(QPoint(0,0), event->size());
    painter.drawImage(dirtyRec, active.image->getDisplayable(event->size(), active.alpha), dirtyRec);
    update();
}

void PaintingArea::drawLineTo(const QPoint &endPoint)
{
    //// Used to draw on the widget
    if(this->activeLayer==-1){
        return;
    }
    LayerObject active = layerStructure[activeLayer];

    active.image->drawLine(lastPoint, endPoint,myPenColor, myPenWidth);
    lastPoint = endPoint;
    update();
}

void PaintingArea::resizeImage(QImage *image_res, const QSize &newSize){
    image_res->scaled(newSize,Qt::IgnoreAspectRatio);
}

