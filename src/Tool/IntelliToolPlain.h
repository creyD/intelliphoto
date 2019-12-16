#ifndef INTELLITOOLFLOODFILLTOOL_H
#define INTELLITOOLFLOODFILLTOOL_H

#include "IntelliTool.h"
#include "QColor"

class IntelliToolPlainTool : public IntelliTool{
public:
    IntelliToolPlainTool(PaintingArea *Area, IntelliColorPicker* colorPicker);

    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;
    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;

};

#endif // INTELLITOOLFLOODFILLTOOL_H
