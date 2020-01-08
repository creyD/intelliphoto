#ifndef INTELLITOOLFLOODFILLTOOL_H
#define INTELLITOOLFLOODFILLTOOL_H

#include "IntelliTool.h"
#include "QColor"
/*!
 * \brief The IntelliToolPlainTool class represents a tool to fill the whole canvas with one color.
 */
class IntelliToolPlainTool : public IntelliTool {
public:
/*!
 * \brief A constructor setting the general paintingArea and colorPicker.
 * \param Area          - The general paintingArea used by the project.
 * \param colorPicker   - The general colorPicker used by the project.
 */
IntelliToolPlainTool(PaintingArea*Area, IntelliColorPicker* colorPicker, IntelliToolsettings* Toolsettings);
/*!
 * \brief A Destructor.
 */
virtual ~IntelliToolPlainTool() override;

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
 * \brief A function managing the left click pressed of a mouse. Filling the whole canvas.
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

#endif // INTELLITOOLFLOODFILLTOOL_H
