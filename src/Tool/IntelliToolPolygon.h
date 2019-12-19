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

private:
    /*!
     * \brief isNearStart
     * \param x
     * \param y
     * \param Startpoint
     * \return true : Near Startpoint, else false
     */
    bool isNearStart(int x, int y, QPoint Startpoint);

    /*!
     * \brief lineWidth of the Drawing Polygon
     */
    int lineWidth;
    /*!
     * \brief width of the active Layer
     */
    int width;
    /*!
     * \brief height of the active Layer
     */
    int height;
    /*!
     * \brief isDrawing true while drawing, else false
     */
    bool isDrawing;
    /*!
     * \brief PointIsNearStart true, when last click near Startpoint, else false
     */
    bool PointIsNearStart;
    /*!
     * \brief drawingPoint Current Point after Left-Click
     */
    QPoint drawingPoint;
    /*!
     * \brief Point Needed to look, if Point is in Polygon
     */
    QPoint Point;
    /*!
     * \brief QPointList List of all Points of the Polygon
     */
    std::vector<QPoint> QPointList;
    /*!
     * \brief Triangles Transformed QPointList into triangulated Form of the Polygon
     */
    std::vector<Triangle> Triangles;

};

#endif // INTELLITOOLPOLYGON_H
