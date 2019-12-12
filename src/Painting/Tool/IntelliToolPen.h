#ifndef INTELLITOOLPEN_H
#define INTELLITOOLPEN_H

#include"IntelliTool.h"
#include"QColor"
#include"QPoint"

class IntelliToolPen : public IntelliTool{
    int penWidth;
    QPoint point;
public:
    IntelliToolPen(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolPen() override;

    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLPEN_H
