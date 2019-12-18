#ifndef INTELLITOOLFLOODFILL_H
#define INTELLITOOLFLOODFILL_H
#include "IntelliTool.h"

#include "QColor"

class IntelliToolFloodFill : public IntelliTool{
public:
    IntelliToolFloodFill(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolFloodFill() override;


    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLFLOODFILL_H
