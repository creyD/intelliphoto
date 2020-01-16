#ifndef Intelli_Tool_H
#define Intelli_Tool_H

#include "IntelliHelper/IntelliColorPicker.h"
#include "IntelliHelper/IntelliToolsettings.h"
#include <vector>

//for unit testing
class UnitTest;

struct LayerObject;
class PaintingArea;

/*!
 * \brief An abstract class that manages the basic events, like mouse clicks or scrolls events.
 */
class IntelliTool {
    friend UnitTest;
public:
enum class Tooltype {
		CIRCLE,
		FLOODFILL,
		LINE,
		PEN,
		PLAIN,
		POLYGON,
        RECTANGLE,
        NONE
};
private:
/*!
 * \brief A function that creates a layer to draw on.
 * \return Returns if a layer could be created
 */
bool createToolLayer();

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

Tooltype ActiveType;

/*!
 * \brief A pointer to the IntelliColorPicker of the PaintingArea to interact with, and get the colors.
 */
IntelliColorPicker* colorPicker;

IntelliToolsettings* Toolsettings;

/*!
 * \brief A pointer to the underlying active Layer, do not work on this. This is used for data grabbing or previews.
 */
LayerObject* activeLayer;

/*!
 * \brief A pointer to the drawing canvas of the tool, work on this.
 */
LayerObject* Canvas;

/*!
 * \brief A flag checking if the user is currently drawing or not.
 */
bool isDrawing = false;

public:
/*!
 * \brief A constructor setting the general Painting Area and colorPicker.
 * \param Area          - The general PaintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliTool(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

/*!
 * \brief An abstract Destructor.
 */
virtual ~IntelliTool() = 0;

/*!
 * \brief A function managing the right click Pressed of a Mouse. Constructing the Canvas to draw on. Call this in child classes!
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseRightPressed(int x, int y);

/*!
 * \brief A function managing the right click Released of a Mouse. Merging the Canvas to Active. Call this in child classes!
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseRightReleased(int x, int y);

/*!
 * \brief A function managing the left click Pressed of a Mouse. Resetting the current draw. Call this in child classes!
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftPressed(int x, int y);

/*!
 * \brief A function managing the left click Released of a Mouse. Call this in child classes!
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftReleased(int x, int y);

/*!
 * \brief A function managing the scroll event. A positive value means scrolling outwards. Call this in child classes!
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value);

/*!
 * \brief A function managing the mouse moved event. Call this in child classes!
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y);

Tooltype getTooltype();

bool getIsDrawing();

};
#endif
