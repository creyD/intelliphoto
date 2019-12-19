#ifndef INTELLITOOLCIRCLE_H
#define INTELLITOOLCIRCLE_H
#include "IntelliTool.h"

#include "QColor"
#include "QPoint"
/*!
 * \brief The IntelliToolCircle class representing a tool to draw a circle.
 */
class IntelliToolCircle : public IntelliTool{
    /*!
     * \brief A function that implements a circle drawing algorithm.
     * \param radius    - The radius of the circle.
     */
    void drawCyrcle(int radius);

    /*!
     * \brief The center of the circle.
     */
    QPoint Middle;

    /*!
     * \brief The alpha value of the inner circle.
     */
    int alphaInner;

    /*!
     * \brief The width of the outer circle edge.
     */
    int edgeWidth;
public:
    /*!
     * \brief A constructor setting the general Painting Area and colorPicker. And reading in the The inner alpha and edgeWIdth.
     * \param Area          - The general PaintingArea used by the project.
     * \param colorPicker   - The general colorPicker used by the project.
     */
    IntelliToolCircle(PaintingArea* Area, IntelliColorPicker* colorPicker);

    /*!
     * \brief An Destructor.
     */
    virtual ~IntelliToolCircle() override;

    /*!
     * \brief A function managing the right click Pressed of a Mouse. Sets the middle point of the cricle.
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseRightPressed(int x, int y) override;

    /*!
     * \brief A function managing the right click Released of a Mouse.
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseRightReleased(int x, int y) override;

    /*!
     * \brief A function managing the left click Pressed of a Mouse. Clearing the canvas layer.
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseLeftPressed(int x, int y) override;

    /*!
     * \brief A function managing the left click Released of a Mouse.
     * \param x - The x coordinate relative to the Active/Canvas Layer.
     * \param y - The y coordinate relative to the Active/Canvas Layer.
     */
    virtual void onMouseLeftReleased(int x, int y) override;

    /*!
     * \brief A function managing the scroll event. Changing the edge Width relative to value.
     * \param value - The absolute the scroll has changed.
     */
    virtual void onWheelScrolled(int value) override;

    /*!
     * \brief A function managing the mouse moved event. Draws a circle with radius of eulerian norm of mouse position and the middle point.
     * \param x - The x coordinate of the new Mouse Position.
     * \param y - The y coordinate of the new Mouse Position.
     */
    virtual void onMouseMoved(int x, int y) override;
};

#endif // INTELLITOOLCIRCLE_H
