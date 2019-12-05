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

    this->setUp();
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
        this->image = new IntelliShapedImage(width, height);
    }else{
        qDebug() << "No valid Image type error";
        return;
    }
    this->setUp();
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
    // Created to hold the image
    QImage visibleImage = image->getDisplayable();

    if(!std::strcmp(fileFormat,"PNG")){
        visibleImage = visibleImage.convertToFormat(QImage::Format_Indexed8);
        fileFormat = "png";
    }

    if (visibleImage.save(fileName, fileFormat)) {
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
void PaintingArea::clearImage()
{
    image->floodFill(qRgb(255, 255, 255));
    update();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int x = event->x()*(float)image->x()/(float)size().width();
        int y = event->y()*(float)image->y()/(float)size().height();
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
        int x = event->x()*(float)image->x()/(float)size().width();
        int y = event->y()*(float)image->y()/(float)size().height();
        drawLineTo(QPoint(x,y));
        update();
    }
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        int x = event->x()*(float)image->x()/(float)size().width();
        int y = event->y()*(float)image->y()/(float)size().height();
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
    QPainter painter(this);
    QRect dirtyRec = event->rect();
    painter.drawImage(dirtyRec, image->getDisplayable(dirtyRec.size()), dirtyRec);
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

