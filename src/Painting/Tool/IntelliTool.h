#ifndef Intelli_Tool_H
#define Intelli_Tool_H

#include"Layer/PaintingArea.h"

class IntelliTool{
private:
    LayerObject* DataValue;
    LayerObject* Preview;
public:
    IntelliTool(LayerObject* DataValue, LayerObject* Preview);
    virtual ~IntelliTool() = 0;

    virtual void onMousePressed(QMouseEvent *event) = 0;
    virtual void onMouseMoved(QMouseEvent* event)=0;
    virtual void onMouseReleased(QMouseEvent* event)=0;
};
#endif
