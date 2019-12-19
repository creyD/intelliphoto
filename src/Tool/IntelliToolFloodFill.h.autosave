#ifndef INTELLITOOLFLOODFILL_H
#define INTELLITOOLFLOODFILL_H
#include "IntelliTool.h"

#include "QColor"

/*!
 * \brief The IntelliToolFloodFill class represents a tool to flood FIll a certian area.
 */
class IntelliToolFloodFill : public IntelliTool{
public:
    /*!
     * \brief A constructor setting the general paintingArea and colorPicker.
     * \param Area          - The general paintingArea used by the project.
     * \param colorPicker   - The general colorPicker used by the project.
     */
    IntelliToolFloodFill(PaintingArea* Area, IntelliColorPicker* colorPicker);

    /*!
     * \brief A Destructor.
     */
    virtual ~IntelliToolFloodFill() override;


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
     * \brief A function managing the left click pressed of a mouse. Sets the point to flood fill around and does this.
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
     * \brief A function managing the scroll event.
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

#endif // INTELLITOOLFLOODFILL_H
