#ifndef INTELLITOOLCIRCLE_H
#define INTELLITOOLCIRCLE_H
#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

class IntelliToolCircle : public IntelliTool{
    void drawCyrcle(int radius);

    QPoint Middle;
    int alphaInner;
    int edgeWidth;
public:
    IntelliToolCircle(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolCircle() override;

    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLCIRCLE_H
