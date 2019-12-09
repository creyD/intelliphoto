#ifndef INTELLIIMAGE_H
#define INTELLIIMAGE_H

#include<QImage>
#include<QPoint>
#include<QColor>
#include<QSize>
#include<QWidget>
#include<vector>

enum class ImageType{
    Raster_Image,
    Shaped_Image
};

class IntelliTool;

class IntelliImage{
    friend IntelliTool;
protected:
    void resizeImage(QImage *image, const QSize &newSize);
    virtual void calculateVisiblity()=0;

    QImage imageData;

    //calculate with polygon
public:
    IntelliImage(int weight, int height);
    virtual ~IntelliImage() = 0;

    //start on top left
        //TODO give tool refrence of image, -> funtkions will not be needed
        virtual void drawPixel(const QPoint &p1, const QColor& color);
        virtual void drawLine(const QPoint &p1, const QPoint& p2, const QColor& color, const int& penWidth);
        virtual void floodFill(const QColor& color);

    //returns the filtered output
    virtual QImage getDisplayable(const QSize& displaySize, int alpha)=0;
    virtual QImage getDisplayable(int alpha=255)=0;

    //returns the filtered output

    //sets the data for the visible image
    virtual void setPolygon(const std::vector<QPoint>& polygonData)=0;


    //loads an image to the ColorBuffer
    virtual bool loadImage(const QString &fileName);
};

#endif
