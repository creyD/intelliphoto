#ifndef INTELLITOOLPOLYGON_H
#define INTELLITOOLPOLYGON_H

#include "IntelliTool.h"
#include <vector>
#include <QPoint>

class IntelliToolPolygon : public IntelliTool
{
public:
    IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker);

    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;
    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;

private:
    bool isNearStart(int x, int y, QPoint Startpoint);

    int lineWidth;
    int width;
    int height;
    bool isDrawing;
    bool PointIsNearStart;
    QPoint drawingPoint;
    std::vector<QPoint> QPointList;

};

#endif // INTELLITOOLPOLYGON_H
