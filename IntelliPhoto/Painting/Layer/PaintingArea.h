
#ifndef PaintingArea_H
#define PaintingArea_H

#include <QColor>
#include <QImage>
#include"Image/IntelliImage.h"
#include <QPoint>
#include <QWidget>
#include <QList>

class PaintingArea : public QWidget
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    PaintingArea(int maxWidth=1000, int maxHeight=800, QWidget *parent = nullptr);

    // Handles all events
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);

    void addLayer(int width, int height, int widthOffset=0, int heightOffset=0, ImageType type = ImageType::Raster_Image);
    void deleteLayer(int index);
    void setLayerToActive(int index);
    void setAlphaToLayer(int index, int alpha);

    // Has the image been modified since last save
    bool isModified() const { return modified; }

    void setPenColor(const QColor &newColor);
    QColor penColor() const { return myPenColor; }

    void setPenWidth(int newWidth);
    int penWidth() const { return myPenWidth; }

public slots:

    // Events to handle
    void clearImage();

    //void setUp helper for konstruktor
    void setUp(int maxWidth, int maxHeight);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Updates the painting area where we are painting
    void paintEvent(QPaintEvent *event) override;

    // Makes sure the area we are drawing on remains
    // as large as the widget
    void resizeEvent(QResizeEvent *event) override;

private:
    struct LayerObject{
        IntelliImage* image;
        int width;
        int height;
        int widthOffset;
        int heightOffset;
        int alpha=255;
    };

    QImage* Canvas;
    int maxWidth;
    int maxHeight;

    std::vector<LayerObject> layerStructure;
    int activeLayer=-1;

    void assembleLayers();

    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image_res, const QSize &newSize);

    // Will be marked true or false depending on if
    // we have saved after a change
    bool modified=false;

    // Marked true or false depending on if the user
    // is drawing
    bool scribbling;

    // Holds the current pen width & color
    int myPenWidth;
    QColor myPenColor;

    // Stores the image being drawn

    // Stores the location at the current mouse event
    QPoint lastPoint;
};

#endif

