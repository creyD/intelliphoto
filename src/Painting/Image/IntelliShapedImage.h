#ifndef INTELLISHAPE_H
#define INTELLISHAPE_H

#include"Image/IntelliImage.h"

class IntelliShapedImage : public IntelliImage{
    friend IntelliTool;
protected:
    virtual void calculateVisiblity() override;
    std::vector<QPoint> polygonData;
public:
    IntelliShapedImage(int weight, int height);
    virtual ~IntelliShapedImage() override;

    //returns the filtered output
    virtual QImage getDisplayable(const QSize& displaySize, int alpha=255) override;
    virtual QImage getDisplayable(int alpha=255) override;

    //gets a copy of the image !allocated
    virtual IntelliImage* getDeepCopy() override;

    //sets the data for the visible image
    virtual void setPolygon(const std::vector<QPoint>& polygonData) override;
};

#endif
