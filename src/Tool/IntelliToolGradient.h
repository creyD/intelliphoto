#ifndef INTELLITOOLGRADIENT_H
#define INTELLITOOLGRADIENT_H
#include "IntelliTool.h"

class IntelliToolGradient : public IntelliTool{
private:
    QPoint A;
    QPoint B;
    QPoint VectorAB;
    QColor LineColor;
    bool hasMoved;

public:
    IntelliToolGradient(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

    ~IntelliToolGradient();

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

    void computePixelColor(QPoint Point);

    float dotProduct(QPoint Vector1, QPoint Vector2);
};

#endif // INTELLITOOLGRADIENT_H
