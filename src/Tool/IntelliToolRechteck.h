#ifndef INTELLIRECHTECKTOOL_H
#define INTELLIRECHTECKTOOL_H

#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

class IntelliToolRechteck : public IntelliTool{
    void drawRechteck(QPoint otherCornor);

    QPoint originCornor;
    int alphaInner;
    int edgeWidth;
public:
    IntelliToolRechteck(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolRechteck() override;

    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLIRECHTECKTOOL_H
