#ifndef INTELLITOOLLINE_H
#define INTELLITOOLLINE_H
#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

enum class LineStyle{
    SOLID_LINE
};

class IntelliToolLine : public IntelliTool
{
    QPoint start;
    QColor color;
    int lineWidth;
    LineStyle lineStyle;
public:
    IntelliToolLine(PaintingArea* Area);
    virtual ~IntelliToolLine() override;


    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLLINE_H
