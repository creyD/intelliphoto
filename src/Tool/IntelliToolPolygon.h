#ifndef INTELLITOOLPOLYGON_H
#define INTELLITOOLPOLYGON_H

#include "IntelliTool.h"
#include "IntelliHelper/IntelliHelper.h"
#include <vector>
#include <QPoint>
/*!
 * \brief The IntelliToolPolygon managed the Drawing of Polygonforms
 */
class IntelliToolPolygon : public IntelliTool
{
    /*!
     * \brief Checks if the given Point lies near the starting Point.
     * \param x             - x coordinate of a point.
     * \param y             - y coordinate of a point.
     * \param Startpoint    - The startingpoint to check for.
     * \return Returns true if the (x,y) point is near to the startpoint, otherwise false.
     */
    bool isNearStart(int x, int y, QPoint Startpoint);

    /*!
     * \brief LineWidth of the drawing polygon.
     */
    int lineWidth;

    /*!
     * \brief IsDrawing true while drawing, else false.
     */
    bool isDrawing;

    /*!
     * \brief PointIsNearStart true, when last click near startpoint, else false.
     */
    bool PointIsNearStart;

    /*!
     * \brief The alpha value of the inner circle.
     */
    int alphaInner;

    /*!
     * \brief QPointList list of all points of the polygon.
     */
    std::vector<QPoint> QPointList;
public:
    /*!
     * \brief IntelliToolPolygon Constructor Define the Tool-intern Parameters
     * \param Area
     * \param colorPicker
     */
    IntelliToolPolygon(PaintingArea* Area, IntelliColorPicker* colorPicker);

    virtual void onMouseLeftPressed(int x, int y) override;
    virtual void onMouseLeftReleased(int x, int y) override;
    virtual void onMouseRightPressed(int x, int y) override;
    virtual void onMouseRightReleased(int x, int y) override;

    virtual void onWheelScrolled(int value) override;

    virtual void onMouseMoved(int x, int y) override;



};

#endif // INTELLITOOLPOLYGON_H
