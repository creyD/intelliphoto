#ifndef INTELLITOOLFLOODFILLTOOL_H
#define INTELLITOOLFLOODFILLTOOL_H

#include "IntelliTool.h"
#include "QColor"

class IntelliToolPlainTool : public IntelliTool
{
public:
    IntelliToolPlainTool(PaintingArea *Area, IntelliColorPicker* colorPicker);

    void onMouseLeftPressed(int x, int y) override;
    void onMouseLeftReleased(int x, int y) override;
    void onMouseRightPressed(int x, int y) override;
    void onMouseRightReleased(int x, int y) override;
    void onMouseMoved(int x, int y) override;

};

#endif // INTELLITOOLFLOODFILLTOOL_H
