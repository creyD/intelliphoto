#ifndef INTELLITOOLLINE_H
#define INTELLITOOLLINE_H
#include "IntelliTool.h"

#include "QPoint"

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliToolFloodFill class represents a tool to draw a line.
 */
class IntelliToolLine : public IntelliTool {
    friend UnitTest;
/*!
 * \brief The starting point of the line.
 */
QPoint lineStartingPoint;

public:

/*!
 * \brief A constructor setting the general paintingArea and colorPicker. And reading in the lineWidth and lineStyle.
 * \param Area          - The general paintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolLine(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

/*!
 * \brief An abstract Destructor.
 */
virtual ~IntelliToolLine() override;

/*!
 * \brief A function managing the right click pressed of a mouse. Clearing the canvas.
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
 * \brief A function managing the left click pressed of a mouse. Sets the starting point of the line.
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
 * \brief A function managing the scroll event. Changing the lineWidth relative to value.
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value) override;

/*!
 * \brief A function managing the mouse moved event. Drawing a Line from the startpoint to the current mouse position.
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLLINE_H
