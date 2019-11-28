#ifndef INTELLIRASTER_H
#define INTELLIRASTER_H

#include"Image/IntelliImage.h"

class IntelliRasterImage : public IntelliImage{

public:
    IntelliRasterImage(int weight, int height);
    virtual ~IntelliRasterImage() override;

    //returns the filtered output
    virtual QImage getDisplayable(const QSize& displaySize) override;
    virtual QImage getDisplayable() override;


    //sets the data for the visible image
    virtual void setPolygon(const std::vector<QPoint>& polygonData) override;
};

#endif
