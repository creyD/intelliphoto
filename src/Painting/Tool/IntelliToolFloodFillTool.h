#ifndef INTELLITOOLFLOODFILLTOOL_H
#define INTELLITOOLFLOODFILLTOOL_H

#include "IntelliToolSetColorTool.h"

class IntelliToolFloodFillTool : public IntelliToolSetColorTool
{
public:
    IntelliToolFloodFillTool(PaintingArea *Area);

    void IntelliToolFloodFillTool::onMouseLeftPressed(int x, int y) override;
    void IntelliToolFloodFillTool::onMouseLeftReleased(int x, int y) override;
    void IntelliToolFloodFillTool::onMouseRightPressed(int x, int y) override;
    void IntelliToolFloodFillTool::onMouseRightReleased(int x, int y) override;
    void IntelliToolFloodFillTool::onMouseMoved(int x, int y) override;

private:
    IntelliToolSetColorTool* Tool;
    bool isPressed;
};

#endif // INTELLITOOLFLOODFILLTOOL_H
