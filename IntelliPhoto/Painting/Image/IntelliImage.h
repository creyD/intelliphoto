#ifndef INTELLIIMAGE_H
#define INTELLIIMAGE_H

#include<QImage>
#include<QPoint>
#include<QColor>
#include<QSize>
#include<vector>

enum class ImageType{
    Raster_Image,
    Shaped_Image
};

class IntelliImage{
protected:
    void resizeImage(QImage *image, const QSize &newSize);

    QImage imageData;
public:
    IntelliImage(int weight, int height);
    virtual ~IntelliImage() = 0;

    //start on top left
    virtual void drawPixel(const QPoint &p1, const QColor& color);
    virtual void drawLine(const QPoint &p1, const QPoint& p2, const QColor& color, const int& penWidth);
    virtual void floodFill(const QColor& color);

    //returns the filtered output
    virtual QImage getDisplayable(const QSize& displaySize)=0;

    //sets the data for the visible image
    virtual void setPolygon(const std::vector<QPoint>& polygonData)=0;

    virtual bool loadImage(const QString &fileName);
};

#endif
