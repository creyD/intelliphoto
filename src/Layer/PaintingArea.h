
#ifndef PaintingArea_H
#define PaintingArea_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QList>
#include "Image/IntelliImage.h"
#include "Image/IntelliRasterImage.h"
#include "Image/IntelliShapedImage.h"
#include "Tool/IntelliTool.h"
#include "IntelliHelper/IntelliColorPicker.h"


struct LayerObject{
    IntelliImage* image;
    int width;
    int hight;
    int widthOffset;
    int hightOffset;
    int alpha=255;


};

class PaintingArea : public QWidget
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT
    friend IntelliTool;
public:
    PaintingArea(int maxWidth=600, int maxHeight=600, QWidget *parent = nullptr);
    ~PaintingArea() override;

    // Handles all events
    bool open(const QString &fileName);
    bool save(const QString &fileName, const char *fileFormat);

    int addLayer(int width, int height, int widthOffset=0, int heightOffset=0, ImageType type = ImageType::Raster_Image);
    int addLayerAt(int idx, int width, int height, int widthOffset=0, int heightOffset=0, ImageType type = ImageType::Raster_Image);
    void deleteLayer(int index);
    void setLayerToActive(int index);
    void setAlphaOfLayer(int index, int alpha);
    void floodFill(int r, int g, int b, int a);
    void movePositionActive(int x, int y);
    void moveActiveLayer(int idx);

    //change properties of colorPicker
    void colorPickerSetFirstColor();
    void colorPickerSetSecondColor();
    void colorPickerSwitchColor();

    //create tools
    void createPenTool();
    void createPlainTool();
    void createLineTool();

public slots:

    // Events to handle
    void slotActivateLayer(int a);
    void slotDeleteActiveLayer();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;
    // Updates the painting area where we are painting
    void paintEvent(QPaintEvent *event) override;

    // Makes sure the area we are drawing on remains
    // as large as the widget
    void resizeEvent(QResizeEvent *event) override;

private:
    void setUp(int maxWidth, int maxHeight);
    void activateUpperLayer();
    void activateLowerLayer();


    QImage* Canvas;
    int maxWidth;
    int maxHeight;

    IntelliTool* Tool;
    IntelliColorPicker colorPicker;

    std::vector<LayerObject> layerBundle;
    int activeLayer=-1;

    void assembleLayers(bool forSaving=false);

    void resizeImage(QImage *image_res, const QSize &newSize);


    //Helper for Tool
    void createTempLayerAfter(int idx);
};

#endif

