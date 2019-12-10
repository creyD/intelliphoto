#ifndef Intelli_Tool_H
#define Intelli_Tool_H

#include<vector>

class LayerObject;
class PaintingArea;

class IntelliTool{
private:
    void createToolLayer();
    void mergeToolLayer();
    void deleteToolLayer();
protected:
    PaintingArea* Area;
    LayerObject* Active;
    LayerObject* Canvas;
    bool drawing = false;
public:
    IntelliTool(PaintingArea* Area);
    virtual ~IntelliTool() = 0;

    virtual void onMouseRightPressed(int x, int y);
    virtual void onMouseRightReleased(int x, int y);
    virtual void onMouseLeftPressed(int x, int y);
    virtual void onMouseLeftReleased(int x, int y);

    virtual void onMouseMoved(int x, int y);
};
#endif
