#ifndef INTELLITOOLSETCOLORTOOL_H
#define INTELLITOOLSETCOLORTOOL_H

#include "QColor"
#include "QPoint"
#include "QColorDialog"

//for unit testing
class UnitTest;

/*!
 * \brief The IntelliColorPicker manages the selected colors for one whole project.
 */
class IntelliColorPicker {
friend UnitTest;
public:
/*!
 * \brief IntelliColorPicker constructor, setting 2 preset colors, be careful, theese color may change in production.
 */
IntelliColorPicker();

/*!
 * \brief IntelliColorPicker destructor clears up his used memory, if there is some.
 */
virtual ~IntelliColorPicker();

/*!
 * \brief A function switching primary and secondary color.
 */
void swapColors();

/*!
 * \brief A function to read the primary selected color.
 * \return Returns the primary color.
 */
QColor getFirstColor() const;

/*!
 * \brief A function to read the secondary selected color.
 * \return Returns the secondary color.
 */
QColor getSecondColor() const;

/*!
 * \brief A function to set the primary color.
 * \param Color - The color to be set as primary.
 */
void setFirstColor(QColor Color);

/*!
 * \brief A function to set the secondary color.
 * \param Color - The color to be set as secondary.
 */
void setSecondColor(QColor Color);

private:
/*!
 * \brief The primary color.
 */
QColor firstColor;

/*!
 * \brief The secondary color.
 */
QColor secondColor;

/*!
 * \brief initializeColors initializes the first and second color.
 */
void initializeColors();
};

#endif
