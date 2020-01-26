#ifndef INTELLITOOLGRADIENT_H
#define INTELLITOOLGRADIENT_H
#include "IntelliTool.h"

class IntelliToolGradient : public IntelliTool{

public:
    IntelliToolGradient(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

    virtual ~IntelliToolGradient() override;

    /*!
     * \brief A function managing the right click Pressed of a Mouse. Constructing the Canvas to draw on. Call this in child classes!
     * \param x - The x coordinate relative to the active/canvas layer.
     * \param y - The y coordinate relative to the active/canvas layer.
     */
    virtual void onMouseRightPressed(int x, int y) override;

    /*!
     * \brief A function managing the right click Released of a Mouse. Merging the Canvas to Active. Call this in child classes!
     * \param x - The x coordinate relative to the active/canvas layer.
     * \param y - The y coordinate relative to the active/canvas layer.
     */
    virtual void onMouseRightReleased(int x, int y) override;

    /*!
     * \brief A function managing the left click Pressed of a Mouse. Resetting the current draw. Call this in child classes!
     * \param x - The x coordinate relative to the active/canvas layer.
     * \param y - The y coordinate relative to the active/canvas layer.
     */
    virtual void onMouseLeftPressed(int x, int y) override;

    /*!
     * \brief A function managing the left click Released of a Mouse. Call this in child classes!
     * \param x - The x coordinate relative to the active/canvas layer.
     * \param y - The y coordinate relative to the active/canvas layer.
     */
    virtual void onMouseLeftReleased(int x, int y) override;

    /*!
     * \brief A function managing the scroll event. A positive value means scrolling outwards. Call this in child classes!
     * \param value - The absolute the scroll has changed.
     */
    virtual void onWheelScrolled(int value) override;

    /*!
     * \brief A function managing the mouse moved event. Call this in child classes!
     * \param x - The x coordinate of the new mouse position.
     * \param y - The y coordinate of the new mouse position.
     */
    virtual void onMouseMoved(int x, int y) override;

private:
    QPoint A;
    QPoint B;
    double doubleA[2];
    double VectorAB[2];
    double NormalVector[2];
    double NormalDotNormal;
    QColor LineColor;
    bool hasMoved;

    void computePixelColor(QPoint Point);

    double dotProduct(double Vector1[2], double Vector2[2]);

    double lenghtVector(double Vector[2]);

    void computeGradientLayer();
};

#endif // INTELLITOOLGRADIENT_H
