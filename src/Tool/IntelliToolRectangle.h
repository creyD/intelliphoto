#ifndef INTELLIRECTANGLETOOL_H
#define INTELLIRECTANGLETOOL_H

#include "IntelliTool.h"

#include "QColor"
#include "QPoint"
/*!
 * \brief The IntelliToolRectangle class represents a tool to draw a rectangle.
 */
class IntelliToolRectangle : public IntelliTool {
/*!
 * \brief A function that implements a rectagle drawing algorithm.
 * \param othercorner - The second corner point of the rectangle.
 */
void drawRectangle(QPoint otherCorner);

/*!
 * \brief origincorner - The first corner point of the rectangle.
 */
QPoint originCorner;
public:
/*!
 * \brief A constructor setting the general paintingArea and colorPicker. And reading in the alphaInner and edgeWidth.
 * \param Area          - The general paintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolRectangle(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);
/*!
 * \brief A Destructor.
 */
virtual ~IntelliToolRectangle() override;

/*!
 * \brief A function managing the right click pressed of a mouse.Resetting the current draw.
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
 * \brief A function managing the left click pressed of a mouse. Setting the originCorner and draws a rectangle.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftPressed(int x, int y) override;

/*!
 * \brief A function managing the left click released of a mouse. Merging the draw to the active layer.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftReleased(int x, int y) override;

/*!
 * \brief A function managing the scroll event.Changing edgeWidth relativ to value.
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value) override;

/*!
 * \brief A function managing the mouse moved event.Drawing a rectangle to currrent mouse position.
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLIRECTANGLETOOL_H
