#ifndef INTELLITOOLCIRCLE_H
#define INTELLITOOLCIRCLE_H
#include "IntelliTool.h"

#include "QColor"
#include "QPoint"

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliToolCircle class represents a tool to draw a circle.
 */
class IntelliToolCircle : public IntelliTool {
friend UnitTest;
/*!
 * \brief A function that implements a circle drawing algorithm.
 * \param radius    - The radius of the circle.
 */
void drawCircle(int radius);

/*!
 * \brief The center of the circle.
 */
QPoint centerPoint;

public:
/*!
 * \brief A constructor setting the general paintingArea and colorPicker. And reading in the inner alpha and edgeWidth.
 * \param Area          - The general paintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolCircle(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

/*!
 * \brief A Destructor.
 */
virtual ~IntelliToolCircle() override;

/*!
 * \brief A function managing the right click pressed of a mouse. Clearing the canvas layer.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseRightPressed(int x, int y) override;

/*!
 * \brief A function managing the right click released of a mouse.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseRightReleased(int x, int y) override;

/*!
 * \brief A function managing the left click pressed of a mouse. Sets the middle point of the cricle.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftPressed(int x, int y) override;

/*!
 * \brief A function managing the left click released of a mouse.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftReleased(int x, int y) override;

/*!
 * \brief A function managing the scroll event. Changing the edge Width relative to value.
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value) override;

/*!
 * \brief A function managing the mouse moved event. Draws a circle with radius of eulerian norm of mouse position and the middle point.
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y) override;
};

#endif
