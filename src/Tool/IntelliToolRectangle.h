#ifndef INTELLIRECTANGLETOOL_H
#define INTELLIRECTANGLETOOL_H

#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

class IntelliToolRectangle : public IntelliTool{
    void drawRectangle(QPoint otherCornor);

    QPoint originCornor;
    int alphaInner;
    int edgeWidth;
public:
    IntelliToolRectangle(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolRectangle() override;

    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLIRECTANGLETOOL_H
