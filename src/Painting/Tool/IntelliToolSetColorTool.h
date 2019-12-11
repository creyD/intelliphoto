#ifndef INTELLITOOLSETCOLORTOOL_H
#define INTELLITOOLSETCOLORTOOL_H

#include"IntelliTool.h"
#include"QColor"
#include"QPoint"
#include"QColorDialog"

class IntelliToolSetColorTool: public IntelliTool{
public:
    IntelliToolSetColorTool(PaintingArea *Area);
    virtual ~IntelliToolSetColorTool() override;

    void getColorbar(int firstOrSecondColor) override;

    QColor IntelliToolSetColorTool::getFirstColor();
    QColor IntelliToolSetColorTool::getSecondColor();

protected:
    QColor firstColor;
    QColor secondColor;
};

#endif // INTELLITOOLSETCOLORTOOL_H
