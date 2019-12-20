#ifndef INTELLITOOLPEN_H
#define INTELLITOOLPEN_H

#include "IntelliTool.h"
#include "QColor"
#include "QPoint"
/*!
 * \brief The IntelliToolPen class represents a tool to draw a line.
 */
class IntelliToolPen : public IntelliTool {
/*!
 * \brief penWidth - The width of the Pen while drawing.
 */
int penWidth;
/*!
 * \brief point - Represents the previous point to help drawing a line.
 */
QPoint previousPoint;
public:
/*!
 * \brief A constructor setting the general paintingArea and colorPicker. Reading the penWidth.
 * \param Area          - The general PaintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolPen(PaintingArea* Area, IntelliColorPicker* colorPicker);
/*!
 * \brief A Destructor.
 */
virtual ~IntelliToolPen() override;

/*!
 * \brief A function managing the right click pressed of a mouse. Resetting the current draw.
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
 * \brief A function managing the left click pressed of a mouse. Starting the drawing procedure.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftPressed(int x, int y) override;

/*!
 * \brief A function managing the left click released of a mouse. Merging the drawing to the active layer.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftReleased(int x, int y) override;

/*!
 * \brief A function managing the scroll event. Changing penWidth relativ to value.
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value) override;

/*!
 * \brief A function managing the mouse moved event. To draw the line.
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLPEN_H
