#ifndef INTELLITOOLSETCOLORTOOL_H
#define INTELLITOOLSETCOLORTOOL_H

#include"Layer/PaintingArea.h"
#include"QColor"
#include"QPoint"
#include"QColorDialog"

class IntelliColorPicker{
public:
    IntelliColorPicker(PaintingArea *Area);
    virtual ~IntelliColorPicker();

    void getColorbar(int firstOrSecondColor);
    void switchColors();

    QColor getFirstColor();
    QColor getSecondColor();

    void setFirstColor(QColor Color);
    void setSecondColor(QColor Color);

private:
    QColor firstColor;
    QColor secondColor;
};

#endif // INTELLITOOLSETCOLORTOOL_H
