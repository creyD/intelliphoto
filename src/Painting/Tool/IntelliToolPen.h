#ifndef INTELLITOOLPEN_H
#define INTELLITOOLPEN_H

#include"IntelliToolSetColorTool.h"
#include"QColor"
#include"QPoint"

class IntelliToolPen : public IntelliToolSetColorTool{
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
    IntelliToolSetColorTool* Tool;
};

#endif // INTELLITOOLPEN_H
