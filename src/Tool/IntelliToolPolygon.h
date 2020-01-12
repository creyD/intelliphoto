#ifndef INTELLITOOLPOLYGON_H
#define INTELLITOOLPOLYGON_H

#include "IntelliTool.h"
#include "IntelliHelper/IntelliTriangulation.h"
#include <vector>
#include <QPoint>

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliToolPolygon managed the Drawing of Polygonforms
 */
class IntelliToolPolygon : public IntelliTool
{
    friend UnitTest;
/*!
 * \brief Checks if the given Point lies near the starting Point.
 * \param x             - x coordinate of a point.
 * \param y             - y coordinate of a point.
 * \param Startpoint    - The startingpoint to check for.
 * \return Returns true if the (x,y) point is near to the startpoint, otherwise false.
 */
bool isNearStart(int x, int y, QPoint Startpoint);

/*!
 * \brief IsDrawing true while drawing, else false.
 */
bool isDrawing;

/*!
 * \brief isInside Checks if Point is inside Image
 */
bool isInside;

/*!
 * \brief PointIsNearStart true, when last click near startpoint, else false.
 */
bool isPointNearStart;

/*!
 * \brief QPointList list of all points of the polygon.
 */
std::vector<QPoint> QPointList;
public:
/*!
 * \brief A constructor setting the general paintingArea and colorPicker.
 * \param Area          - The general paintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);
/*!
 * \brief A Destructor.
 */
~IntelliToolPolygon() override;

/*!
 * \brief A function managing the left click pressed of a mouse. Setting polygon points.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftPressed(int x, int y) override;

/*!
 * \brief A function managing the left click released of a mouse. Merging the fill to the active layer.
 * \param x - The x coordinate relative to the active/canvas layer.
 * \param y - The y coordinate relative to the active/canvas layer.
 */
virtual void onMouseLeftReleased(int x, int y) override;

/*!
 * \brief A function managing the right click pressed of a mouse. Resetting the current fill.
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
 * \brief A function managing the scroll event. CHanging the lineWidth relative to value.
 * \param value - The absolute the scroll has changed.
 */
virtual void onWheelScrolled(int value) override;

/*!
 * \brief A function managing the mouse moved event.
 * \param x - The x coordinate of the new mouse position.
 * \param y - The y coordinate of the new mouse position.
 */
virtual void onMouseMoved(int x, int y) override;


};

#endif // INTELLITOOLPOLYGON_H
