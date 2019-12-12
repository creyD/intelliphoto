#ifndef INTELLITOOLFLOODFILLTOOL_H
#define INTELLITOOLFLOODFILLTOOL_H

#include "IntelliHelper/IntelliColorPicker.h"

class IntelliToolFloodFillTool : public IntelliTool
{
public:
    IntelliToolFloodFillTool(PaintingArea *Area);

    void onMouseLeftPressed(int x, int y) override;
    void onMouseLeftReleased(int x, int y) override;
    void onMouseRightPressed(int x, int y) override;
    void onMouseRightReleased(int x, int y) override;
    void onMouseMoved(int x, int y) override;

private:
    IntelliColorPicker* Tool;
    bool isPressed;
};

#endif // INTELLITOOLFLOODFILLTOOL_H
