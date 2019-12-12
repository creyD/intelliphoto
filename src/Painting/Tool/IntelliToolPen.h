#ifndef INTELLITOOLPEN_H
#define INTELLITOOLPEN_H

#include"IntelliTool.h"
#include"QColor"
#include"QPoint"

class IntelliColorPicker;

class IntelliToolPen : public IntelliTool{
    QPoint point;
public:
    IntelliToolPen(PaintingArea* Area);
    virtual ~IntelliToolPen() override;

    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;
    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;

    virtual void onMouseMoved(int x, int y) override;

private:
    IntelliColorPicker* Tool;
};

#endif // INTELLITOOLPEN_H
