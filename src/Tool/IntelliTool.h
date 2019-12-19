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

    /*!
     * \brief A pointer to the underlying active Layer, do not work on this. This is used for data grabbing or previews.
     */
    LayerObject* Active;

    /*!
     * \brief A pointer to the drawing canvas of the tool, work on this.
     */
    LayerObject* Canvas;

    /*!
     * \brief A flag checking if the user is currently drawing or not.
     */
    bool drawing = false;

public:
    /*!
     * \brief A constructor setting the general Painting Area and colorPicker.
     * \param Area          - The general PaintingArea used by the project.
     * \param colorPicker   - The general colorPicker used by the project
     */
    IntelliTool(PaintingArea* Area, IntelliColorPicker* colorPicker);

    /*!
     * \brief An abstract Destructor.
     */
    virtual ~IntelliTool() = 0;

    /*!
     * \brief A function managing the right click Pressed of a Mouse. Constructing the Canvas to draw on. Call this in child classes!
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseRightPressed(int x, int y);

    /*!
     * \brief A function managing the right click Released of a Mouse. Merging the Canvas to Active. Call this in child classes!
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseRightReleased(int x, int y);

    /*!
     * \brief A function managing the left click Pressed of a Mouse. Resetting the current draw. Call this in child classes!
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseLeftPressed(int x, int y);

    /*!
     * \brief A function managing the left click Released of a Mouse. Call this in child classes!
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseLeftReleased(int x, int y);

    /*!
     * \brief A function managing the scroll event. A Positive Value means scrolling outwards. Call this in child classes!
     * \param value - The absolute the scroll has changed.
     */
    virtual void onWheelScrolled(int value);

    /*!
     * \brief A function managing the mouse moved event. Call this in child classes!
     * \param x - The x coordinate of the new Mouse Position.
     * \param y - The y coordinate of the new Mouse Position.
     */
    virtual void onMouseMoved(int x, int y);


};
#endif
