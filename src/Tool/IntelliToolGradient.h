#ifndef INTELLITOOLGRADIENT_H
#define INTELLITOOLGRADIENT_H
#include "IntelliTool.h"
/*!
 * \brief The IntelliToolGradient class that represents a gradient call
 */
class IntelliToolGradient : public IntelliTool {

public:
/*!
 * \brief IntelliToolGradient basic constructor of the gradient tool.
 * \param Area          - a reference to the paintingArea
 * \param colorPicker   - a reference to the colorpicker
 * \param Toolsettings  - a regerence to the Toolsettings
 */
IntelliToolGradient(PaintingArea* Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);

/*!
 * \brief ~IntelliToolGradient basic destructor.
 */
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

/*!
 * \brief startPoint of the line
 */
QPoint startPoint;

/*!
 * \brief endPoint of the line
 */
QPoint endPoint;
/*!
 * \brief doubleStartPoint startPoint as double Values
 */
double doubleStartPoint[2];

/*!
 * \brief VectorStartEnd a vector between start and end point.
 */
double VectorStartEnd[2];

/*!
 * \brief LineColor color of th line.
 */
QColor LineColor;

/*!
 * \brief hasMoved indicates a movement
 */
bool hasMoved;

/*!
 * \brief computeAndDrawPixelColor computes the pixelcolor for a given point and sets it to the image.
 * \param Point the point which shoud be computed
 */
void computeAndDrawPixelColor(QPoint Point, int FirstColor[4], int SecondColor[4], double NormalVector[2], double NormalDotNormal);

/*!
 * \brief dotProduct calculates the dot product of 2 vetors.
 * \param Vector1   - first argument
 * \param Vector2   - second argument
 * \return returns the dot product.
 */
double dotProduct(double Vector1[2], double Vector2[2]);

/*!
 * \brief lenghtVector returns the length of a vector
 * \param Vector    - Vector to calculate the length
 * \return returns the length of the vector
 */
double lenghtVector(double Vector[2]);

/*!
 * \brief computeGradientLayer computes the gradient over all pixels in the image.
 */
void computeGradientLayer();
};

#endif // INTELLITOOLGRADIENT_H
