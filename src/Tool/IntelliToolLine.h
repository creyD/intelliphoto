#ifndef INTELLITOOLLINE_H
#define INTELLITOOLLINE_H
#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

enum class LineStyle{
    SOLID_LINE,
    DOTTED_LINE
};

class IntelliToolLine : public IntelliTool{
    QPoint start;
    int lineWidth;
    LineStyle lineStyle;
public:
    IntelliToolLine(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliToolLine() override;


    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLLINE_H
