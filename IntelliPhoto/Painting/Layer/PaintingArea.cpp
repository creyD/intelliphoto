// ---------- PaintingArea.cpp ----------

#include <QtWidgets>
#include "PaintingArea.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedimage.h"

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget(parent)
{
    //create standart image
    this->image = new IntelliRasterimage(400,200);

    this->setUp();
}

PaintingArea::PaintingArea(int width, int height, ImageType type, QWidget *parent)
    : QWidget(parent){
    if(type==ImageType::Raster_Image){
        this->image = new IntelliRasterimage(width, height);
    }else if(type==ImageType::Shaped_Image){
        this->image = new IntelliShapedImage(width, height);
    }else{
        qDebug() << "No valid Image type error";
        return;
    }
}

void PaintingArea::setUp(){
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
}

// Used to load the image and place it in the widget
bool PaintingArea::openImage(const QString &fileName)
{
    return image->loadImage(fileName);
}

// Save the current image
bool PaintingArea::saveImage(const QString &fileName, const char *fileFormat)
{
    // Created to hold the image
    QImage visibleImage = image->getDisplayable(size());
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
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
    modified = true;
    update();
}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

// If the button is released we set variables to stop drawing
void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void PaintingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    //painter.drawImage(dirtyRect, image, dirtyRect);
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
void PaintingArea::resizeEvent(QResizeEvent *event)
{
    //resizing done here
    //if (width() > image.width() || height() > image.height()) {
    //    int newWidth = qMax(width() + 128, image.width());
    //    int newHeight = qMax(height() + 128, image.height());
    //    resizeImage(&image, QSize(newWidth, newHeight));
    //    update();
    //}
    QWidget::resizeEvent(event);
}

void PaintingArea::drawLineTo(const QPoint &endPoint)
{
    // Used to draw on the widget
    image->drawLine(lastPoint, endPoint,myPenColor, myPenWidth);

    // Set that the image hasn't been saved
    modified = true;

    int rad = (myPenWidth / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    // Update the last position where we left off drawing
    lastPoint = endPoint;
}

// When the app is resized create a new image using
// the changes made to the image
void PaintingArea::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

