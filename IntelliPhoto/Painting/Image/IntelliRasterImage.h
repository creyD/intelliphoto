#ifndef INTELLIRASTER_H
#define INTELLIRASTER_H

#include"Image/IntelliImage.h"

class IntelliRasterimage : public IntelliImage{
public:
    IntelliRasterimage(int weight, int height);
    virtual ~IntelliRasterimage() override;

    //returns the filtered output
    virtual QImage getDisplayable(const QSize& displaySize) override;

    //sets the data for the visible image
    virtual void setPolygon(const std::vector<QPoint>& polygonData) override;
};

#endif
