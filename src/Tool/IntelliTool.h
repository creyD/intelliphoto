#ifndef Intelli_Tool_H
#define Intelli_Tool_H

#include "IntelliHelper/IntelliColorPicker.h"
#include <vector>

class LayerObject;
class PaintingArea;

/*!
 * \brief An abstract class that manages the basic events, like mouse clicks or scrolls events.
 */
class IntelliTool{
private:
    /*!
     * \brief A function that creates a layer to draw on.
     */
    void createToolLayer();

    /*!
     * \brief A function that merges the drawing- and the active- layer.
     */
    void mergeToolLayer();

    /*!
     * \brief A function that deletes the drawinglayer.
     */
    void deleteToolLayer();
protected:
    /*!
     * \brief A pointer to the general PaintingArea to interact with.
     */
    PaintingArea* Area;

    /*!
     * \brief A pointer to the IntelliColorPicker of the PaintingArea to interact with, and get the colors.
     */
    IntelliColorPicker* colorPicker;

    LayerObject* Active;
    LayerObject* Canvas;
    bool drawing = false;

public:
    IntelliTool(PaintingArea* Area, IntelliColorPicker* colorPicker);
    virtual ~IntelliTool() = 0;

    virtual void onMouseRightPressed(int x, int y);
    virtual void onMouseRightReleased(int x, int y);
    virtual void onMouseLeftPressed(int x, int y);
    virtual void onMouseLeftReleased(int x, int y);

    virtual void onWheelScrolled(int value);

    virtual void onMouseMoved(int x, int y);


};
#endif
